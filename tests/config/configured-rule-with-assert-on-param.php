<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisSetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisSetList::ANNOTATIONS_TO_ATTRIBUTES
    ])
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'addAssertAttributeOnParameters' => true,
        ]
    )
    ->withImportNames();
