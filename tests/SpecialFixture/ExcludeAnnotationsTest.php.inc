<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;

/**
 * @deprecated
 * @template T
 */
class ExcludeAnnotationsTest
{
    /**
     * @var string
     */
    public $name;

    /**
     * @throws Exception
     */
    public function throwsException()
    {
    }
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;

/**
 * @deprecated
 */
#[\PhpStaticAnalysis\Attributes\Template('T')]
class ExcludeAnnotationsTest
{
    #[\PhpStaticAnalysis\Attributes\Type('string')]
    public $name;

    /**
     * @throws Exception
     */
    public function throwsException()
    {
    }
}

?>
