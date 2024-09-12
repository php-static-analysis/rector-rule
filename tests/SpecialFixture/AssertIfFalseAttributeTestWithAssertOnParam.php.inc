<?php

namespace test\PhpStaticAnalysis\RectorRule\SpecialFixture;

use Exception;
use PhpStaticAnalysis\Attributes\AssertIfFalse;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfFalseAttributeTestWithAssertOnParam
{
    /**
     * @phpstan-assert-if-false string $name
     */
    public function checkName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-false !string $name
     */
    public function checkNegatedName($name)
    {
        return is_string($name);
    }

    /**
     * @phpstan-assert-if-false =string $name
     */
    public function checkEqualityName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-false string $this->item
     */
    public function checkPropertyName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-false string $this->getName()
     */
    public function checkMethodName($name)
    {
        return !is_string($name);
    }

    /**
     * @codeCoverageIgnore
     * @phpstan-assert-if-false string $name
     */
    public function checkMoreNames($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-false string $name
     */
    #[Returns('string')]
    public function checkAnotherName($name)
    {
        return !is_string($name);
    }

    /**
     * @phpstan-assert-if-false string $name1
     * @phpstan-assert-if-false string $name2
     */
    public function checkTwoNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    /**
     * @phpstan-assert-if-false string $name2
     */
    #[AssertIfFalse(name1: 'string')]
    public function checkTwoMoreNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    /**
     * @psalm-assert-if-false string $name
     */
    public function checkPsalmName($name)
    {
        return !is_string($name);
    }
}

/**
 * @phpstan-assert-if-false string $name
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
use PhpStaticAnalysis\Attributes\AssertIfFalse;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfFalseAttributeTestWithAssertOnParam
{
    public function checkName(#[AssertIfFalse('string')]
    $name)
    {
        return !is_string($name);
    }

    public function checkNegatedName(#[AssertIfFalse('!string')]
    $name)
    {
        return is_string($name);
    }

    public function checkEqualityName(#[AssertIfFalse('=string')]
    $name)
    {
        return !is_string($name);
    }

    #[AssertIfFalse('string $this->item')]
    public function checkPropertyName($name)
    {
        return !is_string($name);
    }

    #[AssertIfFalse('string $this->getName()')]
    public function checkMethodName($name)
    {
        return !is_string($name);
    }

    /**
     * @codeCoverageIgnore
     */
    public function checkMoreNames(#[AssertIfFalse('string')]
    $name)
    {
        return !is_string($name);
    }

    #[Returns('string')]
    public function checkAnotherName(#[AssertIfFalse('string')]
    $name)
    {
        return !is_string($name);
    }

    public function checkTwoNames(#[AssertIfFalse('string')]
    $name1, #[AssertIfFalse('string')]
    $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    #[AssertIfFalse(name1: 'string')]
    public function checkTwoMoreNames($name1, #[AssertIfFalse('string')]
    $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    public function checkPsalmName(#[AssertIfFalse('string')]
    $name)
    {
        return !is_string($name);
    }
}

function checkName(#[AssertIfFalse('string')]
$name)
{
    return !is_string($name);
}

?>
