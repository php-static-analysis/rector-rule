<?php

declare(strict_types=1);

namespace test\PhpStaticAnalysis\RectorRule;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AnnotationsToAttributesWithParamOnParamRectorTest extends AbstractRectorTestCase
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
        yield [__DIR__ . '/SpecialFixture/ParamAttributeTestWithParamOnParam.php.inc'];
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured-rule-with-param-on-param.php';
    }
}
