<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

class SelfOutAttributeTest
{
    /**
     * @phpstan-self-out self<T>
     */
    public function add()
    {
    }

    /**
     * @phpstan-this-out self<T>
     */
    public function addThis()
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
     * @phpstan-self-out self<T>
     */
    #[Param(name:'string')]
    public function addAnother()
    {
    }

    /**
     * @phpstan-self-out self<T> this is the new type
     */
    public function addUserName()
    {
    }

    /**
     * @psalm-self-out self<T>
     */
    public function addPsalm()
    {
    }
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\SelfOut;
use PhpStaticAnalysis\Attributes\Param;

class SelfOutAttributeTest
{
    #[SelfOut('self<T>')]
    public function add()
    {
    }

    #[SelfOut('self<T>')]
    public function addThis()
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

    #[SelfOut('self<T>')]
    public function addPsalm()
    {
    }
}

?>
