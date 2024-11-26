<?php

namespace test\PhpStaticAnalysis\RectorRule\WithExtraRulesFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTest
{
    #[Param(name: 'string')]
    #[Param(description: 'string')]
    public function getName(string $name, $description)
    {
        return $name . $description;
    }
}
?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\WithExtraRulesFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ParamAttributeTest
{
    #[Param(description: 'string')]
    public function getName(string $name, $description)
    {
        return $name . $description;
    }
}
?>
