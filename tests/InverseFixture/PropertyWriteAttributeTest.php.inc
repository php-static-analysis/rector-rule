<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\PropertyWrite;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[PropertyWrite(name: 'string')]
#[PropertyWrite(userName: 'string')] // the name of the user
class PropertyWriteAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\PropertyWrite;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @template T
 * @property-write string $name
 * @property-write string $userName
 */
class PropertyWriteAttributeTest
{
}

?>
