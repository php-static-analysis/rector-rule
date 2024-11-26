<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

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
#[Property(name: 'string')]
#[TemplateImplements('TemplateInterface<int>')] // this is the implemented interface
class TemplateImplementsAttributeTest implements TemplateInterface
{
}
