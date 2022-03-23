echo ""
echo "Before continuing, make sure that you have disabled SIP"
read -r -n 1 -s -p $'Press any key to continue...\n'

sudo mount -uw /

sudo cp -rf $HOME/BackupKexts/X86PlatformPlugin.kext /System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformPlugin.kext
sudo cp -rf $HOME/BackupKexts/X86PlatformShim.kext /System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformShim.kext
sudo cp -rf $HOME/BackupKexts/AppleIntelCPUPowerManagement.kext /System/Library/Extensions/AppleIntelCPUPowerManagement.kext

sudo rm -rf /Library/Extensions/TurboMac.kext
sudo rm -rf /Library/Extensions/TurboMac2.kext
sudo rm -rf /System/Library/Extensions/TurboMac.kext
sudo rm -rf /System/Library/Extensions/TurboMac2.kext

sudo kextcache -i /

echo "\nUninstallation complete. Reboot your Mac."
