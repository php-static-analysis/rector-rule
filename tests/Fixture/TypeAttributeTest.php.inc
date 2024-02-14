<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\IsReadOnly;

class TypeAttributeTest
{
    /**
     * @var string
     */
    public $name;

    /**
     * @deprecated
     * @var string
     */
    public $anotherName;

    /**
     * @var string
     */
    #[IsReadOnly]
    public $otherName;

    /**
     * @psalm-var string
     */
    public $psalmName;

    /**
     * @phpstan-var string
     */
    public $phpstanName;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\IsReadOnly;

class TypeAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $name;

    /**
     * @deprecated
     */
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $anotherName;

    #[IsReadOnly]
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $otherName;

    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $psalmName;

    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $phpstanName;
}

?>
