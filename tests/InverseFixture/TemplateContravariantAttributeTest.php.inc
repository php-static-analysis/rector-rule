<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\TemplateContravariant;

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[TemplateContravariant('T1')]
#[TemplateContravariant('T2', 'Exception')]
#[TemplateContravariant('T3')] // this is contravariant
#[TemplateContravariant('T4', 'Exception')] // this is also contravariant
class TemplateContravariantAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\TemplateContravariant;

/**
 * @codeCoverageIgnore
 * @property string $name
 * @template-contravariant T1
 * @template-contravariant T2 of Exception
 * @template-contravariant T3
 * @template-contravariant T4 of Exception
 */
class TemplateContravariantAttributeTest
{
}

?>
