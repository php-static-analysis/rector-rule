<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @property string $name
 * @property string $userName the name of the user
 * @psalm-property int $num
 * @phpstan-property string[] $index
 */
#[Template('T')]
class PropertyAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[Property(name: 'string')]
#[Property(userName: 'string')] // the name of the user
#[Property(num: 'int')]
#[Property(index: 'string[]')]
class PropertyAttributeTest
{
}

?>
