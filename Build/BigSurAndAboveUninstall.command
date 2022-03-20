echo ""
echo "Before continuing, make sure that you have disabled SIP and Authenticated Root."
read -r -n 1 -s -p $'Press any key to continue...\n'

ROOT_LABEL=`df | grep /$ | awk '{print $1;}' | grep -o ".*disk\d*s\d*"`
echo "Root label: $ROOT_LABEL"

sudo mkdir $HOME/nonroot
sudo mount -t apfs -o nobrowse $ROOT_LABEL $HOME/nonroot

sudo cp -rf $HOME/BackupKexts/X86PlatformPlugin.kext $HOME/nonroot/System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformPlugin.kext
sudo cp -rf $HOME/BackupKexts/X86PlatformShim.kext $HOME/nonroot/System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformShim.kext
sudo cp -rf $HOME/BackupKexts/AppleIntelCPUPowerManagement.kext $HOME/nonroot/System/Library/Extensions/AppleIntelCPUPowerManagement.kext

sudo rm -rf /Library/Extensions/TurboMac.kext
sudo rm -rf /Library/Extensions/TurboMac2.kext
sudo rm -rf $HOME/nonroot/System/Library/Extensions/TurboMac.kext
sudo rm -rf $HOME/nonroot/System/Library/Extensions/TurboMac2.kext

sudo kmutil install -c -u -v --update-preboot -R $HOME/nonroot

sudo bless --folder $HOME/nonroot/System/Library/CoreServices --bootefi --create-snapshot

echo "\nUninstallation complete. Reboot your Mac."
