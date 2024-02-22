<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

/**
 * @internal
 */
class InternalAttributeTest
{
    /**
     * @internal
     */
    public const NAME = 'name';

    /**
     * @internal
     */
    public string $name = '';

    /**
     * @internal
     */
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     * @internal
     */
    public function getMoreNames(): void
    {
    }

    /**
     * @internal
     */
    #[Param(name:'string')]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    /**
     * @internal only available in the current namespace
     */
    public function getUserName(): void
    {
    }

    /**
     * @psalm-internal A\B
     */
    public function getPsalmName(): void
    {
    }

    /**
     * @psalm-internal A\B Only available in the A\B namespace
     */
    public function getPsalmNameWithComment(): void
    {
    }
}

/**
 * @internal
 */
function getName(): void
{
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\Param;

#[\PhpStaticAnalysis\Attributes\Internal]
class InternalAttributeTest
{
    #[\PhpStaticAnalysis\Attributes\Internal]
    public const NAME = 'name';

    #[\PhpStaticAnalysis\Attributes\Internal]
    public string $name = '';

    #[\PhpStaticAnalysis\Attributes\Internal]
    public function getName(): void
    {
    }

    /**
     * @codeCoverageIgnore
     */
    #[\PhpStaticAnalysis\Attributes\Internal]
    public function getMoreNames(): void
    {
    }

    #[Param(name:'string')]
    #[\PhpStaticAnalysis\Attributes\Internal]
    public function getAnotherName($name)
    {
        return "Hello " . $name;
    }

    #[\PhpStaticAnalysis\Attributes\Internal] // only available in the current namespace
    public function getUserName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Internal('A\B')]
    public function getPsalmName(): void
    {
    }

    #[\PhpStaticAnalysis\Attributes\Internal('A\B')] // Only available in the A\B namespace
    public function getPsalmNameWithComment(): void
    {
    }
}

#[\PhpStaticAnalysis\Attributes\Internal]
function getName(): void
{
}

?>
