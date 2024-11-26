<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Throws;

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
}

#[Throws('Exception')]
function getName(): void
{
    throw new Exception();
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Throws;

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
     * @param string $name
     * @throws Exception
     */
    public function getAnotherName($name): void
    {
        throw new Exception();
    }

    /**
     * @throws Exception
     */
    public function getUserName(): void
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
