<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

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
