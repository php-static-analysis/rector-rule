<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Deprecated;
use PhpStaticAnalysis\Attributes\Param;

#[Deprecated]
class DeprecatedAttributeTest
{
    #[Deprecated]
    public const NAME = 'name';

    #[Deprecated]
    public string $name = '';

    #[Deprecated]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[Deprecated]
    public function getMoreNames(): void
    {
    }

    #[Param(name: 'string')]
    #[Deprecated]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Deprecated] // use getNewUserName() instead
    public function getUserName(): void
    {
    }
}

#[Deprecated]
function getName(): void
{
}

