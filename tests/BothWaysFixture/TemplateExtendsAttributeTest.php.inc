<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

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
#[Property(name: 'string')]
#[TemplateExtends('TemplateClass<int>')] // this is the extended class
class TemplateExtendsAttributeTest extends TemplateClass
{
}

#[TemplateExtends('TemplateClass<int>')]
class TemplateExtendsAttributeTest2 extends TemplateClass
{
}
