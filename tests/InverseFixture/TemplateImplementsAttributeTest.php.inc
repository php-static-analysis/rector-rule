<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateImplements;

#[Template('T')]
interface TemplateInterface
{
}

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[TemplateImplements('TemplateInterface<int>')] // this is the implemented interface
class TemplateImplementsAttributeTest implements TemplateInterface
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateImplements;

/**
 * @template T
 */
interface TemplateInterface
{
}

/**
 * @codeCoverageIgnore
 * @property string $name
 * @template-implements TemplateInterface<int>
 */
class TemplateImplementsAttributeTest implements TemplateInterface
{
}

?>
