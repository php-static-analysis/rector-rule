<?php

declare(strict_types=1);

namespace test\PhpStaticAnalysis\RectorRule;

use Iterator;
use Rector\Testing\PHPUnit\AbstractRectorTestCase;

final class AttributesToAnnotationsToAttributesRectorTest extends AbstractRectorTestCase
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
        return self::yieldFilesFromDirectory(__DIR__ . '/BothWaysFixture');
    }

    public function provideConfigFilePath(): string
    {
        return __DIR__ . '/config/configured-both-ways-rule.php';
    }
}
