<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Impure;
use PhpStaticAnalysis\Attributes\Param;

class ImpureAttributeTest
{
    #[Impure]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[Impure]
    public function getMoreNames(): void
    {
    }

    #[Param(name: 'string')]
    #[Impure]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Impure] // this function is impure
    public function getUserName(): void
    {
    }
}
