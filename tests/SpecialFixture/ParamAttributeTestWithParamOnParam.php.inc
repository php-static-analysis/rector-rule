<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTestWithParamOnParam
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
     * @param string $name
     */
    #[Returns('string')]
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
     * @param string $name2
     */
    #[Param(name1: 'string')]
    public function getTwoMoreNames($name1, $name2)
    {
        return $name1 . $name2;
    }

    /**
     * @psalm-param string $name
     */
    public function getPsalmName($name)
    {
        return $name;
    }

    /**
     * @phpstan-param string $name
     */
    public function getPHPStanName($name)
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
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTestWithParamOnParam
{
    public function getName(#[Param('string')]
    $name)
    {
        return $name;
    }

    /**
     * @codeCoverageIgnore
     */
    public function getMoreNames(#[Param('string')]
    $name)
    {
        return $name;
    }

    #[Returns('string')]
    public function getAnotherName(#[Param('string')]
    $name)
    {
        return $name;
    }

    public function getTwoNames(#[Param('string')]
    $name1, #[Param('string')]
    $name2)
    {
        return $name1 . $name2;
    }

    #[Param(name1: 'string')]
    public function getTwoMoreNames($name1, #[Param('string')]
    $name2)
    {
        return $name1 . $name2;
    }

    public function getPsalmName(#[Param('string')]
    $name)
    {
        return $name;
    }

    public function getPHPStanName(#[Param('string')]
    $name)
    {
        return $name;
    }
}

function getName(#[Param('string')]
$name)
{
    return $name;
}

?>
