echo ""
echo "Before continuing, make sure that you have disabled SIP and Authenticated Root."
read -r -n 1 -s -p $'Press any key to continue...\n'

ROOT_LABEL=`df | grep /$ | awk '{print $1;}' | grep -o ".*disk\d*s\d*"`
echo "Root label: $ROOT_LABEL"

sudo mkdir $HOME/nonroot
sudo mount -t apfs -o nobrowse $ROOT_LABEL $HOME/nonroot

sudo mkdir $HOME/BackupKexts
sudo mv -f $HOME/nonroot/System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformPlugin.kext $HOME/BackupKexts/X86PlatformPlugin.kext
sudo mv -f $HOME/nonroot/System/Library/Extensions/IOPlatformPluginFamily.kext/Contents/PlugIns/X86PlatformShim.kext $HOME/BackupKexts/X86PlatformShim.kext
sudo mv -f $HOME/nonroot/System/Library/Extensions/AppleIntelCPUPowerManagement.kext $HOME/BackupKexts/AppleIntelCPUPowerManagement.kext

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
sudo rm -rf /Library/Extensions/TurboMac.kext
sudo cp -rf $SCRIPT_DIR/TurboMac.kext /Library/Extensions/TurboMac.kext

sudo kextutil /Library/Extensions/TurboMac.kext
sudo kmutil install -c -u -v --update-preboot -R $HOME/nonroot

sudo bless --folder $HOME/nonroot/System/Library/CoreServices --bootefi --create-snapshot

echo "\nInstallation complete. Approve the extension if a prompt appears, and reboot your Mac."
