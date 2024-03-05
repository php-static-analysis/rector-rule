<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @method string getString()
 * @method string getName() used to get the name
 * @psalm-method void setString(string $text)
 * @phpstan-method static string staticGetter()
 */
#[Template('T')]
class MethodAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Method;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[Method('string getString()')]
#[Method('string getName()')] // used to get the name
#[Method('void setString(string $text)')]
#[Method('static string staticGetter()')]
class MethodAttributeTest
{
}

?>
