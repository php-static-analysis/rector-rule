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

    /**
     * @template T the type of object
     */
    public function getUserName()
    {
        return 'John';
    }

    /**
     * @template T of object the type of object
     */
    public function getAnotherUserName()
    {
        return 'John';
    }

    /**
     * @psalm-template T
     */
    public function getPsalmName()
    {
        return 'John';
    }

    /**
     * @phpstan-template T
     */
    public function getPHPStanName()
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

    #[\PhpStaticAnalysis\Attributes\Template('T')] // the type of object
    public function getUserName()
    {
        return 'John';
    }

    #[\PhpStaticAnalysis\Attributes\Template('T', 'object')] // the type of object
    public function getAnotherUserName()
    {
        return 'John';
    }

    #[\PhpStaticAnalysis\Attributes\Template('T')]
    public function getPsalmName()
    {
        return 'John';
    }

    #[\PhpStaticAnalysis\Attributes\Template('T')]
    public function getPHPStanName()
    {
        return 'John';
    }
}

#[\PhpStaticAnalysis\Attributes\Template('T')]
function getName()
{
    return "Ann";
}

?>
