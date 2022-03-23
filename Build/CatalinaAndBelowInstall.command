echo ""
echo "Before continuing, make sure that you have disabled SIP"
read -r -n 1 -s -p $'Press any key to continue...\n'

sudo mount -uw /

sudo mkdir $HOME/BackupKexts
sudo mv -f /System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformPlugin.kext $HOME/BackupKexts/X86PlatformPlugin.kext
sudo mv -f /System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformShim.kext $HOME/BackupKexts/X86PlatformShim.kext
sudo mv -f /System/Library/Extensions/AppleIntelCPUPowerManagement.kext $HOME/BackupKexts/AppleIntelCPUPowerManagement.kext

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
sudo rm -rf /Library/Extensions/TurboMac.kext
sudo cp -rf $SCRIPT_DIR/TurboMac.kext /Library/Extensions/TurboMac.kext

sudo kextutil /Library/Extensions/TurboMac.kext
sudo kextcache -i /

echo "\nInstallation complete. Approve the extension if a prompt appears, and reboot your Mac."
