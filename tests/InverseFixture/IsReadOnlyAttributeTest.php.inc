<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\IsReadOnly;
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
     * @var string
     * @readonly
     */
    public $otherName;

    /**
     * @readonly
     */
    public $nameWithComment;
}

?>
