<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
#[Property(name:'string')]
#[RequireImplements('RequireInterface')] // this is the interface that needs to be implemented
trait RequireImplementsAttributeTest2
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\RequireImplements;

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
 * @property string $name
 * @phpstan-require-implements RequireInterface
 */
trait RequireImplementsAttributeTest2
{
}

?>
