<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

class PureAttributeTest
{
    /**
     * @pure
     */
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     * @pure
     */
    public function getMoreNames(): void
    {
    }

    /**
     * @pure
     */
    #[Param(name:'string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @pure this function is pure
     */
    public function getUserName(): void
    {
    }

    /**
     * @psalm-pure
     */
    public function getPsalmName(): void
    {
    }

    /**
     * @phpstan-pure
     */
    public function getPHPStanName(): void
    {
    }
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

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

    #[Param(name:'string')]
    #[Pure]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Pure] // this function is pure
    public function getUserName(): void
    {
    }

    #[Pure]
    public function getPsalmName(): void
    {
    }

    #[Pure]
    public function getPHPStanName(): void
    {
    }
}

?>
