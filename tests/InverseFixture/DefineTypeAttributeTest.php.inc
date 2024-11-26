<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\DefineType;

/**
 * @codeCoverageIgnore
 */
#[DefineType(StringArray: 'string[]')]
class DefineTypeAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\DefineType;

/**
 * @codeCoverageIgnore
 * @phpstan-type StringArray string[]
 */
class DefineTypeAttributeTest
{
}

?>
