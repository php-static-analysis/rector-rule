<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Throws;

class ThrowsAttributeTest
{
    #[Throws('Exception')]
    public function getName(): void
    {
        throw new Exception();
    }

    /**
     * @codeCoverageIgnore
     */
    #[Throws('Exception')]
    public function getMoreNames(): void
    {
        throw new Exception();
    }

    #[Param(name: 'string')]
    #[Throws('Exception')]
    public function getAnotherName($name): void
    {
        throw new Exception();
    }

    #[Throws('Exception')] // this is the exception that is thrown
    public function getUserName(): void
    {
        throw new Exception();
    }
}

#[Throws('Exception')]
function getName(): void
{
    throw new Exception();
}
