<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\TemplateCovariant;

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[TemplateCovariant('T1')]
#[TemplateCovariant('T2', 'Exception')]
#[TemplateCovariant('T3', 'Exception')] // this is also covariant
class TemplateCovariantAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\TemplateCovariant;

/**
 * @codeCoverageIgnore
 * @property string $name
 * @template-covariant T1
 * @template-covariant T2 of Exception
 * @template-covariant T3 of Exception
 */
class TemplateCovariantAttributeTest
{
}

?>
