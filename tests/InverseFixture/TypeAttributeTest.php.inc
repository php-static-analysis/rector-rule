<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\IsReadOnly;
use PhpStaticAnalysis\Attributes\Type;

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
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\IsReadOnly;
use PhpStaticAnalysis\Attributes\Type;

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
     * @readonly
     * @var string
     */
    public $otherName;

    /**
     * @var string
     */
    public $userName;
}

?>
