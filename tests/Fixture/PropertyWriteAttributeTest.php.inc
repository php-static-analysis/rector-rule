<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
 * @property-write string $name
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

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
 */
#[Template('T')]
#[\PhpStaticAnalysis\Attributes\PropertyWrite(name: 'string')]
#[\PhpStaticAnalysis\Attributes\PropertyWrite(num: 'int')]
#[\PhpStaticAnalysis\Attributes\PropertyWrite(index: 'string[]')]
class PropertyWriteAttributeTest
{
}

?>
