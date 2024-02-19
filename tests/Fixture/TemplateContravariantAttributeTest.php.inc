<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;

/**
 * @deprecated
 * @template-contravariant T1
 * @template-contravariant T2 of Exception
 * @phpstan-template-contravariant T3
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
 * @deprecated
 */
#[Property(name:'string')]
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T1')]
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T2', 'Exception')]
#[\PhpStaticAnalysis\Attributes\TemplateContravariant('T3')]
class TemplateContravariantAttributeTest
{
}

?>
