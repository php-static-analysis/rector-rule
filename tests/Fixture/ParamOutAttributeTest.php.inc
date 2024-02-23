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
    #[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')]
    public function setName(&$name)
    {
        $name = '';
    }

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')]
    public function setMoreNames(&$name)
    {
        $name = '';
    }

    #[Returns('void')]
    #[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')]
    public function setAnotherName(&$name)
    {
        $name = '';
    }

    #[\PhpStaticAnalysis\Attributes\ParamOut(name1: 'string')]
    #[\PhpStaticAnalysis\Attributes\ParamOut(name2: 'string')]
    public function setTwoNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    #[ParamOut(name1: 'string')]
    #[\PhpStaticAnalysis\Attributes\ParamOut(name2: 'string')]
    public function setTwoMoreNames(&$name1, &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    #[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')] // the name of the user
    public function setUserName(&$name)
    {
        $name = '';
    }

    #[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')]
    public function setPsalmName(&$name)
    {
        $name = '';
    }

    #[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')]
    public function setPHPStanName(&$name)
    {
        $name = '';
    }
}

#[\PhpStaticAnalysis\Attributes\ParamOut(name: 'string')]
function setName(&$name)
{
    $name = '';
}

?>
