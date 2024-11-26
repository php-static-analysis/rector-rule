<?php

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\AssertIfTrue;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfTrueAttributeTest
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
        return !is_string($name);
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
     * @phpstan-assert-if-true string $name the name of the user
     */
    public function checkUserName($name)
    {
        return !is_string($name);
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

namespace test\PhpStaticAnalysis\RectorRule\Fixture;

use PhpStaticAnalysis\Attributes\AssertIfTrue;
use PhpStaticAnalysis\Attributes\Returns;

class AssertIfTrueAttributeTest
{
    #[AssertIfTrue(name: 'string')]
    public function checkName($name)
    {
        return !is_string($name);
    }

    #[AssertIfTrue(name: '!string')]
    public function checkNegatedName($name)
    {
        return !is_string($name);
    }

    #[AssertIfTrue(name: '=string')]
    public function checkEqualityName($name)
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
    #[AssertIfTrue(name: 'string')]
    public function checkMoreNames($name)
    {
        return !is_string($name);
    }

    #[Returns('string')]
    #[AssertIfTrue(name: 'string')]
    public function checkAnotherName($name)
    {
        return !is_string($name);
    }

    #[AssertIfTrue(name1: 'string')]
    #[AssertIfTrue(name2: 'string')]
    public function checkTwoNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    #[AssertIfTrue(name1: 'string')]
    #[AssertIfTrue(name2: 'string')]
    public function checkTwoMoreNames($name1, $name2)
    {
        return !is_string($name1) || !is_string($name2);
    }

    #[AssertIfTrue(name: 'string')] // the name of the user
    public function checkUserName($name)
    {
        return !is_string($name);
    }

    #[AssertIfTrue(name: 'string')]
    public function checkPsalmName($name)
    {
        return !is_string($name);
    }
}

#[AssertIfTrue(name: 'string')]
function checkName($name)
{
    return !is_string($name);
}

?>
