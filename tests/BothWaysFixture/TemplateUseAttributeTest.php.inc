<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateUse;

#[Template('T')]
trait TemplateTrait
{
}

#[Property(name: 'string')]
#[TemplateUse('TemplateTrait<int>')] // this is the used trait
class TemplateUseAttributeTest
{
    /**
     * @codeCoverageIgnore
     */
    use TemplateTrait;
}
