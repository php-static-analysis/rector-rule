<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\ImportType;

/**
 * @codeCoverageIgnore
 */
#[ImportType(StringArray: 'StringClass')]
class ImportTypeAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\ImportType;

/**
 * @codeCoverageIgnore
 * @phpstan-import-type StringArray from StringClass
 */
class ImportTypeAttributeTest
{
}

?>
