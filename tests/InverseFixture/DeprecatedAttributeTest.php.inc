<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
}

#[Deprecated]
function getName(): void
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Deprecated;
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
     * @param string $name
     * @deprecated
     */
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }
    /**
     * @deprecated
     */
    public function getUserName(): void
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
