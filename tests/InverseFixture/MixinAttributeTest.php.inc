<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Mixin;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 * @template T
 * @mixin A
 * @mixin B
 */
class MixinAttributeTest
{
}

?>
