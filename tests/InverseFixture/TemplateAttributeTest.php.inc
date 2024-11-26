<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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

    #[Param(name:'string')]
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

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @template T
 */
class TemplateAttributeTest
{
    /**
     * @template T
     */
    public function getName()
    {
        return 'John';
    }
    /**
     * @template T of object
     */
    public function getExtraName()
    {
        return 'John';
    }
    /**
     * @codeCoverageIgnore
     * @template T
     */
    public function getMoreNames()
    {
        return 'Mike';
    }
    /**
     * @param string $name
     * @template T
     */
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }
    /**
     * @template T
     */
    public function getUserName()
    {
        return 'John';
    }
    /**
     * @template T of object
     */
    public function getAnotherUserName()
    {
        return 'John';
    }
}

/**
 * @template T
 */
function getName()
{
    return "Ann";
}

?>
