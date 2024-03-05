<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

#[Template('T')]
class TemplateClass
{
}

/**
 * @codeCoverageIgnore
 * @extends TemplateClass<int> this is the extended class
 */
#[Property(name:'string')]
class TemplateExtendsAttributeTest extends TemplateClass
{
}

/**
 * @template-extends TemplateClass<int>
 */
class TemplateExtendsAttributeTest2 extends TemplateClass
{
}

/**
 * @phpstan-extends TemplateClass<int>
 */
class TemplateExtendsAttributeTest3 extends TemplateClass
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\TemplateExtends;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

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

#[TemplateExtends('TemplateClass<int>')]
class TemplateExtendsAttributeTest3 extends TemplateClass
{
}

?>
