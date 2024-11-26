<?php

declare(strict_types=1);

use PhpStaticAnalysis\RectorRule\AttributesToAnnotationsRector;
use Rector\Config\RectorConfig;

return RectorConfig::configure()
    ->withRules([
        AttributesToAnnotationsRector::class
    ]);
