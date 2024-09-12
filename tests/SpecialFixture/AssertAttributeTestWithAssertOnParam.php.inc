<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Assert;
use PhpStaticAnalysis\Attributes\Returns;

class AssertAttributeTestWithAssertOnParam
{
    /**
     * @phpstan-assert string $name
     */
    public function checkName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert !string $name
     */
    public function checkNegatedName($name)
    {
        if (is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert =string $name
     */
    public function checkEqualityName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert string $this->item
     */
    public function checkPropertyName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert string $this->getName()
     */
    public function checkMethodName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @codeCoverageIgnore
     * @phpstan-assert string $name
     */
    public function checkMoreNames($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert string $name
     */
    #[Returns('string')]
    public function checkAnotherName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert string $name1
     * @phpstan-assert string $name2
     */
    public function checkTwoNames($name1, $name2)
    {
        if (!is_string($name1) || !is_string($name2)) {
            throw new Exception();
        }
    }

    /**
     * @phpstan-assert string $name2
     */
    #[Assert(name1: 'string')]
    public function checkTwoMoreNames($name1, $name2)
    {
        if (!is_string($name1) || !is_string($name2)) {
            throw new Exception();
        }
    }

    /**
     * @psalm-assert string $name
     */
    public function checkPsalmName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }
}

/**
 * @phpstan-assert string $name
 */
function checkName($name)
{
    if (!is_string($name)) {
        throw new Exception();
    }
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Assert;
use PhpStaticAnalysis\Attributes\Returns;

class AssertAttributeTestWithAssertOnParam
{
    public function checkName(#[Assert('string')]
    $name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    public function checkNegatedName(#[Assert('!string')]
    $name)
    {
        if (is_string($name)) {
            throw new Exception();
        }
    }

    public function checkEqualityName(#[Assert('=string')]
    $name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert('string $this->item')]
    public function checkPropertyName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Assert('string $this->getName()')]
    public function checkMethodName($name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    /**
     * @codeCoverageIgnore
     */
    public function checkMoreNames(#[Assert('string')]
    $name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    #[Returns('string')]
    public function checkAnotherName(#[Assert('string')]
    $name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }

    public function checkTwoNames(#[Assert('string')]
    $name1, #[Assert('string')]
    $name2)
    {
        if (!is_string($name1) || !is_string($name2)) {
            throw new Exception();
        }
    }

    #[Assert(name1: 'string')]
    public function checkTwoMoreNames($name1, #[Assert('string')]
    $name2)
    {
        if (!is_string($name1) || !is_string($name2)) {
            throw new Exception();
        }
    }

    public function checkPsalmName(#[Assert('string')]
    $name)
    {
        if (!is_string($name)) {
            throw new Exception();
        }
    }
}

function checkName(#[Assert('string')]
$name)
{
    if (!is_string($name)) {
        throw new Exception();
    }
}

?>
