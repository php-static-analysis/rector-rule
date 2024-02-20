<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
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

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
 */
#[Template('T')]
#[\PhpStaticAnalysis\Attributes\Method('string getString()')]
#[\PhpStaticAnalysis\Attributes\Method('string getName()')] // used to get the name
#[\PhpStaticAnalysis\Attributes\Method('void setString(string $text)')]
#[\PhpStaticAnalysis\Attributes\Method('static string staticGetter()')]
class MethodAttributeTest
{
}

?>
