<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAnnotationsToAttributesSetList;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAttributesToAnnotationsSetList;
use Rector\Config\RectorConfig;
use Rector\DeadCode\Rector\ClassMethod\RemoveUselessParamTagRector;
use Rector\DeadCode\Rector\ClassMethod\RemoveUselessReturnTagRector;
use Rector\DeadCode\Rector\Property\RemoveUselessVarTagRector;

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisAttributesToAnnotationsSetList::ATTRIBUTES_TO_ANNOTATIONS
    ])
    ->withRules([
        RemoveUselessParamTagRector::class,
        RemoveUselessReturnTagRector::class,
        RemoveUselessVarTagRector::class
    ])
    ->withSets([
        PhpStaticAnalysisAnnotationsToAttributesSetList::ANNOTATIONS_TO_ATTRIBUTES
    ])
    ->withImportNames();
