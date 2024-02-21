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

use PhpStaticAnalysis\Attributes\Param;

#[\PhpStaticAnalysis\Attributes\Deprecated]
class DeprecatedAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public const NAME = 'name';

    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public string $name = '';

    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public function getMoreNames(): void
    {
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[\PhpStaticAnalysis\Attributes\Deprecated] // use getNewUserName() instead
    public function getUserName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public function getPsalmName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Deprecated]
    public function getPHPStanName(): void
    {
    }
}

#[\PhpStaticAnalysis\Attributes\Deprecated]
function getName(): void
{
}

?>
