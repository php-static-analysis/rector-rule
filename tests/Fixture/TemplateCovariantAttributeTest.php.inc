<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @deprecated
 * @template-covariant T1
 * @template-covariant T2 of Exception
 * @psalm-template-covariant T3
 * @phpstan-template-covariant T4
 */
#[Property(name:'string')]
class TemplateCovariantAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @deprecated
 */
#[Property(name:'string')]
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T1')]
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T2', 'Exception')]
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T3')]
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T4')]
class TemplateCovariantAttributeTest
{
}

?>
