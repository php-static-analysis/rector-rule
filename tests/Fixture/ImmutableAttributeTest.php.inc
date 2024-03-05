<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

/**
 * @codeCoverageIgnore
 * @immutable all properties are read only
 */
class ImmutableAttributeTest
{
}

/**
 * @psalm-immutable
 */
class ImmutableAttributePsalmTest
{
}

/**
 * @phpstan-immutable
 */
class ImmutableAttributePHPStanTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Immutable;
use PhpStaticAnalysis\Attributes\Param;

/**
 * @codeCoverageIgnore
 */
#[Immutable] // all properties are read only
class ImmutableAttributeTest
{
}

#[Immutable]
class ImmutableAttributePsalmTest
{
}

#[Immutable]
class ImmutableAttributePHPStanTest
{
}

?>
