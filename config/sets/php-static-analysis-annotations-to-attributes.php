<?php

declare(strict_types=1);

use PhpStaticAnalysis\Attributes\Deprecated;
use PhpStaticAnalysis\Attributes\Impure;
use PhpStaticAnalysis\Attributes\Internal;
use PhpStaticAnalysis\Attributes\Method;
use PhpStaticAnalysis\Attributes\Mixin;
use PhpStaticAnalysis\Attributes\ParamOut;
use PhpStaticAnalysis\Attributes\PropertyRead;
use PhpStaticAnalysis\Attributes\PropertyWrite;
use PhpStaticAnalysis\Attributes\Pure;
use PhpStaticAnalysis\Attributes\RequireExtends;
use PhpStaticAnalysis\Attributes\RequireImplements;
use PhpStaticAnalysis\Attributes\SelfOut;
use PhpStaticAnalysis\Attributes\TemplateContravariant;
use PhpStaticAnalysis\Attributes\TemplateCovariant;
use PhpStaticAnalysis\Attributes\TemplateExtends;
use PhpStaticAnalysis\Attributes\TemplateImplements;
use PhpStaticAnalysis\Attributes\TemplateUse;
use PhpStaticAnalysis\Attributes\Throws;
use Rector\Config\RectorConfig;
use Rector\Php80\ValueObject\AnnotationToAttribute;
use PhpStaticAnalysis\Attributes\IsReadOnly;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Property;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\Attributes\Template;
use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;

return static function (RectorConfig $rectorConfig): void {
    $rectorConfig->ruleWithConfiguration(
        AnnotationsToAttributesRector::class,
        [
            new AnnotationToAttribute('deprecated', Deprecated::class),
            new AnnotationToAttribute('extends', TemplateExtends::class),
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
            new AnnotationToAttribute('use', TemplateUse::class),
            new AnnotationToAttribute('var', Type::class),
            'addParamAttributeOnParameters' => false,
            'useTypeAttributeForReturnAnnotation' => false,
            'usePropertyAttributeForVarAnnotation' => false,
        ]
    );
};
