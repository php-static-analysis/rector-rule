<?php

namespace test\PhpStaticAnalysis\RectorRule\WithExtraRulesFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ReturnsAttributeTest
{
    #[Returns('string')]
    public function getName()
    {
        return 'John';
    }

    #[Returns('string')]
    public function getMoreNames(): string
    {
        return 'Mike';
    }

}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\WithExtraRulesFixture;

use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ReturnsAttributeTest
{
    #[Returns('string')]
    public function getName()
    {
        return 'John';
    }

    public function getMoreNames(): string
    {
        return 'Mike';
    }

}

?>
