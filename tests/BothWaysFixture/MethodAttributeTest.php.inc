<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Method;
use PhpStaticAnalysis\Attributes\Template;

/**
 * @codeCoverageIgnore
 */
#[Template('T')]
#[Method('string getString()')]
#[Method('string getName()')] // used to get the name
class MethodAttributeTest
{
}
