<?php

declare(strict_types=1);

namespace PhpStaticAnalysis\RectorRule;

use PhpParser\Node;
use PhpParser\Node\Arg;
use PhpParser\Node\Attribute;
use PhpParser\Node\AttributeGroup;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Identifier;
use PhpParser\Node\Name\FullyQualified;
use PhpParser\Node\Scalar;
use PhpParser\Node\Scalar\String_;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassConst;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Function_;
use PhpParser\Node\Stmt\Interface_;
use PhpParser\Node\Stmt\Trait_;
use PhpParser\Node\Stmt\TraitUse;
use PHPStan\PhpDocParser\Ast\PhpDoc\AssertTagMethodValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\AssertTagPropertyValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\AssertTagValueNode;
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
use PHPStan\PhpDocParser\Ast\PhpDoc\ThrowsTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\TypeAliasImportTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\TypeAliasTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\UsesTagValueNode;
use PHPStan\PhpDocParser\Ast\PhpDoc\VarTagValueNode;
use PHPStan\PhpDocParser\Ast\Type\IdentifierTypeNode;
use PhpStaticAnalysis\Attributes\Assert;
use PhpStaticAnalysis\Attributes\AssertIfFalse;
use PhpStaticAnalysis\Attributes\AssertIfTrue;
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

    private bool $addAssertAttributeOnParameters = false;

    private bool $useTypeAttributeForReturnAnnotation = false;

    private bool $usePropertyAttributeForVarAnnotation = false;

    private bool $useTypeAttributeForTypeClassAnnotation = false;

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
    #[Param(configuration: '(AnnotationToAttribute|bool|string[])[]')]
    public function configure(array $configuration): void
    {
        $excludedAnnotations = [];
        foreach ($configuration as $key => $value) {
            if ($value instanceof AnnotationToAttribute) {
                $tag = str_replace('_', '-', $value->getTag());
                $this->annotationsToAttributes[$tag] = $value;
            } elseif (is_bool($value) && $key == 'addParamAttributeOnParameters') {
                $this->addParamAttributeOnParameters = $value;
            } elseif (is_bool($value) && $key == 'addAssertAttributeOnParameters') {
                $this->addAssertAttributeOnParameters = $value;
            } elseif (is_bool($value) && $key == 'useTypeAttributeForReturnAnnotation') {
                $this->useTypeAttributeForReturnAnnotation = $value;
            } elseif (is_bool($value) && $key == 'usePropertyAttributeForVarAnnotation') {
                $this->usePropertyAttributeForVarAnnotation = $value;
            } elseif (is_bool($value) && $key == 'useTypeAttributeForTypeClassAnnotation') {
                $this->useTypeAttributeForTypeClassAnnotation = $value;
            } elseif (is_array($value) && $key == 'excludeAnnotations') {
                $excludedAnnotations = $value;
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
        foreach ($excludedAnnotations as $excludedAnnotation) {
            if (isset($this->annotationsToAttributes[$excludedAnnotation])) {
                unset($this->annotationsToAttributes[$excludedAnnotation]);
            }
        }
    }

    #[Returns('array<class-string<Node>>')]
    public function getNodeTypes(): array
    {
        return [
            Class_::class,
            ClassConst::class,
            ClassMethod::class,
            Function_::class,
            Interface_::class,
            Stmt\Property::class,
            Trait_::class
        ];
    }

    /**
     * @psalm-suppress MoreSpecificImplementedParamType
     */
    #[Param(node: 'Stmt\Class_|Stmt\ClassConst|Stmt\ClassMethod|Stmt\Function_|Stmt\Interface_|Stmt\Property|Stmt\Trait_')]
    public function refactor(Node $node): ?Node
    {
        $hasChanged = false;
        $phpDocInfo = $this->phpDocInfoFactory->createFromNode($node);

        $attributeGroups = [];
        if ($phpDocInfo instanceof PhpDocInfo) {
            $attributeGroups = $this->processAnnotations($phpDocInfo);
        }

        if ($attributeGroups !== []) {
            $hasChanged = true;
            $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($node);

            $this->attributeGroupNamedArgumentManipulator->decorate($attributeGroups);
        }

        if (($this->addParamAttributeOnParameters || $this->addAssertAttributeOnParameters) &&
            ($node instanceof ClassMethod || $node instanceof Function_)) {
            foreach ($attributeGroups as $attrKey => $attributeGroup) {
                foreach ($attributeGroup->attrs as $key => $attribute) {
                    $attributeName = (string)$attribute->name;
                    if (
                        (($attributeName === Param::class || $attributeName === ParamOut::class)
                        && $this->addParamAttributeOnParameters) ||
                        (($attributeName === Assert::class || $attributeName === AssertIfFalse::class || $attributeName === AssertIfTrue::class)
                        && $this->addAssertAttributeOnParameters)
                    ) {
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

                                    $hasChanged = true;
                                }
                            }
                        }
                    }
                }
                if ($attributeGroup->attrs === []) {
                    unset($attributeGroups[$attrKey]);
                    $hasChanged = true;
                }
            }
        }

        if ($node instanceof Class_) {
            foreach ($node->stmts as $stmt) {
                if ($stmt instanceof TraitUse) {
                    $phpDocInfo = $this->phpDocInfoFactory->createFromNode($stmt);
                    if ($phpDocInfo instanceof PhpDocInfo) {
                        $useAttributeGroups = $this->processAnnotations($phpDocInfo);

                        if ($useAttributeGroups !== []) {
                            $this->docBlockUpdater->updateRefactoredNodeWithPhpDocInfo($stmt);

                            $this->attributeGroupNamedArgumentManipulator->decorate($useAttributeGroups);
                            $attributeGroups = array_merge($attributeGroups, $useAttributeGroups);

                            $hasChanged = true;
                        }
                    }
                }
            }
        }

        if ($attributeGroups !== []) {
            $node->attrGroups = array_merge($node->attrGroups, $attributeGroups);
            $hasChanged = true;
        }

        if (! $hasChanged) {
            return null;
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
                        new Arg(new String_($methodSignature))
                    ];
                    break;
                case $tagValueNode instanceof ParamOutTagValueNode:
                case $tagValueNode instanceof ParamTagValueNode:
                    $args = [
                        new Arg(
                            value: new String_((string)($tagValueNode->type)),
                            name: new Identifier(substr($tagValueNode->parameterName, 1))
                        )
                    ];
                    $attributeComment = $tagValueNode->description;
                    break;
                case $tagValueNode instanceof PropertyTagValueNode:
                    $args = [
                        new Arg(
                            value: new String_((string)($tagValueNode->type)),
                            name: new Identifier(substr($tagValueNode->propertyName, 1))
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
                case $tagValueNode instanceof ThrowsTagValueNode:
                case $tagValueNode instanceof UsesTagValueNode:
                case $tagValueNode instanceof VarTagValueNode:
                    $args = [
                        new Arg(new String_((string)($tagValueNode->type)))
                    ];
                    $attributeComment = $tagValueNode->description;
                    break;
                case $tagValueNode instanceof TemplateTagValueNode:
                    $args = [
                        new Arg(new String_($tagValueNode->name))
                    ];
                    if ($tagValueNode->bound instanceof IdentifierTypeNode) {
                        $args[] = new Arg(new String_($tagValueNode->bound->name));
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
                            $args[] = new Arg(new String_($namespace));
                            $attributeComment = implode(' ', $parts);
                        }
                    } else {
                        $attributeComment = (string)$tagValueNode;
                    }
                    break;
                case $tagValueNode instanceof TypeAliasTagValueNode:
                    if ($this->useTypeAttributeForTypeClassAnnotation) {
                        $alias = (string)($tagValueNode);
                        $args = [
                            new Arg(new String_($alias))
                        ];
                    } else {
                        $args = [
                            new Arg(
                                value: new String_((string)($tagValueNode->type)),
                                name: new Identifier($tagValueNode->alias)
                            )
                        ];
                    }
                    break;
                case $tagValueNode instanceof TypeAliasImportTagValueNode:
                    $args = [
                        new Arg(
                            value: new String_((string)($tagValueNode->importedFrom)),
                            name: new Identifier($tagValueNode->importedAlias)
                        )
                    ];
                    break;
                case $tagValueNode instanceof AssertTagValueNode:
                case $tagValueNode instanceof AssertTagPropertyValueNode:
                case $tagValueNode instanceof AssertTagMethodValueNode:
                    $type = (string)($tagValueNode->type);
                    if ($tagValueNode->isNegated) {
                        $type = '!' . $type;
                    }
                    if ($tagValueNode->isEquality) {
                        $type = '=' . $type;
                    }
                    if ($tagValueNode instanceof AssertTagValueNode) {
                        $args = [
                            new Arg(
                                value: new String_($type),
                                name: new Identifier(substr($tagValueNode->parameter, 1))
                            )
                        ];
                    } else {
                        if ($tagValueNode instanceof AssertTagPropertyValueNode) {
                            $type .= ' ' . $tagValueNode->parameter . '->' . $tagValueNode->property;
                        } else {
                            $type .= ' ' . $tagValueNode->parameter . '->' . $tagValueNode->method . '()';
                        }
                        $args = [new Arg(new String_($type))];
                    }
                    $attributeComment = $tagValueNode->description;
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
            if ($this->useTypeAttributeForTypeClassAnnotation && $tagName == 'type') {
                $tagName = 'var';
            }
            if (isset($this->annotationsToAttributes[$tagName])) {
                return $this->annotationsToAttributes[$tagName];
            }
        }

        return null;
    }
}
