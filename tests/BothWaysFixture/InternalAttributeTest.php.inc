<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Internal;
use PhpStaticAnalysis\Attributes\Param;

#[Internal]
class InternalAttributeTest
{
    #[Internal]
    public const NAME = 'name';

    #[Internal]
    public string $name = '';

    #[Internal]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[Internal]
    public function getMoreNames(): void
    {
    }

    #[Param(name: 'string')]
    #[Internal]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Internal] // only available in the current namespace
    public function getUserName(): void
    {
    }

    #[Internal('A\B')]
    public function getPsalmName(): void
    {
    }

    #[Internal('A\B')] // Only available in the A\B namespace
    public function getPsalmNameWithComment(): void
    {
    }
}

#[Internal]
function getName(): void
{
}
