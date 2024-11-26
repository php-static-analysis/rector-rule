<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Returns;

class ParamOutAttributeTest
{
    #[ParamOut(name: 'string')]
    public function setName(&$name)
    {
        $name = '';
    }

    /**
     * @codeCoverageIgnore
     */
    #[ParamOut(name: 'string')]
    public function setMoreNames(&$name)
    {
        $name = '';
    }

    #[Returns('void')]
    #[ParamOut(name: 'string')]
    public function setAnotherName(&$name)
    {
        $name = '';
    }

    #[ParamOut(name1: 'string')]
    #[ParamOut(name2: 'string')]
    public function setTwoNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    #[ParamOut(name: 'string')] // the name of the user
    public function setUserName(&$name)
    {
        $name = '';
    }
}

#[ParamOut(name: 'string')]
function setName(&$name)
{
    $name = '';
}
