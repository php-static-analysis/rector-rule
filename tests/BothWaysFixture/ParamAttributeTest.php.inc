<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTest
{
    #[Param(name: 'string')]
    public function getName($name)
    {
        return $name;
    }

    /**
     * @codeCoverageIgnore
     */
    #[Param(name: 'string')]
    public function getMoreNames($name)
    {
        return $name;
    }

    #[Returns('string')]
    #[Param(name: 'string')]
    public function getAnotherName($name)
    {
        return $name;
    }

    #[Param(name1: 'string')]
    #[Param(name2: 'string')]
    public function getTwoNames($name1, $name2)
    {
        return $name1 . $name2;
    }

    #[Param(name: 'string')] // the name of the user
    public function getUserName($name)
    {
        return $name;
    }
}

#[Param(name: 'string')]
function getName($name)
{
    return $name;
}
