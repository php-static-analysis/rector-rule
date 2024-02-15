<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisSetList;
use Rector\Config\RectorConfig;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->sets([
        PhpStaticAnalysisSetList::ANNOTATIONS_TO_ATTRIBUTES
    ]);
    $rectorConfig->ruleWithConfiguration(
        AnnotationsToAttributesRector::class,
        [
            'usePropertyAttributeForVarAnnotation' => true,
        ]
    );
};
