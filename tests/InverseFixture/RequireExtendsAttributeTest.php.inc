<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

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
#[Property(name:'string')]
#[RequireExtends('RequireClass')] // this is the class that needs to be extended
trait RequireExtendsAttributeTest2
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\RequireExtends;

class RequireClass
{
}

/**
 * @phpstan-require-extends RequireClass
 */
trait RequireExtendsAttributeTest
{
}

/**
 * @codeCoverageIgnore
 * @property string $name
 * @phpstan-require-extends RequireClass
 */
trait RequireExtendsAttributeTest2
{
}

?>
