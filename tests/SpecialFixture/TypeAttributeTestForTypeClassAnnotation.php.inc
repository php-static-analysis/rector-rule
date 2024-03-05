<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Type;

/**
 * @codeCoverageIgnore
 * @phpstan-type StringArray string[]
 * @psalm-type IntArray = int[]
 */
#[Type('FloatArray float[]')]
class TypeAttributeTestForTypeClassAnnotation
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Type;

/**
 * @codeCoverageIgnore
 */
#[Type('FloatArray float[]')]
#[Type('StringArray string[]')]
#[Type('IntArray int[]')]
class TypeAttributeTestForTypeClassAnnotation
{
}

?>
