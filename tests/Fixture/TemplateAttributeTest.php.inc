<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

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
     * @deprecated
     * @template T
     */
    public function getMoreNames()
    {
        return 'Mike';
    }

    /**
     * @template T
     */
    #[Param(name:'string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
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
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

#[\PhpStaticAnalysis\Attributes\Template('T')]
class TemplateAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Template('T')]
    public function getName()
    {
        return 'John';
    }

    #[\PhpStaticAnalysis\Attributes\Template('T', 'object')]
    public function getExtraName()
    {
        return 'John';
    }

    /**
     * @deprecated
     */
    #[\PhpStaticAnalysis\Attributes\Template('T')]
    public function getMoreNames()
    {
        return 'Mike';
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\Template('T')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }
}

#[\PhpStaticAnalysis\Attributes\Template('T')]
function getName()
{
    return "Ann";
}

?>
