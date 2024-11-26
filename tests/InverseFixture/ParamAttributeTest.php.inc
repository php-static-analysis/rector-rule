<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTest
{
    #[Param(name: 'string')]
    public function getName($name)
    {
        return $name;
    }

    /**
     * @codeCoverageIgnore
     */
    #[Param(name: 'string')]
    public function getMoreNames($name)
    {
        return $name;
    }

    #[Returns('string')]
    #[Param(name: 'string')]
    public function getAnotherName($name)
    {
        return $name;
    }

    #[Param(name1: 'string')]
    #[Param(name2: 'string')]
    public function getTwoNames($name1, $name2)
    {
        return $name1 . $name2;
    }

    #[Param(name: 'string')] // the name of the user
    public function getUserName($name)
    {
        return $name;
    }
}

#[Param(name: 'string')]
function getName($name)
{
    return $name;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTest
{
    /**
     * @param string $name
     */
    public function getName($name)
    {
        return $name;
    }

    /**
     * @codeCoverageIgnore
     * @param string $name
     */
    public function getMoreNames($name)
    {
        return $name;
    }

    /**
     * @return string
     * @param string $name
     */
    public function getAnotherName($name)
    {
        return $name;
    }

    /**
     * @param string $name1
     * @param string $name2
     */
    public function getTwoNames($name1, $name2)
    {
        return $name1 . $name2;
    }

    /**
     * @param string $name
     */
    public function getUserName($name)
    {
        return $name;
    }
}

/**
 * @param string $name
 */
function getName($name)
{
    return $name;
}

?>
