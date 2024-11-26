<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\TemplateCovariant;

/**
 * @codeCoverageIgnore
 */
#[Property(name: 'string')]
#[TemplateCovariant('T1')]
#[TemplateCovariant('T2', 'Exception')]
#[TemplateCovariant('T3', 'Exception')] // this is also covariant
class TemplateCovariantAttributeTest
{
}
