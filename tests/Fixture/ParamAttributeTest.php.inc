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
     * @deprecated
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

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Param(name: 'string')]
    public function getName($name)
    {
        return $name;
    }

    /**
     * @deprecated
     */
    #[\PhpStaticAnalysis\Attributes\Param(name: 'string')]
    public function getMoreNames($name)
    {
        return $name;
    }

    #[Returns('string')]
    #[\PhpStaticAnalysis\Attributes\Param(name: 'string')]
    public function getAnotherName($name)
    {
        return $name;
    }

    #[\PhpStaticAnalysis\Attributes\Param(name1: 'string')]
    #[\PhpStaticAnalysis\Attributes\Param(name2: 'string')]
    public function getTwoNames($name1, $name2)
    {
        return $name1 . $name2;
    }

    #[Param(name1: 'string')]
    #[\PhpStaticAnalysis\Attributes\Param(name2: 'string')]
    public function getTwoMoreNames($name1, $name2)
    {
        return $name1 . $name2;
    }

    #[\PhpStaticAnalysis\Attributes\Param(name: 'string')]
    public function getPsalmName($name)
    {
        return $name;
    }

    #[\PhpStaticAnalysis\Attributes\Param(name: 'string')]
    public function getPHPStanName($name)
    {
        return $name;
    }
}

#[\PhpStaticAnalysis\Attributes\Param(name: 'string')]
function getName($name)
{
    return $name;
}

?>
