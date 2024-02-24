<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;

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
 * @phpstan-require-extends RequireClass this is the class that needs to be extended
 */
#[Property(name:'string')]
trait RequireExtendsAttributeTest2
{
}

/**
 * @psalm-require-extends RequireClass
 */
trait RequireExtendsAttributeTest3
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;

class RequireClass
{
}

#[\PhpStaticAnalysis\Attributes\RequireExtends('RequireClass')]
trait RequireExtendsAttributeTest
{
}

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[\PhpStaticAnalysis\Attributes\RequireExtends('RequireClass')] // this is the class that needs to be extended
trait RequireExtendsAttributeTest2
{
}

#[\PhpStaticAnalysis\Attributes\RequireExtends('RequireClass')]
trait RequireExtendsAttributeTest3
{
}

?>
