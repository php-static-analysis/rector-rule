<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;

interface RequireInterface
{
}

/**
 * @phpstan-require-implements RequireInterface
 */
trait RequireImplementsAttributeTest
{
}

/**
 * @codeCoverageIgnore
 * @phpstan-require-implements RequireInterface this is the interface that needs to be implemented
 */
#[Property(name:'string')]
trait RequireImplementsAttributeTest2
{
}

/**
 * @psalm-require-implements RequireInterface
 */
trait RequireImplementsAttributeTest3
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\RequireImplements;
use PhpStaticAnalysis\Attributes\Property;

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
#[Property(name:'string')]
#[RequireImplements('RequireInterface')] // this is the interface that needs to be implemented
trait RequireImplementsAttributeTest2
{
}

#[RequireImplements('RequireInterface')]
trait RequireImplementsAttributeTest3
{
}

?>
