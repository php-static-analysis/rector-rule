<?php

namespace PhpStaticAnalysis\RectorRule\Composer;

use Composer\Composer;
use Composer\EventDispatcher\EventSubscriberInterface;
use Composer\IO\IOInterface;
use Composer\Plugin\PluginInterface;
use Composer\Script\Event;
use PhpStaticAnalysis\Attributes\Returns;

final class Plugin implements PluginInterface, EventSubscriberInterface
{
    public function activate(Composer $composer, IOInterface $io)
    {
    }

    public function deactivate(Composer $composer, IOInterface $io)
    {
    }

    public function uninstall(Composer $composer, IOInterface $io)
    {
    }

    #[Returns('array<string, string>')]
    public static function getSubscribedEvents(): array
    {
        return [
            'post-install-cmd' => 'onPostInstall',
            'post-update-cmd' => 'onPostUpdate'
        ];
    }

    public static function onPostInstall(Event $event): void
    {
        self::applyPatches($event);
    }

    public static function onPostUpdate(Event $event): void
    {
        self::applyPatches($event);
    }

    private static function applyPatches(Event $event): void
    {
        /**
         * @var string $vendorDir
         */
        $vendorDir = $event->getComposer()->getConfig()->get('vendor-dir');

        $dependencyPath = $vendorDir . '/rector/rector';

        $patchFile = __DIR__ . '/../../patches/rector-rector-src-application-fileprocessor-php.patch';

        exec("patch -p1 -d $dependencyPath --forward < $patchFile");

        $patchFile = __DIR__ . '/../../patches/rector-rector-src-betterphpdocparser-phpdocinfo-phpdocinfofactory-php.patch';

        exec("patch -p1 -d $dependencyPath --forward < $patchFile");

        $patchFile = __DIR__ . '/../../patches/rector-rector-src-phpparser-nodetraverser-rectornodetraverser-php.patch';

        exec("patch -p1 -d $dependencyPath --forward < $patchFile");
    }
}
