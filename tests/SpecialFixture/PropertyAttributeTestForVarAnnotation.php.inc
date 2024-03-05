<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\IsReadOnly;

class PropertyAttributeTestForVarAnnotation
{
    /**
     * @var string
     */
    public $name;

    /**
     * @codeCoverageIgnore
     * @var string
     */
    public $anotherName;

    /**
     * @var string
     */
    #[IsReadOnly]
    public $otherName;

    /**
     * @psalm-var string
     */
    public $psalmName;

    /**
     * @phpstan-var string
     */
    public $phpstanName;
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\IsReadOnly;

class PropertyAttributeTestForVarAnnotation
{
    #[Property('string')]
    public $name;

    /**
     * @codeCoverageIgnore
     */
    #[Property('string')]
    public $anotherName;

    #[IsReadOnly]
    #[Property('string')]
    public $otherName;

    #[Property('string')]
    public $psalmName;

    #[Property('string')]
    public $phpstanName;
}

?>
