<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
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

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
 */
#[Template('T')]
#[\PhpStaticAnalysis\Attributes\PropertyRead(name: 'string')]
#[\PhpStaticAnalysis\Attributes\PropertyRead(userName: 'string')] // the name of the user
#[\PhpStaticAnalysis\Attributes\PropertyRead(num: 'int')]
#[\PhpStaticAnalysis\Attributes\PropertyRead(index: 'string[]')]
class PropertyReadAttributeTest
{
}

?>
