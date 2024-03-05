<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @codeCoverageIgnore
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

use PhpStaticAnalysis\Attributes\TemplateCovariant;
use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[TemplateCovariant('T1')]
#[TemplateCovariant('T2', 'Exception')]
#[TemplateCovariant('T3')] // this is covariant
#[TemplateCovariant('T4', 'Exception')] // this is also covariant
#[TemplateCovariant('T5')]
#[TemplateCovariant('T6')]
class TemplateCovariantAttributeTest
{
}

?>
