<?php

namespace test\PhpStaticAnalysis\RectorRule\WithExtraRulesFixture;

use PhpStaticAnalysis\Attributes\Type;

class TypeAttributeTest
{
    #[Type('string')]
    public $name;

    #[Type('string')]
    public string $anotherName;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\WithExtraRulesFixture;

use PhpStaticAnalysis\Attributes\Type;

class TypeAttributeTest
{
    #[Type('string')]
    public $name;

    public string $anotherName;
}

?>
