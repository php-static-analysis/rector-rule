<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

#[Template('T')]
trait TemplateTrait
{
}

#[Property(name:'string')]
class TemplateUseAttributeTest
{
    /**
     * @codeCoverageIgnore
     * @use TemplateTrait<int> this is the used trait
     */
    use TemplateTrait;
}

class TemplateUseAttributeTest2
{
    /**
     * @template-use TemplateTrait<int>
     */
    use TemplateTrait;
}

class TemplateUseAttributeTest3
{
    /**
     * @phpstan-use TemplateTrait<int>
     */
    use TemplateTrait;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\TemplateUse;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Template;

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

#[TemplateUse('TemplateTrait<int>')]
class TemplateUseAttributeTest2
{
    use TemplateTrait;
}

#[TemplateUse('TemplateTrait<int>')]
class TemplateUseAttributeTest3
{
    use TemplateTrait;
}

?>
