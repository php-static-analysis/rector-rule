<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @deprecated
 * @template-covariant T1
 * @template-covariant T2 of Exception
 * @template-covariant T3 this is covariant
 * @template-covariant T4 of Exception this is also covariant
 * @psalm-template-covariant T5
 * @phpstan-template-covariant T6
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
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T3')] // this is covariant
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T4', 'Exception')] // this is also covariant
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T5')]
#[\PhpStaticAnalysis\Attributes\TemplateCovariant('T6')]
class TemplateCovariantAttributeTest
{
}

?>
