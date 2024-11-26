<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Immutable;

/**
 * @codeCoverageIgnore
 */
#[Immutable] // all properties are read only
class ImmutableAttributeTest
{
}

