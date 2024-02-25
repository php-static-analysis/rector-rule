<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

class ImpureAttributeTest
{
    /**
     * @impure
     */
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     * @impure
     */
    public function getMoreNames(): void
    {
    }

    /**
     * @impure
     */
    #[Param(name:'string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @impure this function is impure
     */
    public function getUserName(): void
    {
    }

    /**
     * @phpstan-impure
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

class ImpureAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Impure]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\Impure]
    public function getMoreNames(): void
    {
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\Impure]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[\PhpStaticAnalysis\Attributes\Impure] // this function is impure
    public function getUserName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Impure]
    public function getPHPStanName(): void
    {
    }
}

?>
