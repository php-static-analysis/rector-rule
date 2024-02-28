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

use PhpStaticAnalysis\Attributes\Param;

/**
 * @codeCoverageIgnore
 */
#[\PhpStaticAnalysis\Attributes\Immutable] // all properties are read only
class ImmutableAttributeTest
{
}

#[\PhpStaticAnalysis\Attributes\Immutable]
class ImmutableAttributePsalmTest
{
}

#[\PhpStaticAnalysis\Attributes\Immutable]
class ImmutableAttributePHPStanTest
{
}

?>
