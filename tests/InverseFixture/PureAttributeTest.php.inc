<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Pure;
use PhpStaticAnalysis\Attributes\Param;

class PureAttributeTest
{
    /**
     * @phpstan-pure
     */
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     * @phpstan-pure
     */
    public function getMoreNames(): void
    {
    }

    /**
     * @param string $name
     * @phpstan-pure
     */
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @phpstan-pure
     */
    public function getUserName(): void
    {
    }
}

?>
