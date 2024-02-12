<?php

declare(strict_types=1);

namespace PhpStaticAnalysis\RectorRule;

use PhpParser\Node;
use PhpParser\Node\Attribute;
use PhpParser\Node\AttributeGroup;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Name\FullyQualified;
use PhpParser\Node\Scalar;
use PhpParser\Node\Stmt;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ParamTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ReturnTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\TemplateTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\VarTagValueNode;
use PHPStan\PhpDocParser\Ast\Type\IdentifierTypeNode;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\Attributes\Type;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Comments\NodeDocBlock\DocBlockUpdater;
use Rector\Contract\Rector\ConfigurableRectorInterface;
use Rector\Php80\NodeManipulator\AttributeGroupNamedArgumentManipulator;
use Rector\Php80\ValueObject\AnnotationToAttribute;
use Rector\Rector\AbstractRector;
use Rector\ValueObject\PhpVersionFeature;
use Rector\VersionBonding\Contract\MinPhpVersionInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

/** @psalm-suppress PropertyNotSetInConstructor */
final class AnnotationsToAttributesRector extends AbstractRector implements ConfigurableRectorInterface, MinPhpVersionInterface
{
    #[Type('AnnotationToAttribute[]')]
    private array $annotationsToAttributes = [];

    private bool $addParamAttributeOnParameters = false;

    public function __construct(
        private PhpDocTagRemover $phpDocTagRemover,
        private AttributeGroupNamedArgumentManipulator $attributeGroupNamedArgumentManipulator,
        private DocBlockUpdater $docBlockUpdater,
        private PhpDocInfoFactory $phpDocInfoFactory,
    ) {
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('// Converts PHPDoc annotations for static analysis to PHP attributes', [
            new CodeSample(
                <<<'CODE_SAMPLE'
<?php

class ArrayAdder
{
    /** @var array<string>  */
    private array $result;

    /**
     * @param array<string> $array1
     * @param array<string> $array2
     * @return array<string>
     */
    public function addArrays(array $array1, array $array2): array
    {
        $this->result = $array1 + $array2;
        return $this->result;
    }
}
CODE_SAMPLE
                ,
                <<<'CODE_SAMPLE'
<?php

use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ArrayAdder
{
    #[Type('array<string>')]
    private array $result;

    #[Param(array1: 'array<string>')]
    #[Param(array2: 'array<string>')]
    #[Returns('array<string>')]
    public function addArrays(array $array1, array $array2): array
    {
        $this->array = $array1 + $array2;
        return $this->array;
    }
}

CODE_SAMPLE
            ),
        ]);
    }

    /**
     * @psalm-suppress MoreSpecificImplementedParamType
     */
    #[Param(configuration: '(AnnotationToAttribute|bool)[]')]
    public function configure(array $configuration): void
    {
        foreach ($configuration as $key => $value) {
            if ($value instanceof AnnotationToAttribute) {
                $this->annotationsToAttributes[] = $value;
            } elseif ($key == 'addParamAttributeOnParameters') {
                $this->addParamAttributeOnParameters = $value;
            }
        }
    }

    #[Returns('array<class-string<Node>>')]
    public function getNodeTypes(): array
    {
        return [
            Stmt\Class_::class,
            Stmt\ClassConst::class,
            Stmt\ClassMethod::class,
            Stmt\Function_::class,
            Stmt\Interface_::class,
            Stmt\Property::class,
            Stmt\Trait_::class
        ];
    }

    /**
     * @psalm-suppress MoreSpecificImplementedParamType
     */
    #[Param(node: 'Stmt\Class_|Stmt\ClassConst|Stmt\ClassMethod|Stmt\Function_|Stmt\Interface_|Stmt\Property|Stmt\Trait_')]
    public function refactor(Node $node): ?Node
    {
        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($node);
        if (!$phpDocInfo instanceof PhpDocInfo) {
            return null;
        }

        $attributeGroups = $this->processAnnotations($phpDocInfo);

        if ($attributeGroups === []) {
            return null;
        }

        $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);

        $this->attributeGroupNamedArgumentManipulator->decorate($attributeGroups);

        if ($this->addParamAttributeOnParameters &&
            ($node instanceof Stmt\ClassMethod || $node instanceof Stmt\Function_)) {
            foreach ($attributeGroups as $attrKey => $attributeGroup) {
                foreach ($attributeGroup->attrs as $key => $attribute) {
                    if ((string)$attribute->name === Param::class) {
                        $args = $attribute->args;
                        if (isset($args[0])) {
                            $arg = $args[0];
                            $argName = (string)$arg->name;
                            $parameters = $node->getParams();
                            foreach ($parameters as $parameter) {
                                if ($parameter->var instanceof Variable && is_string($parameter->var->name) &&
                                    $parameter->var->name === $argName) {
                                    unset($attributeGroup->attrs[$key]);
                                    $arg->name = null;
                                    $parameterAttributeGroups = [new AttributeGroup([$attribute])];
                                    $parameter->attrGroups = array_merge($parameter->attrGroups, $parameterAttributeGroups);
                                }
                            }
                        }
                    }
                }
                if ($attributeGroup->attrs === []) {
                    unset($attributeGroups[$attrKey]);
                }
            }
        }

        $node->attrGroups = array_merge($node->attrGroups, $attributeGroups);

        return $node;
    }

    #[Returns('AttributeGroup[]')]
    private function processAnnotations(PhpDocInfo $phpDocInfo): array
    {
        if ($phpDocInfo->getPhpDocNode()->children === []) {
            return [];
        }

        $attributeGroups = [];
        $tagValueNodes = [];

        foreach ($phpDocInfo->getPhpDocNode()->children as $phpDocChildNode) {
            if (!$phpDocChildNode instanceof PhpDocTagNode) {
                continue;
            }

            $tagValueNode = $phpDocChildNode->value;
            switch (true) {
                case $tagValueNode instanceof ParamTagValueNode:
                    $args = [
                        new Node\Arg(
                            value: new Scalar\String_((string)($tagValueNode->type)),
                            name: new Node\Identifier(substr($tagValueNode->parameterName, 1))
                        )
                    ];
                    break;
                case $tagValueNode instanceof ReturnTagValueNode:
                case $tagValueNode instanceof VarTagValueNode:
                    $args = [
                        new Node\Arg(new Scalar\String_((string)($tagValueNode->type)))
                    ];
                    break;
                case $tagValueNode instanceof TemplateTagValueNode:
                    $args = [
                        new Node\Arg(new Scalar\String_($tagValueNode->name))
                    ];
                    if ($tagValueNode->bound instanceof IdentifierTypeNode) {
                        $args[] = new Node\Arg(new Scalar\String_($tagValueNode->bound->name));
                    }
                    break;
                case $tagValueNode instanceof GenericTagValueNode:
                    $args = [];
                    break;
                default:
                    continue 2;
            }

            $annotationToAttribute = $this->matchAnnotationToAttribute($phpDocChildNode->name);
            if (!$annotationToAttribute instanceof AnnotationToAttribute) {
                continue;
            }

            $tagValueNodes[] = $tagValueNode;

            $attributeName = new FullyQualified($annotationToAttribute->getAttributeClass());
            $attribute = new Attribute($attributeName, $args);
            $attributeGroups[] = new AttributeGroup([$attribute]);
        }

        foreach ($tagValueNodes as $tagValueNode) {
            $this->phpDocTagRemover->removeTagValueFromNode($phpDocInfo, $tagValueNode);
        }

        return $attributeGroups;
    }

    public function provideMinPhpVersion(): int
    {
        return PhpVersionFeature::ATTRIBUTES;
    }

    private function matchAnnotationToAttribute(
        string $tagName
    ): AnnotationToAttribute|null {
        foreach ($this->annotationsToAttributes as $annotationToAttribute) {
            if ($tagName == '@' . $annotationToAttribute->getTag()) {
                return $annotationToAttribute;
            }
        }

        return null;
    }
}
