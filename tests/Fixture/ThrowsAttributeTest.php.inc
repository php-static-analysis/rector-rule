<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Param;

class ThrowsAttributeTest
{
    /**
     * @throws Exception
     */
    public function getName(): void
    {
        throw new Exception();
    }

    /**
     * @codeCoverageIgnore
     * @throws Exception
     */
    public function getMoreNames(): void
    {
        throw new Exception();
    }

    /**
     * @throws Exception
     */
    #[Param(name:'string')]
    public function getAnotherName($name): void
    {
        throw new Exception();
    }

    /**
     * @throws Exception this is the exception that is thrown
     */
    public function getUserName(): void
    {
        throw new Exception();
    }

    /**
     * @phpstan-throws Exception
     */
    public function getPHPStanName(): void
    {
        throw new Exception();
    }
}

/**
 * @throws Exception
 */
function getName(): void
{
    throw new Exception();
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Throws;
use Exception;
use PhpStaticAnalysis\Attributes\Param;

class ThrowsAttributeTest
{
    #[Throws('Exception')]
    public function getName(): void
    {
        throw new Exception();
    }

    /**
     * @codeCoverageIgnore
     */
    #[Throws('Exception')]
    public function getMoreNames(): void
    {
        throw new Exception();
    }

    #[Param(name:'string')]
    #[Throws('Exception')]
    public function getAnotherName($name): void
    {
        throw new Exception();
    }

    #[Throws('Exception')] // this is the exception that is thrown
    public function getUserName(): void
    {
        throw new Exception();
    }

    #[Throws('Exception')]
    public function getPHPStanName(): void
    {
        throw new Exception();
    }
}

#[Throws('Exception')]
function getName(): void
{
    throw new Exception();
}

?>
