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
     * @deprecated
     * @readonly
     */
    public $anotherName;

    /**
     * @readonly
     */
    #[Type('string')]
    public $otherName;

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
     * @deprecated
     */
    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $anotherName;

    #[Type('string')]
    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $otherName;

    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $psalmName;

    #[\PhpStaticAnalysis\Attributes\IsReadOnly]
    public $phpstanName;
}

?>
