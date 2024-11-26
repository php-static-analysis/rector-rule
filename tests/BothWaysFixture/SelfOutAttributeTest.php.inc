<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

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

    #[Param(name: 'string')]
    #[SelfOut('self<T>')]
    public function addAnother()
    {
    }

    #[SelfOut('self<T>')] // this is the new type
    public function addUserName()
    {
    }
}
