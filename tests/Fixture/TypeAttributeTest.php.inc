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
     * @codeCoverageIgnore
     * @var string
     */
    public $anotherName;

    /**
     * @var string
     */
    #[IsReadOnly]
    public $otherName;

    /**
     * @var string this is the name of the user
     */
    public $userName;

    /**
     * @var string $otherUserName this is also the name of the user
     */
    public $otherUserName;

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
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $anotherName;

    #[IsReadOnly]
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $otherName;

    #[\PhpStaticAnalysis\Attributes\Type('string')] // this is the name of the user
    public $userName;

    #[\PhpStaticAnalysis\Attributes\Type('string')] // this is also the name of the user
    public $otherUserName;

    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $psalmName;

    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $phpstanName;
}

?>
