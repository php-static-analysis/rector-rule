<?php

declare(strict_types=1);

use PhpStaticAnalysis\Attributes\Assert;
use PhpStaticAnalysis\Attributes\AssertIfFalse;
use PhpStaticAnalysis\Attributes\AssertIfTrue;
use PhpStaticAnalysis\Attributes\DefineType;
use PhpStaticAnalysis\Attributes\Deprecated;
use PhpStaticAnalysis\Attributes\Immutable;
use PhpStaticAnalysis\Attributes\ImportType;
use PhpStaticAnalysis\Attributes\Impure;
use PhpStaticAnalysis\Attributes\Internal;
use PhpStaticAnalysis\Attributes\IsReadOnly;
use PhpStaticAnalysis\Attributes\Method;
use PhpStaticAnalysis\Attributes\Mixin;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\PropertyRead;
use PhpStaticAnalysis\Attributes\PropertyWrite;
use PhpStaticAnalysis\Attributes\Pure;
use PhpStaticAnalysis\Attributes\RequireExtends;
use PhpStaticAnalysis\Attributes\RequireImplements;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\Attributes\SelfOut;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\TemplateContravariant;
use PhpStaticAnalysis\Attributes\TemplateCovariant;
use PhpStaticAnalysis\Attributes\TemplateExtends;
use PhpStaticAnalysis\Attributes\TemplateImplements;
use PhpStaticAnalysis\Attributes\TemplateUse;
use PhpStaticAnalysis\Attributes\Throws;
use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use Rector\Config\RectorConfig;
use Rector\Php80\ValueObject\AnnotationToAttribute;

return RectorConfig::configure()
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            new AnnotationToAttribute('assert', Assert::class),
            new AnnotationToAttribute('assert_if_false', AssertIfFalse::class),
            new AnnotationToAttribute('assert_if_true', AssertIfTrue::class),
            new AnnotationToAttribute('deprecated', Deprecated::class),
            new AnnotationToAttribute('extends', TemplateExtends::class),
            new AnnotationToAttribute('immutable', Immutable::class),
            new AnnotationToAttribute('import_type', ImportType::class),
            new AnnotationToAttribute('impure', Impure::class),
            new AnnotationToAttribute('implements', TemplateImplements::class),
            new AnnotationToAttribute('internal', Internal::class),
            new AnnotationToAttribute('method', Method::class),
            new AnnotationToAttribute('mixin', Mixin::class),
            new AnnotationToAttribute('param', Param::class),
            new AnnotationToAttribute('param_out', ParamOut::class),
            new AnnotationToAttribute('property', Property::class),
            new AnnotationToAttribute('property_read', PropertyRead::class),
            new AnnotationToAttribute('property_write', PropertyWrite::class),
            new AnnotationToAttribute('pure', Pure::class),
            new AnnotationToAttribute('readonly', IsReadOnly::class),
            new AnnotationToAttribute('require_extends', RequireExtends::class),
            new AnnotationToAttribute('require_implements', RequireImplements::class),
            new AnnotationToAttribute('return', Returns::class),
            new AnnotationToAttribute('self_out', SelfOut::class),
            new AnnotationToAttribute('template', Template::class),
            new AnnotationToAttribute('template_contravariant', TemplateContravariant::class),
            new AnnotationToAttribute('template_covariant', TemplateCovariant::class),
            new AnnotationToAttribute('template_extends', TemplateExtends::class),
            new AnnotationToAttribute('template_implements', TemplateImplements::class),
            new AnnotationToAttribute('template_use', TemplateUse::class),
            new AnnotationToAttribute('this_out', SelfOut::class),
            new AnnotationToAttribute('throws', Throws::class),
            new AnnotationToAttribute('type', DefineType::class),
            new AnnotationToAttribute('use', TemplateUse::class),
            new AnnotationToAttribute('var', Type::class),
            'addParamAttributeOnParameters' => false,
            'addAssertAttributeOnParameters' => false,
            'useTypeAttributeForReturnAnnotation' => false,
            'usePropertyAttributeForVarAnnotation' => false,
            'excludeAnnotations' => [],
            'useTypeAttributeForTypeClassAnnotation' => false,
        ]
    );
