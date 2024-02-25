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

use PhpStaticAnalysis\Attributes\Param;

class PureAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Pure]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\Pure]
    public function getMoreNames(): void
    {
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\Pure]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[\PhpStaticAnalysis\Attributes\Pure] // this function is pure
    public function getUserName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Pure]
    public function getPsalmName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Pure]
    public function getPHPStanName(): void
    {
    }
}

?>
