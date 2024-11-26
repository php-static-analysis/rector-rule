<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ReturnsAttributeTest
{
    #[Returns('string')]
    public function getName()
    {
        return 'John';
    }

    /**
     * @codeCoverageIgnore
     */
    #[Returns('string')]
    public function getMoreNames()
    {
        return 'Mike';
    }

    #[Param(name: 'string')]
    #[Returns('string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Returns('string')] // the name of the user
    public function getUserName()
    {
        return 'John';
    }
}

#[Returns('string')]
function getName()
{
    return "Ann";
}
