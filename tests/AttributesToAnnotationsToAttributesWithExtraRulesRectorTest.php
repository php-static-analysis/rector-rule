<?php

declare(strict_types=1);

namespace test\PhpStaticAnalysis\RectorRule;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AttributesToAnnotationsToAttributesWithExtraRulesRectorTest extends AbstractRectorTestCase
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
        return self::yieldFilesFromDirectory(__DIR__ . '/WithExtraRulesFixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured-with-extra-rule-rule.php';
    }
}
