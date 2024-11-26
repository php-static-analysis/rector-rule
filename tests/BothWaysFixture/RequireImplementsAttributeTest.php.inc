<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\RequireImplements;

interface RequireInterface
{
}

#[RequireImplements('RequireInterface')]
trait RequireImplementsAttributeTest
{
}

/**
 * @codeCoverageIgnore
 */
#[Property(name: 'string')]
#[RequireImplements('RequireInterface')] // this is the interface that needs to be implemented
trait RequireImplementsAttributeTest2
{
}
