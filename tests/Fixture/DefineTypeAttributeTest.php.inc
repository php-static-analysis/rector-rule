<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\DefineType;

/**
 * @codeCoverageIgnore
 * @phpstan-type StringArray string[]
 * @psalm-type IntArray int[]
 */
#[DefineType(FloatArray: 'float[]')]
class DefineTypeAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\DefineType;

/**
 * @codeCoverageIgnore
 */
#[DefineType(FloatArray: 'float[]')]
#[DefineType(StringArray: 'string[]')]
#[DefineType(IntArray: 'int[]')]
class DefineTypeAttributeTest
{
}

?>
