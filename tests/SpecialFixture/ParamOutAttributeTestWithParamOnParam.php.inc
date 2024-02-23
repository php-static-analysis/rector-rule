<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Returns;

class ParamOutAttributeTestWithParamOnParam
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
    #[Returns('string')]
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

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Returns;

class ParamOutAttributeTestWithParamOnParam
{
    public function setName(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name)
    {
        $name = '';
    }

    /**
     * @codeCoverageIgnore
     */
    public function setMoreNames(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name)
    {
        $name = '';
    }

    #[Returns('string')]
    public function setAnotherName(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name)
    {
        $name = '';
    }

    public function setTwoNames(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name1, #[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    #[ParamOut(name1: 'string')]
    public function setTwoMoreNames(&$name1, #[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name2)
    {
        $name1 = '';
        $name2 = '';
    }

    public function setPsalmName(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name)
    {
        $name = '';
    }

    public function setPHPStanName(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
    &$name)
    {
        $name = '';
    }
}

function setName(#[\PhpStaticAnalysis\Attributes\ParamOut('string')]
&$name)
{
    $name = '';
}

?>
