<?php

declare(strict_types=1);

namespace PhpStaticAnalysis\RectorRule;

use PhpParser\Node;
use PhpParser\Node\Stmt;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassConst;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\Node\Stmt\Function_;
use PhpParser\Node\Stmt\Interface_;
use PhpParser\Node\Stmt\Trait_;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\NodeVisitor\AttributeNodeVisitor;
use Rector\Contract\Rector\RectorInterface;
use Rector\Rector\AbstractRector;
use Rector\ValueObject\PhpVersion;
use Rector\ValueObject\PhpVersionFeature;
use Rector\VersionBonding\Contract\MinPhpVersionInterface;
use Symplify\RuleDocGenerator\ValueObject\CodeSample\CodeSample;
use Symplify\RuleDocGenerator\ValueObject\RuleDefinition;

final class AttributesToAnnotationsRector extends AbstractRector implements RectorInterface, MinPhpVersionInterface
{
    private AttributeNodeVisitor $nodeVisitor;

    public function __construct(
    ) {
        $this->nodeVisitor = new AttributeNodeVisitor(AttributeNodeVisitor::TOOL_PHPSTAN);
    }

    public function getRuleDefinition(): RuleDefinition
    {
        return new RuleDefinition('// Converts PHP attributes for static analysis to PHPDoc annotations', [
            new CodeSample(
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
                ,
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
            ),
        ]);
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
        $existingComments = $node->getDocComment();
        $node = $this->nodeVisitor->enterNode($node);
        assert($node instanceof Node);
        $newComments = $node->getDocComment();
        if ($newComments !== null && ($existingComments === null ||
            $newComments->getText() !== $existingComments->getText())) {
            return $node;
        }
        return null;
    }

    #[Returns('PhpVersion::PHP_80')]
    public function provideMinPhpVersion(): int
    {
        return PhpVersionFeature::ATTRIBUTES;
    }
}
