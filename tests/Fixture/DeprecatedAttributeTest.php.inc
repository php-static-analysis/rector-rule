<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

/**
 * @deprecated
 */
class DeprecatedAttributeTest
{
    /**
     * @deprecated
     */
    public const NAME = 'name';

    /**
     * @deprecated
     */
    public string $name = '';

    /**
     * @deprecated
     */
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     * @deprecated
     */
    public function getMoreNames(): void
    {
    }

    /**
     * @deprecated
     */
    #[Param(name:'string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @deprecated use getNewUserName() instead
     */
    public function getUserName(): void
    {
    }

    /**
     * @psalm-deprecated
     */
    public function getPsalmName(): void
    {
    }

    /**
     * @phpstan-deprecated
     */
    public function getPHPStanName(): void
    {
    }
}

/**
 * @deprecated
 */
function getName(): void
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

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

    #[Param(name:'string')]
    #[Deprecated]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Deprecated] // use getNewUserName() instead
    public function getUserName(): void
    {
    }

    #[Deprecated]
    public function getPsalmName(): void
    {
    }

    #[Deprecated]
    public function getPHPStanName(): void
    {
    }
}

#[Deprecated]
function getName(): void
{
}

?>
