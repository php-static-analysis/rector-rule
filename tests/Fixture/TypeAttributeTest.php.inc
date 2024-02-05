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
}

?>
