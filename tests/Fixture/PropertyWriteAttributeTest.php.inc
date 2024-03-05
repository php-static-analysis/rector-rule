<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @property-write string $name
 * @property-write string $userName the name of the user
 * @psalm-property-write int $num
 * @phpstan-property-write string[] $index
 */
#[Template('T')]
class PropertyWriteAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\PropertyWrite;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[PropertyWrite(name: 'string')]
#[PropertyWrite(userName: 'string')] // the name of the user
#[PropertyWrite(num: 'int')]
#[PropertyWrite(index: 'string[]')]
class PropertyWriteAttributeTest
{
}

?>
