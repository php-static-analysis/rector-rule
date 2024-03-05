<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @property-read string $name
 * @property-read string $userName the name of the user
 * @psalm-property-read int $num
 * @phpstan-property-read string[] $index
 */
#[Template('T')]
class PropertyReadAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\PropertyRead;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[PropertyRead(name: 'string')]
#[PropertyRead(userName: 'string')] // the name of the user
#[PropertyRead(num: 'int')]
#[PropertyRead(index: 'string[]')]
class PropertyReadAttributeTest
{
}

?>
