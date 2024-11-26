<?php

namespace test\PhpStaticAnalysis\RectorRule\BothWaysFixture;

use Exception;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\TemplateContravariant;

/**
 * @codeCoverageIgnore
 */
#[Property(name: 'string')]
#[TemplateContravariant('T1')]
#[TemplateContravariant('T2', 'Exception')]
#[TemplateContravariant('T3', 'Exception')] // this is also contravariant
class TemplateContravariantAttributeTest
{
}
