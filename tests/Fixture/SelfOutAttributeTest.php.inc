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

use PhpStaticAnalysis\Attributes\Param;

class SelfOutAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\SelfOut('self<T>')]
    public function add()
    {
    }

    #[\PhpStaticAnalysis\Attributes\SelfOut('self<T>')]
    public function addThis()
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\SelfOut('self<T>')]
    public function addMore()
    {
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\SelfOut('self<T>')]
    public function addAnother()
    {
    }

    #[\PhpStaticAnalysis\Attributes\SelfOut('self<T>')] // this is the new type
    public function addUserName()
    {
    }

    #[\PhpStaticAnalysis\Attributes\SelfOut('self<T>')]
    public function addPsalm()
    {
    }
}

?>
