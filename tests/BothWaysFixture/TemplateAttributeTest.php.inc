<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Template;

#[Template('T')]
class TemplateAttributeTest
{
    #[Template('T')]
    public function getName()
    {
        return 'John';
    }

    #[Template('T', 'object')]
    public function getExtraName()
    {
        return 'John';
    }

    /**
     * @codeCoverageIgnore
     */
    #[Template('T')]
    public function getMoreNames()
    {
        return 'Mike';
    }

    #[Param(name: 'string')]
    #[Template('T')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Template('T')] // the type of object
    public function getUserName()
    {
        return 'John';
    }

    #[Template('T', 'object')] // the type of object
    public function getAnotherUserName()
    {
        return 'John';
    }
}

#[Template('T')]
function getName()
{
    return "Ann";
}
