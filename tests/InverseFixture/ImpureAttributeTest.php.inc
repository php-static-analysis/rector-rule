<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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

    #[Param(name:'string')]
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

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Impure;
use PhpStaticAnalysis\Attributes\Param;

class ImpureAttributeTest
{
    /**
     * @phpstan-impure
     */
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     * @phpstan-impure
     */
    public function getMoreNames(): void
    {
    }

    /**
     * @param string $name
     * @phpstan-impure
     */
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @phpstan-impure
     */
    public function getUserName(): void
    {
    }
}

?>
