<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @mixin A
 * @mixin B the proxied class
 */
#[Template('T')]
class MixinAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Mixin;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[Mixin('A')]
#[Mixin('B')] // the proxied class
class MixinAttributeTest
{
}

?>
