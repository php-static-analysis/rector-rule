<?php

declare(strict_types=1);

namespace PhpStaticAnalysis\RectorRule\Set\Provider;

use PhpStaticAnalysis\Attributes\Returns;
use Rector\Set\Contract\SetInterface;
use Rector\Set\Contract\SetProviderInterface;
use Rector\Set\Enum\SetGroup;
use Rector\Set\ValueObject\Set;

final class PhpStaticAnalysisSetProvider implements SetProviderInterface
{
    #[Returns('SetInterface[]')]
    public function provide(): array
    {
        return [
            new Set(SetGroup::ATTRIBUTES, 'Php Static Analysis Attributes', __DIR__ . '/../../../config/sets/php-static-analysis-annotations-to-attributes.php'),
        ];
    }
}
