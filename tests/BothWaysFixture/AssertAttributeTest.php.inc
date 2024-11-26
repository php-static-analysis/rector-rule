<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Assert;
use PhpStaticAnalysis\Attributes\Returns;

class AssertAttributeTest
{
    #[Assert(name: 'string')]
    public function checkName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert(name: '!string')]
    public function checkNegatedName($name)
    {
        if (is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert(name: '=string')]
    public function checkEqualityName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert('string $this->item')]
    public function checkPropertyName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert('string $this->getName()')]
    public function checkMethodName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @codeCoverageIgnore
     */
    #[Assert(name: 'string')]
    public function checkMoreNames($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Returns('string')]
    #[Assert(name: 'string')]
    public function checkAnotherName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert(name1: 'string')]
    #[Assert(name2: 'string')]
    public function checkTwoNames($name1, $name2)
    {
        if (!is_string($name1) && !is_string($name2)) {
            throw new Exception();
        }
    }

    #[Assert(name: 'string')]
    public function checkUserName($name) // the name of the user
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }
}

#[Assert(name: 'string')]
function checkName($name)
{
    if (!is_string($name)) {
        throw new Exception();
    }
}
