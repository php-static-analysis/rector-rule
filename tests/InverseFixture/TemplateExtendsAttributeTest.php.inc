<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateExtends;

#[Template('T')]
class TemplateClass
{
}

/**
 * @codeCoverageIgnore
 */
#[Property(name:'string')]
#[TemplateExtends('TemplateClass<int>')] // this is the extended class
class TemplateExtendsAttributeTest extends TemplateClass
{
}

#[TemplateExtends('TemplateClass<int>')]
class TemplateExtendsAttributeTest2 extends TemplateClass
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateExtends;

/**
 * @template T
 */
class TemplateClass
{
}

/**
 * @codeCoverageIgnore
 * @property string $name
 * @template-extends TemplateClass<int>
 */
class TemplateExtendsAttributeTest extends TemplateClass
{
}

/**
 * @template-extends TemplateClass<int>
 */
class TemplateExtendsAttributeTest2 extends TemplateClass
{
}

?>
