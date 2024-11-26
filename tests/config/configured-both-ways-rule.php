<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAnnotationsToAttributesSetList;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAttributesToAnnotationsSetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisAttributesToAnnotationsSetList::ATTRIBUTES_TO_ANNOTATIONS
    ])
    ->withSets([
        PhpStaticAnalysisAnnotationsToAttributesSetList::ANNOTATIONS_TO_ATTRIBUTES
    ])
    ->withImportNames();
