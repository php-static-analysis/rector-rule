<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

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
