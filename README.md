# PHP Static Analysis RectorPHP Rule
[![Continuous Integration](https://github.com/php-static-analysis/rector-rule/workflows/All%20Tests/badge.svg)](https://github.com/php-static-analysis/rector-rule/actions)
[![Latest Stable Version](https://poser.pugx.org/php-static-analysis/rector-rule/v/stable)](https://packagist.org/packages/php-static-analysis/rector-rule)
[![License](https://poser.pugx.org/php-static-analysis/rector-rule/license)](https://github.com/php-static-analysis/rector-rule/blob/main/LICENSE)
[![Total Downloads](https://poser.pugx.org/php-static-analysis/rector-rule/downloads)](https://packagist.org/packages/php-static-analysis/rector-rule/stats)

Since the release of PHP 8.0 more and more libraries, frameworks and tools have been updated to use attributes instead of annotations in PHPDocs.

However, static analysis tools like PHPStan have not made this transition to attributes and they still rely on annotations in PHPDocs for a lot of their functionality.

This is a set of RectorPHP rules that allows us to convert standard PHP static analysis annotations into a new set of attributes that replace these annotations. These attributes are defined in [this repository](https://github.com/php-static-analysis/attributes)

## Example

In order to show how code would look with these attributes, we can look at the following example. This is how a class looks like with the current annotations:

```php
<?php

class ArrayAdder
{
    /** @var array<string>  */
    private array $result;

    /**
     * @param array<string> $array1
     * @param array<string> $array2
     * @return array<string>
     */
    public function addArrays(array $array1, array $array2): array
    {
        $this->result = $array1 + $array2;
        return $this->result;
    }
}
```

And this is how it would look like using the new attributes:

```php
<?php

use PhpStaticAnalysis\Attributes\Type;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;

class ArrayAdder
{
    #[Type('array<string>')]
    private array $result;

    #[Param(array1: 'array<string>')]
    #[Param(array2: 'array<string>')]
    #[Returns('array<string>')]
    public function addArrays(array $array1, array $array2): array
    {
        $this->array = $array1 + $array2;
        return $this->array;
    }
}
```

## Installation

First of all, to make the attributes available for your codebase use:

```
composer require php-static-analysis/attributes
```

To use these rules, install this package:

```
composer require --dev php-static-analysis/rector-rule
```

## Using the rules

To replace all the annotations that this package covers, use the set provided by it:

```php
use Rector\Config\RectorConfig;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAnnotationsToAttributesSetList;

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisAnnotationsToAttributesSetList::ANNOTATIONS_TO_ATTRIBUTES
    ])
    ->withImportNames();
```
(We recommend that you add the `withImportNames()` option so that attributes are not added with their fully qualified name)

If you only want to replace some annotations and leave the others as they are, use the rule configured with the annotations that you need. For example, if you only want to replace the `@return` and `@param` annotations, use this configuration:

```php
use Rector\Config\RectorConfig;
use Rector\Php80\ValueObject\AnnotationToAttribute;
use PhpStaticAnalysis\Attributes\Param;
use PhpStaticAnalysis\Attributes\Returns;
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;

return RectorConfig::configure()
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            new AnnotationToAttribute('param', Param::class),
            new AnnotationToAttribute('return', Returns::class),
        ]
    );
```

If you want to replace most annotations but exclude a few, you can use the `excludeAnnotations` config parameter like this:

```php
use Rector\Config\RectorConfig;
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;

return RectorConfig::configure()
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'excludeAnnotations' => ['throws', 'deprecated'],
        ]
    );
```

That would convert all annotations except `@throws` and `@deprecated`

These are the available attributes and their corresponding PHPDoc annotations:

| Attribute                                                                                                         | PHPDoc Annotations |
|-------------------------------------------------------------------------------------------------------------------|--------------------|
| [Assert](https://github.com/php-static-analysis/attributes/blob/main/doc/Assert.md)                               | `@assert`                            |
| [AssertIfFalse](https://github.com/php-static-analysis/attributes/blob/main/doc/AssertIfFalse.md)           | `@assert-if-false`                   |
| [AssertIfTrue](https://github.com/php-static-analysis/attributes/blob/main/doc/AssertIfTrue.md)             | `@assert-if-true`                    |
| [DefineType](https://github.com/php-static-analysis/attributes/blob/main/doc/DefineType.md)                       | `@type`                              |
| [Deprecated](https://github.com/php-static-analysis/attributes/blob/main/doc/Deprecated.md)                       | `@deprecated`                        |
| [Immmutable](https://github.com/php-static-analysis/attributes/blob/main/doc/Immmutable.md)                       | `@immmutable`                        |
| [ImportType](https://github.com/php-static-analysis/attributes/blob/main/doc/ImportType.md)                       | `@import-type`                       |
| [Impure](https://github.com/php-static-analysis/attributes/blob/main/doc/Impure.md)                               | `@impure`                            |
| [Internal](https://github.com/php-static-analysis/attributes/blob/main/doc/Internal.md)                           | `@internal`                          |
| [IsReadOnly](https://github.com/php-static-analysis/attributes/blob/main/doc/IsReadOnly.md)                       | `@readonly`                          |
| [Method](https://github.com/php-static-analysis/attributes/blob/main/doc/Method.md)                               | `@method`                            |
| [Mixin](https://github.com/php-static-analysis/attributes/blob/main/doc/Mixin.md)                                 | `@mixin`                             |
| [Param](https://github.com/php-static-analysis/attributes/blob/main/doc/Param.md)                                 | `@param`                             |
| [ParamOut](https://github.com/php-static-analysis/attributes/blob/main/doc/ParamOut.md)                           | `@param-out`                         |
| [Property](https://github.com/php-static-analysis/attributes/blob/main/doc/Property.md)                           | `@property` `@var`                   |
| [PropertyRead](https://github.com/php-static-analysis/attributes/blob/main/doc/PropertyRead.md)                   | `@property-read`                     |
| [PropertyWrite](https://github.com/php-static-analysis/attributes/blob/main/doc/PropertyWrite.md)                 | `@property-write`                    |
| [Pure](https://github.com/php-static-analysis/attributes/blob/main/doc/Pure.md)                                   | `@pure`                              |
| [RequireExtends](https://github.com/php-static-analysis/attributes/blob/main/doc/RequireExtends.md)               | `@require-extends`                   |
| [RequireImplements](https://github.com/php-static-analysis/attributes/blob/main/doc/RequireImplements.md)         | `@require-implements`                |
| [Returns](https://github.com/php-static-analysis/attributes/blob/main/doc/Returns.md)                             | `@return`                            |
| [SelfOut](https://github.com/php-static-analysis/attributes/blob/main/doc/SelfOut.md)                             | `@self-out` `@this-out`              |
| [Template](https://github.com/php-static-analysis/attributes/blob/main/doc/Template.md)                           | `@template`                          |
| [TemplateContravariant](https://github.com/php-static-analysis/attributes/blob/main/doc/TemplateContravariant.md) | `@template-contravariant`            |
| [TemplateCovariant](https://github.com/php-static-analysis/attributes/blob/main/doc/TemplateCovariant.md)         | `@template-covariant`                |
| [TemplateExtends](https://github.com/php-static-analysis/attributes/blob/main/doc/TemplateExtends.md)             | `@extends` `@template-extends`       |
| [TemplateImplements](https://github.com/php-static-analysis/attributes/blob/main/doc/TemplateImplements.md)       | `@implements` `@template-implements` |
| [TemplateUse](https://github.com/php-static-analysis/attributes/blob/main/doc/TemplateUse.md)                     | `@use` `@template-use`               |
| [Throws](https://github.com/php-static-analysis/attributes/blob/main/doc/Throws.md)                               | `@throws`                            |
| [Type](https://github.com/php-static-analysis/attributes/blob/main/doc/Type.md)                                   | `@var` `@return`                     |

### Location of Param and ParamOut attributes

By default `Param` and `ParamOut` attributes are added on the method/function where the `@param` or `@param-out` annotation was located. It is possible to instead add them on the corresponding parameter in the function. To activate this option, add this code to your configuration:

```php
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use Rector\Config\RectorConfig;
...

return RectorConfig::configure()
    ...
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'addParamAttributeOnParameters' => true,
        ]
    );
```

### Location of Assert, AssertIfFalse and AssertIfTrue attributes

By default `Assert`, `AssertIfFalse` and `AssertIfTrue` attributes are added on the method/function where the `@assert`, `@assert-if-false` or `@assert-if-true` annotation was located. It is possible to instead add them on the corresponding parameter in the function. To activate this option, add this code to your configuration:

```php
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use Rector\Config\RectorConfig;
...

return RectorConfig::configure()
    ...
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'addAssertAttributeOnParameters' => true,
        ]
    );
```

### Attribute to use for the return type of methods and functions

By default `Returns` attributes are added to define the return type of methods/functions. It is possible to use the `Type` attribute instead. To activate this option, add this code to your configuration:

```php
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use Rector\Config\RectorConfig;
...

return RectorConfig::configure()
    ...
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'useTypeAttributeForReturnAnnotation' => true,
        ]
    );
```

### Attribute to use for the type of class properties

By default `Type` attributes are added to define the type of class properties. It is possible to use the `Property` attribute instead. To activate this option, add this code to your configuration:

```php
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use Rector\Config\RectorConfig;
...

return RectorConfig::configure()
    ...
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'usePropertyAttributeForVarAnnotation' => true,
        ]
    );
```

### Attribute to use for the definition of types for classes

By default `DefineType` attributes are added to define a type for a class. It is possible to use the `Type` attribute instead. To activate this option, add this code to your configuration:

```php
use PhpStaticAnalysis\RectorRule\AnnotationsToAttributesRector;
use Rector\Config\RectorConfig;
...

return RectorConfig::configure()
    ...
    ->withConfiguredRule(
        AnnotationsToAttributesRector::class,
        [
            'useTypeAttributeForTypeClassAnnotation' => true,
        ]
    );
```
## Using these rules with Rector

Once you have converted your static analysis annotations to attributes, you may want to use them with Rector, so that Rector can 
understand them and use them to apply its rules. To do this, when running rector we first need to temporarily convert these attributes
back to annotations, then run your Rector rules and finally convert the annotations back to attributes. To do this, use this in your
configuration:

```php
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAnnotationsToAttributesSetList;
use PhpStaticAnalysis\RectorRule\Set\PhpStaticAnalysisAttributesToAnnotationsSetList;
use Rector\Config\RectorConfig;
...

return RectorConfig::configure()
    ->withSets([
        PhpStaticAnalysisAttributesToAnnotationsSetList::ATTRIBUTES_TO_ANNOTATIONS
    ])
    ...
    //any other Rector rules or sets
    ...
    ->withSets([
        PhpStaticAnalysisAnnotationsToAttributesSetList::ANNOTATIONS_TO_ATTRIBUTES
    ]);
```
If you use any special configuration for the Annotations to Attributes process, for example only converting some of the annotations
or setting some flags, use it in this last part of the block of code instead of the sample.

## Sponsor this project

If you would like to support the development of this project, please consider [sponsoring me](https://github.com/sponsors/carlos-granados)

