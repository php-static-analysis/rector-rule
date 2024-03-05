<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Returns;

class ParamOutAttributeTest
{
    /**
     * @param-out string $name
     */
    public function setName(&$name)
    {
        $name = '';
    }

    /**
     * @codeCoverageIgnore
     * @param-out string $name
     */
    public function setMoreNames(&$name)
    {
        $name = '';
    }

    /**
     * @param-out string $name
     */
    #[Returns('void')]
    public function setAnotherName(&$name)
    {
        $name = '';
    }

    /**
     * @param-out string $name1
     * @param-out string $name2
     */
    public function setTwoNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    /**
     * @param-out string $name2
     */
    #[ParamOut(name1: 'string')]
    public function setTwoMoreNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    /**
     * @param-out string $name the name of the user
     */
    public function setUserName(&$name)
    {
        $name = '';
    }

    /**
     * @psalm-param-out string $name
     */
    public function setPsalmName(&$name)
    {
        $name = '';
    }

    /**
     * @phpstan-param-out string $name
     */
    public function setPHPStanName(&$name)
    {
        $name = '';
    }
}

/**
 * @param-out string $name
 */
function setName(&$name)
{
    $name = '';
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Returns;

class ParamOutAttributeTest
{
    #[ParamOut(name: 'string')]
    public function setName(&$name)
    {
        $name = '';
    }

    /**
     * @codeCoverageIgnore
     */
    #[ParamOut(name: 'string')]
    public function setMoreNames(&$name)
    {
        $name = '';
    }

    #[Returns('void')]
    #[ParamOut(name: 'string')]
    public function setAnotherName(&$name)
    {
        $name = '';
    }

    #[ParamOut(name1: 'string')]
    #[ParamOut(name2: 'string')]
    public function setTwoNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    #[ParamOut(name1: 'string')]
    #[ParamOut(name2: 'string')]
    public function setTwoMoreNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    #[ParamOut(name: 'string')] // the name of the user
    public function setUserName(&$name)
    {
        $name = '';
    }

    #[ParamOut(name: 'string')]
    public function setPsalmName(&$name)
    {
        $name = '';
    }

    #[ParamOut(name: 'string')]
    public function setPHPStanName(&$name)
    {
        $name = '';
    }
}

#[ParamOut(name: 'string')]
function setName(&$name)
{
    $name = '';
}

?>
