<?php

declare(strict_types=1);

use PhpStaticAnalysis\Attributes\IsReadOnly;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisSetList;
use Rector\Config\RectorConfig;
use Rector\Php80\ValueObject\AnnotationToAttribute;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->sets([
        PhpStaticAnalysisSetList::ANNOTATIONS_TO_ATTRIBUTES
    ]);
};
