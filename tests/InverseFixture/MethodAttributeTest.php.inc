<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Method;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[Method('string getString()')]
#[Method('string getName()')] // used to get the name
class MethodAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Method;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @template T
 * @method string getString()
 * @method string getName()
 */
class MethodAttributeTest
{
}

?>
