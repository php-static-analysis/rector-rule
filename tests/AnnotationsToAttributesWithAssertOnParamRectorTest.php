<?php

declare(strict_types=1);

namespace test\PhpStaticAnalysis\RectorRule;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AnnotationsToAttributesWithAssertOnParamRectorTest extends AbstractRectorTestCase
{
    /**
     * @dataProvider provideData()
     */
    public function test(string $filePath): void
    {
        $this->doTestFile($filePath);
    }

    public static function provideData(): Iterator
    {
        yield [__DIR__ . '/SpecialFixture/AssertAttributeTestWithAssertOnParam.php.inc'];
        yield [__DIR__ . '/SpecialFixture/AssertIfFalseAttributeTestWithAssertOnParam.php.inc'];
        yield [__DIR__ . '/SpecialFixture/AssertIfTrueAttributeTestWithAssertOnParam.php.inc'];
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured-rule-with-assert-on-param.php';
    }
}
