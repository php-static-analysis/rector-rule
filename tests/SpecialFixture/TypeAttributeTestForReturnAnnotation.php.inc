<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

class TypeAttributeTestForReturnAnnotation
{
    /**
     * @return string
     */
    public function getName()
    {
        return 'John';
    }

    /**
     * @deprecated
     * @return string
     */
    public function getMoreNames()
    {
        return 'Mike';
    }

    /**
     * @return string
     */
    #[Param(name:'string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @psalm-return string
     */
    public function getPsalmName()
    {
        return 'John';
    }

    /**
     * @phpstan-return string
     */
    public function getPHPStanName()
    {
        return 'John';
    }
}

/**
 * @return string
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

class TypeAttributeTestForReturnAnnotation
{
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public function getName()
    {
        return 'John';
    }

    /**
     * @deprecated
     */
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public function getMoreNames()
    {
        return 'Mike';
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public function getPsalmName()
    {
        return 'John';
    }

    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public function getPHPStanName()
    {
        return 'John';
    }
}

#[\PhpStaticAnalysis\Attributes\Type('string')]
function getName()
{
    return "Ann";
}

?>
