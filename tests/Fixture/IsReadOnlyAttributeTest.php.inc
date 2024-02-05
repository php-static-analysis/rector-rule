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
}

?>
