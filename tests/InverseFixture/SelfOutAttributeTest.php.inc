<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\SelfOut;

class SelfOutAttributeTest
{
    #[SelfOut('self<T>')]
    public function add()
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[SelfOut('self<T>')]
    public function addMore()
    {
    }

    #[Param(name:'string')]
    #[SelfOut('self<T>')]
    public function addAnother()
    {
    }

    #[SelfOut('self<T>')] // this is the new type
    public function addUserName()
    {
    }
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\SelfOut;

class SelfOutAttributeTest
{
    /**
     * @phpstan-self-out self<T>
     */
    public function add()
    {
    }

    /**
     * @codeCoverageIgnore
     * @phpstan-self-out self<T>
     */
    public function addMore()
    {
    }

    /**
     * @param string $name
     * @phpstan-self-out self<T>
     */
    public function addAnother()
    {
    }

    /**
     * @phpstan-self-out self<T>
     */
    public function addUserName()
    {
    }
}

?>
