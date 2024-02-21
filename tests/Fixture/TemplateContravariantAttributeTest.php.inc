<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @codeCoverageIgnore
 * @template-contravariant T1
 * @template-contravariant T2 of Exception
 * @template-contravariant T3 this is contravariant
 * @template-contravariant T4 of Exception this is also contravariant
 * @phpstan-template-contravariant T5
 */
#[Property(name:'string')]
class TemplateContravariantAttributeTest
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T1')]
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T2', 'Exception')]
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T3')] // this is contravariant
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T4', 'Exception')] // this is also contravariant
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T5')]
class TemplateContravariantAttributeTest
{
}

?>
