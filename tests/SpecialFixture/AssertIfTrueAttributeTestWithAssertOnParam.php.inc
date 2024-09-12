<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use Exception;
use PhpStaticAnalysis\Attributes\AssertIfTrue;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfTrueAttributeTestWithAssertOnParam
{
    /**
     * @phpstan-assert-if-true string $name
     */
    public function checkName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-true !string $name
     */
    public function checkNegatedName($name)
    {
        return is_string($name);
    }

    /**
     * @phpstan-assert-if-true =string $name
     */
    public function checkEqualityName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-true string $this->item
     */
    public function checkPropertyName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-true string $this->getName()
     */
    public function checkMethodName($name)
    {
        return !is_string($name);
    }

    /**
     * @codeCoverageIgnore
     * @phpstan-assert-if-true string $name
     */
    public function checkMoreNames($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-true string $name
     */
    #[Returns('string')]
    public function checkAnotherName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-true string $name1
     * @phpstan-assert-if-true string $name2
     */
    public function checkTwoNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    /**
     * @phpstan-assert-if-true string $name2
     */
    #[AssertIfTrue(name1: 'string')]
    public function checkTwoMoreNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    /**
     * @psalm-assert-if-true string $name
     */
    public function checkPsalmName($name)
    {
        return !is_string($name);
    }
}

/**
 * @phpstan-assert-if-true string $name
 */
function checkName($name)
{
    return !is_string($name);
}

?>
-----
<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use Exception;
use PhpStaticAnalysis\Attributes\AssertIfTrue;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfTrueAttributeTestWithAssertOnParam
{
    public function checkName(#[AssertIfTrue('string')]
    $name)
    {
        return !is_string($name);
    }

    public function checkNegatedName(#[AssertIfTrue('!string')]
    $name)
    {
        return is_string($name);
    }

    public function checkEqualityName(#[AssertIfTrue('=string')]
    $name)
    {
        return !is_string($name);
    }

    #[AssertIfTrue('string $this->item')]
    public function checkPropertyName($name)
    {
        return !is_string($name);
    }

    #[AssertIfTrue('string $this->getName()')]
    public function checkMethodName($name)
    {
        return !is_string($name);
    }

    /**
     * @codeCoverageIgnore
     */
    public function checkMoreNames(#[AssertIfTrue('string')]
    $name)
    {
        return !is_string($name);
    }

    #[Returns('string')]
    public function checkAnotherName(#[AssertIfTrue('string')]
    $name)
    {
        return !is_string($name);
    }

    public function checkTwoNames(#[AssertIfTrue('string')]
    $name1, #[AssertIfTrue('string')]
    $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    #[AssertIfTrue(name1: 'string')]
    public function checkTwoMoreNames($name1, #[AssertIfTrue('string')]
    $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    public function checkPsalmName(#[AssertIfTrue('string')]
    $name)
    {
        return !is_string($name);
    }
}

function checkName(#[AssertIfTrue('string')]
$name)
{
    return !is_string($name);
}

?>
