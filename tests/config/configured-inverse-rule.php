<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAttributesToAnnotationsSetList;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisAttributesToAnnotationsSetList::ATTRIBUTES_TO_ANNOTATIONS
    ])
    ->withImportNames();
