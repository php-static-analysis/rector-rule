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
     * @deprecated
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

use PhpStaticAnalysis\Attributes\IsReadOnly;

class PropertyAttributeTestForVarAnnotation
{
    #[\PhpStaticAnalysis\Attributes\Property('string')]
    public $name;

    /**
     * @deprecated
     */
    #[\PhpStaticAnalysis\Attributes\Property('string')]
    public $anotherName;

    #[IsReadOnly]
    #[\PhpStaticAnalysis\Attributes\Property('string')]
    public $otherName;

    #[\PhpStaticAnalysis\Attributes\Property('string')]
    public $psalmName;

    #[\PhpStaticAnalysis\Attributes\Property('string')]
    public $phpstanName;
}

?>
