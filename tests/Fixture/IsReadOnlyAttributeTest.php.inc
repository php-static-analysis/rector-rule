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

use PhpStaticAnalysis\Attributes\IsReadOnly;
use PhpStaticAnalysis\Attributes\Type;

class IsReadOnlyAttributeTest
{
    #[IsReadOnly]
    public $name;

    /**
     * @codeCoverageIgnore
     */
    #[IsReadOnly]
    public $anotherName;

    #[Type('string')]
    #[IsReadOnly]
    public $otherName;

    #[IsReadOnly] // please do not write here
    public $nameWithComment;

    #[IsReadOnly]
    public $psalmName;

    #[IsReadOnly]
    public $phpstanName;
}

?>
