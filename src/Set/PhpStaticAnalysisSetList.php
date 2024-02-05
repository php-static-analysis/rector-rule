<?php

declare(strict_types=1);

namespace PhpStaticAnalysis\RectorRule\Set;

use PhpStaticAnalysis\Attributes\Type;
use Rector\Set\Contract\SetListInterface;

final class PhpStaticAnalysisSetList implements SetListInterface
{
    #[Type('string')]
    public const ANNOTATIONS_TO_ATTRIBUTES = __DIR__ . '/../../config/sets/php-static-analysis-annotations-to-attributes.php';
}
