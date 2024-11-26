<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

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
