<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\PropertyRead;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[PropertyRead(name: 'string')]
#[PropertyRead(userName: 'string')] // the name of the user
class PropertyReadAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\PropertyRead;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @template T
 * @property-read string $name
 * @property-read string $userName
 */
class PropertyReadAttributeTest
{
}

?>
