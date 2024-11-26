<?php

declare(strict_types=1);

namespace PhpStaticAnalysis\RectorRule\Set;

use PhpStaticAnalysis\Attributes\Type;
use Rector\Set\Contract\SetListInterface;

final class PhpStaticAnalysisAttributesToAnnotationsSetList
{
    #[Type('string')]
    public const ATTRIBUTES_TO_ANNOTATIONS = __DIR__ . '/../../config/sets/php-static-analysis-attributes-to-annotations.php';
}
