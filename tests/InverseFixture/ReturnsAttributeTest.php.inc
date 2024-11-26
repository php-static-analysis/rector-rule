<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
}

#[Returns('string')]
function getName()
{
    return "Ann";
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

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
     * @param string $name
     * @return string
     */
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @return string
     */
    public function getUserName()
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
