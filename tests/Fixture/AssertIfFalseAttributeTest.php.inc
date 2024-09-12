<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\AssertIfFalse;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfFalseAttributeTest
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
        return !is_string($name);
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
     * @phpstan-assert-if-false string $name the name of the user
     */
    public function checkUserName($name)
    {
        return !is_string($name);
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

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use Exception;
use PhpStaticAnalysis\Attributes\AssertIfFalse;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfFalseAttributeTest
{
    #[AssertIfFalse(name: 'string')]
    public function checkName($name)
    {
        return !is_string($name);
    }

    #[AssertIfFalse(name: '!string')]
    public function checkNegatedName($name)
    {
        return !is_string($name);
    }

    #[AssertIfFalse(name: '=string')]
    public function checkEqualityName($name)
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
    #[AssertIfFalse(name: 'string')]
    public function checkMoreNames($name)
    {
        return !is_string($name);
    }

    #[Returns('string')]
    #[AssertIfFalse(name: 'string')]
    public function checkAnotherName($name)
    {
        return !is_string($name);
    }

    #[AssertIfFalse(name1: 'string')]
    #[AssertIfFalse(name2: 'string')]
    public function checkTwoNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    #[AssertIfFalse(name1: 'string')]
    #[AssertIfFalse(name2: 'string')]
    public function checkTwoMoreNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    #[AssertIfFalse(name: 'string')] // the name of the user
    public function checkUserName($name)
    {
        return !is_string($name);
    }

    #[AssertIfFalse(name: 'string')]
    public function checkPsalmName($name)
    {
        return !is_string($name);
    }
}

#[AssertIfFalse(name: 'string')]
function checkName($name)
{
    return !is_string($name);
}

?>
