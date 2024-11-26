<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAnnotationsToAttributesSetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisAnnotationsToAttributesSetList::ANNOTATIONS_TO_ATTRIBUTES
    ])
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'addAssertAttributeOnParameters' => true,
        ]
    )
    ->withImportNames();
