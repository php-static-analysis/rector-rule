<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Pure;
use PhpStaticAnalysis\Attributes\Param;

class PureAttributeTest
{
    #[Pure]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[Pure]
    public function getMoreNames(): void
    {
    }

    #[Param(name: 'string')]
    #[Pure]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Pure] // this function is pure
    public function getUserName(): void
    {
    }
}
