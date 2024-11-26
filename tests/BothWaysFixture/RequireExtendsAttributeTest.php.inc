<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\RequireExtends;

class RequireClass
{
}

#[RequireExtends('RequireClass')]
trait RequireExtendsAttributeTest
{
}

/**
 * @codeCoverageIgnore
 */
#[Property(name: 'string')]
#[RequireExtends('RequireClass')] // this is the class that needs to be extended
trait RequireExtendsAttributeTest2
{
}
