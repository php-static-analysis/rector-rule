<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateUse;

#[Template('T')]
trait TemplateTrait
{
}

#[Property(name:'string')]
#[TemplateUse('TemplateTrait<int>')] // this is the used trait
class TemplateUseAttributeTest
{
    /**
     * @codeCoverageIgnore
     */
    use TemplateTrait;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\InverseFixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateUse;

/**
 * @template T
 */
trait TemplateTrait
{
}

/**
 * @property string $name
 */
class TemplateUseAttributeTest
{
    /**
     * @codeCoverageIgnore
     * @template-use TemplateTrait<int>
     */
    use TemplateTrait;
}

?>
