<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Type;

class IsReadOnlyAttributeTest
{
    /**
     * @readonly
     */
    public $name;

    /**
     * @codeCoverageIgnore
     * @readonly
     */
    public $anotherName;

    /**
     * @readonly
     */
    #[Type('string')]
    public $otherName;

    /**
     * @readonly please do not write here
     */
    public $nameWithComment;

    /**
     * @psalm-readonly
     */
    public $psalmName;

    /**
     * @phpstan-readonly
     */
    public $phpstanName;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Type;

class IsReadOnlyAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $name;

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $anotherName;

    #[Type('string')]
    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $otherName;

    #[\PhpStaticAnalysis\Attributes\IsReadOnly] // please do not write here
    public $nameWithComment;

    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $psalmName;

    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $phpstanName;
}

?>
