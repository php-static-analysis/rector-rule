<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[Property(name: 'string')]
#[Property(userName: 'string')] // the name of the user
class PropertyAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @template T
 * @property string $name
 * @property string $userName
 */
class PropertyAttributeTest
{
}

?>
