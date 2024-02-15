<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
 * @property string $name
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

use PhpStaticAnalysis\Attributes\Template;

/**
 * @deprecated
 */
#[Template('T')]
#[\PhpStaticAnalysis\Attributes\Property(name: 'string')]
#[\PhpStaticAnalysis\Attributes\Property(num: 'int')]
#[\PhpStaticAnalysis\Attributes\Property(index: 'string[]')]
class PropertyAttributeTest
{
}

?>
