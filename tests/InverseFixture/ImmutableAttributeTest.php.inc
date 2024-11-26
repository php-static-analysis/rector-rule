<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Immutable;

/**
 * @codeCoverageIgnore
 */
#[Immutable] // all properties are read only
class ImmutableAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Immutable;

/**
 * @codeCoverageIgnore
 * @phpstan-immutable
 */
class ImmutableAttributeTest
{
}

?>
