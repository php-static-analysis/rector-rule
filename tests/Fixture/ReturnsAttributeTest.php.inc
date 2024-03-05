<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

class ReturnsAttributeTest
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
     * @return string the name of the user
     */
    public function getUserName()
    {
        return 'John';
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

use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\Attributes\Param;

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

    #[Param(name:'string')]
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

    #[Returns('string')]
    public function getPsalmName()
    {
        return 'John';
    }

    #[Returns('string')]
    public function getPHPStanName()
    {
        return 'John';
    }
}

#[Returns('string')]
function getName()
{
    return "Ann";
}

?>
