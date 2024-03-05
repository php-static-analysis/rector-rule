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

use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\Attributes\IsReadOnly;

class TypeAttributeTest
{
    #[Type('string')]
    public $name;

    /**
     * @codeCoverageIgnore
     */
    #[Type('string')]
    public $anotherName;

    #[IsReadOnly]
    #[Type('string')]
    public $otherName;

    #[Type('string')] // this is the name of the user
    public $userName;

    #[Type('string')] // this is also the name of the user
    public $otherUserName;

    #[Type('string')]
    public $psalmName;

    #[Type('string')]
    public $phpstanName;
}

?>
