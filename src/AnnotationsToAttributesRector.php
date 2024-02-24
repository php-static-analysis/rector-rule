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
use PHPStan\PhpDocParser\Ast\PhpDoc\DeprecatedTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ExtendsTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\GenericTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ImplementsTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\MethodTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\MixinTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ParamOutTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ParamTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PhpDocTagNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\PropertyTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\RequireExtendsTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\RequireImplementsTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\ReturnTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\SelfOutTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\TemplateTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\UsesTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\VarTagValueNode;
use PHPStan\PhpDocParser\Ast\Type\IdentifierTypeNode;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\Attributes\Type;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfo;
use Rector\BetterPhpDocParser\PhpDocInfo\PhpDocInfoFactory;
use Rector\BetterPhpDocParser\PhpDocManipulator\PhpDocTagRemover;
use Rector\Comments\NodeDocBlock\DocBlockUpdater;
use Rector\Contract\Rector\ConfigurableRectorInterface;
use Rector\NodeTypeResolver\Node\AttributeKey;
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

    private bool $useTypeAttributeForReturnAnnotation = false;

    private bool $usePropertyAttributeForVarAnnotation = false;

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
                $tag = str_replace('_', '-', $value->getTag());
                $this->annotationsToAttributes[$tag] = $value;
            } elseif ($key == 'addParamAttributeOnParameters') {
                $this->addParamAttributeOnParameters = $value;
            } elseif ($key == 'useTypeAttributeForReturnAnnotation') {
                $this->useTypeAttributeForReturnAnnotation = $value;
            } elseif ($key == 'usePropertyAttributeForVarAnnotation') {
                $this->usePropertyAttributeForVarAnnotation = $value;
            }
        }
        if ($this->useTypeAttributeForReturnAnnotation) {
            if (isset($this->annotationsToAttributes['return'])) {
                $this->annotationsToAttributes['return'] =
                    new AnnotationToAttribute('return', Type::class);
            }
        }
        if ($this->usePropertyAttributeForVarAnnotation) {
            if (isset($this->annotationsToAttributes['var'])) {
                $this->annotationsToAttributes['var'] =
                    new AnnotationToAttribute('var', Property::class);
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

        $attributeGroups = [];
        if ($phpDocInfo instanceof PhpDocInfo) {
            $attributeGroups = $this->processAnnotations($phpDocInfo);
        }

        if ($attributeGroups !== []) {
            $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);

            $this->attributeGroupNamedArgumentManipulator->decorate($attributeGroups);
        }

        if ($this->addParamAttributeOnParameters &&
            ($node instanceof Stmt\ClassMethod || $node instanceof Stmt\Function_)) {
            foreach ($attributeGroups as $attrKey => $attributeGroup) {
                foreach ($attributeGroup->attrs as $key => $attribute) {
                    $attributeName = (string)$attribute->name;
                    if ($attributeName === Param::class || $attributeName == ParamOut::class) {
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

        if ($node instanceof Stmt\Class_) {
            foreach ($node->stmts as $stmt) {
                if ($stmt instanceof Stmt\TraitUse) {
                    $phpDocInfo = $this->phpDocInfoFactory->createFromNode($stmt);
                    if ($phpDocInfo instanceof PhpDocInfo) {
                        $useAttributeGroups = $this->processAnnotations($phpDocInfo);

                        if ($useAttributeGroups !== []) {
                            $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($stmt);

                            $this->attributeGroupNamedArgumentManipulator->decorate($useAttributeGroups);
                            $attributeGroups = array_merge($attributeGroups, $useAttributeGroups);
                        }
                    }
                }
            }
        }

        if ($attributeGroups !== []) {
            $node->attrGroups = array_merge($node->attrGroups, $attributeGroups);
        }

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
            $attributeComment = '';
            switch (true) {
                case $tagValueNode instanceof MethodTagValueNode:
                    $methodSignature = (string)($tagValueNode);
                    $attributeComment = $tagValueNode->description;
                    if ($attributeComment) {
                        $methodSignature = substr($methodSignature, 0, -(strlen($attributeComment) + 1));
                    }
                    $args = [
                        new Node\Arg(new Scalar\String_($methodSignature))
                    ];
                    break;
                case $tagValueNode instanceof ParamOutTagValueNode:
                case $tagValueNode instanceof ParamTagValueNode:
                    $args = [
                        new Node\Arg(
                            value: new Scalar\String_((string)($tagValueNode->type)),
                            name: new Node\Identifier(substr($tagValueNode->parameterName, 1))
                        )
                    ];
                    $attributeComment = $tagValueNode->description;
                    break;
                case $tagValueNode instanceof PropertyTagValueNode:
                    $args = [
                        new Node\Arg(
                            value: new Scalar\String_((string)($tagValueNode->type)),
                            name: new Node\Identifier(substr($tagValueNode->propertyName, 1))
                        )
                    ];
                    $attributeComment = $tagValueNode->description;
                    break;
                case $tagValueNode instanceof ExtendsTagValueNode:
                case $tagValueNode instanceof ImplementsTagValueNode:
                case $tagValueNode instanceof MixinTagValueNode:
                case $tagValueNode instanceof RequireExtendsTagValueNode:
                case $tagValueNode instanceof RequireImplementsTagValueNode:
                case $tagValueNode instanceof ReturnTagValueNode:
                case $tagValueNode instanceof SelfOutTagValueNode:
                case $tagValueNode instanceof UsesTagValueNode:
                case $tagValueNode instanceof VarTagValueNode:
                    $args = [
                        new Node\Arg(new Scalar\String_((string)($tagValueNode->type)))
                    ];
                    $attributeComment = $tagValueNode->description;
                    break;
                case $tagValueNode instanceof TemplateTagValueNode:
                    $args = [
                        new Node\Arg(new Scalar\String_($tagValueNode->name))
                    ];
                    if ($tagValueNode->bound instanceof IdentifierTypeNode) {
                        $args[] = new Node\Arg(new Scalar\String_($tagValueNode->bound->name));
                    }
                    $attributeComment = $tagValueNode->description;
                    break;
                case $tagValueNode instanceof DeprecatedTagValueNode:
                case $tagValueNode instanceof GenericTagValueNode:
                    $args = [];
                    if ($phpDocChildNode->name === '@psalm-internal') {
                        $remainingText = (string)$tagValueNode;
                        $parts = explode(' ', $remainingText);
                        $namespace = array_shift($parts);
                        if ($namespace) {
                            $args[] = new Node\Arg(new Scalar\String_($namespace));
                            $attributeComment = implode(' ', $parts);
                        }
                    } else {
                        $attributeComment = (string)$tagValueNode;
                    }
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
            $attributeGroup = new AttributeGroup([$attribute]);
            if ($attributeComment && defined('Rector\NodeTypeResolver\Node\AttributeKey::ATTRIBUTE_COMMENT')) {
                $attributeGroup->setAttribute(AttributeKey::ATTRIBUTE_COMMENT, $attributeComment);
            }
            $attributeGroups[] = $attributeGroup;
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
        if (str_starts_with($tagName, '@')) {
            $tagName = substr($tagName, 1);
            if (str_starts_with($tagName, 'psalm-')) {
                $tagName = substr($tagName, 6);
            } elseif (str_starts_with($tagName, 'phpstan-')) {
                $tagName = substr($tagName, 8);
            }
            if (isset($this->annotationsToAttributes[$tagName])) {
                return $this->annotationsToAttributes[$tagName];
            }
        }

        return null;
    }
}
