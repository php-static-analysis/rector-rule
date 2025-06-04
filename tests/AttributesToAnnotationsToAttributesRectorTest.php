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
        $fileName = basename($filePath);
        $this->expectOutputString(
            <<<TXT

WARNING: On fixture file "$fileName" for test "test\PhpStaticAnalysis\RectorRule\AttributesToAnnotationsToAttributesRectorTest"
File not changed but some Rector rules applied:
 * PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector
 * PhpStaticAnalysis\RectorRule\AttributesToAnnotationsRector

TXT
        );
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
