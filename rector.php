<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisSetList;

return RectorConfig::configure()
    ->withPaths([
        __DIR__ . '/src',
        __DIR__ . '/tests',
    ])
    ->withSkip([
        __DIR__ . '/tests/Fixture',
    ])
    ->withSets([
        PhpStaticAnalysisSetList::ANNOTATIONS_TO_ATTRIBUTES
    ]);
