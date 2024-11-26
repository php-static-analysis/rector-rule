<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\PropertyWrite;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[PropertyWrite(name: 'string')]
#[PropertyWrite(userName: 'string')] // the name of the user
class PropertyWriteAttributeTest
{
}
