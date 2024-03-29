<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

#[Template('T')]
interface TemplateInterface
{
}

/**
 * @codeCoverageIgnore
 * @implements TemplateInterface<int> this is the implemented interface
 */
#[Property(name:'string')]
class TemplateImplementsAttributeTest implements TemplateInterface
{
}

/**
 * @template-implements TemplateInterface<int>
 */
class TemplateImplementsAttributeTest2 implements TemplateInterface
{
}

/**
 * @phpstan-implements TemplateInterface<int>
 */
class TemplateImplementsAttributeTest3 implements TemplateInterface
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\TemplateImplements;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

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

#[TemplateImplements('TemplateInterface<int>')]
class TemplateImplementsAttributeTest2 implements TemplateInterface
{
}

#[TemplateImplements('TemplateInterface<int>')]
class TemplateImplementsAttributeTest3 implements TemplateInterface
{
}

?>
