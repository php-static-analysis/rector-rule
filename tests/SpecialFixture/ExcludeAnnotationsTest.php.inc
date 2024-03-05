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

use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\Type;
use Exception;

/**
 * @deprecated
 */
#[Template('T')]
class ExcludeAnnotationsTest
{
    #[Type('string')]
    public $name;

    /**
     * @throws Exception
     */
    public function throwsException()
    {
    }
}

?>
