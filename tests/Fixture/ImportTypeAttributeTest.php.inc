<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\ImportType;

/**
 * @codeCoverageIgnore
 * @phpstan-import-type StringArray from StringClass
 * @psalm-import-type IntArray from IntClass
 */
#[ImportType(FloatArray: FloatClass::class)]
class ImportTypeAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\ImportType;

/**
 * @codeCoverageIgnore
 */
#[ImportType(FloatArray: FloatClass::class)]
#[ImportType(StringArray: 'StringClass')]
#[ImportType(IntArray: 'IntClass')]
class ImportTypeAttributeTest
{
}

?>
