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
     * @codeCoverageIgnore
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

use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\Attributes\Param;

class TypeAttributeTestForReturnAnnotation
{
    #[Type('string')]
    public function getName()
    {
        return 'John';
    }

    /**
     * @codeCoverageIgnore
     */
    #[Type('string')]
    public function getMoreNames()
    {
        return 'Mike';
    }

    #[Param(name:'string')]
    #[Type('string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[Type('string')]
    public function getPsalmName()
    {
        return 'John';
    }

    #[Type('string')]
    public function getPHPStanName()
    {
        return 'John';
    }
}

#[Type('string')]
function getName()
{
    return "Ann";
}

?>
