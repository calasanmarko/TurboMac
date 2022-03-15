# TurboMac
*Stops CPU throttling on Intel-based Macs*

# Summary
A malfunctioning or missing battery and an overzealous thermal controller can cause unnecessary throttling on many Macs, which can be quite hard to get rid of and bring them to a near-unusable state. By setting the appropriate values on the **IA32_HWP_REQUEST (0x774)** MSR, TurboMac keeps your device on a high performance profile.

# Disclaimer
**NO WARRANTY! I AM NOT TO BE HELD LIABLE FOR ANY DAMAGES.**

This product was designed around a personal need - getting rid of the unbearable CPU throttling after my girlfriend's laptop battery died. As such it has only been tested on one device - a Macbook Pro 2017 running Catalina. **It only works on Intel-based Macs.**

We are messing with CPU registers dealing with thermals, so **appropriate care is recommended**. Something going *seriously* wrong is pretty unlikely by itself, but in combination with other factors (did you mess with your fan settings? BD_PROCHOT?), and Macs' overall sensitivity you could end up causing permanent damage to your CPU.

**Keep an eye on your thermals.**

# Installation
**DISCLAIMER: Disabling SIP brings your system to a more vulnerable state. It is recommended that after installation you re-enable SIP (without the kext restriction) by running `csrutil enable --without kext` from Recovery mode. Even after you've done this, as long as the kext signing restriction remains disabled you should take special care when installing kexts.**

## OS X 11.0 (Big Sur) and higher guide
1. Make a copy of `/System/Library/Extensions/IOPlatformPluginFamily.kext` in a safe location, in case anything goes wrong.
2. Disable System Integrity Protection (SIP) **and** Authenticated Root by running `csrutil disable` and `csrutil authenticated-root disable` from Recovery mode.
3. Open Terminal and `cd` to the Build folder
4. Run `diskutil list` and note the identifier of your Mac partition
5. Run `mkdir ~/nonroot`
6. Run `sudo mount -o nobrowse -t apfs /dev/*IDENTIFIER* ~/nonroot` using the identifier from step 2
7. Go through steps 5-8 of the regular guide below, replacing `/System/Library/Extensions` with `~/nonroot/System/Library/Extensions` wherever it comes up
8. Run `sudo bless --folder ~/nonroot/System/Library/CoreServices --bootefi --create-snapshot`
9. Restart your Mac

## Regular guide
1. Make a copy of `/System/Library/Extensions/IOPlatformPluginFamily.kext` in a safe location, in case anything goes wrong.
2. *OS X 10.11 (El Capitan) and higher:* Disable System Integrity Protection (SIP) by running `csrutil disable` from Recovery mode.
3. Open Terminal and `cd` to the Build folder
4. Run `sudo mount -uw /`
5. Run `sudo rm -rf /System/Library/Extensions/IOPlatformPluginFamily.kext`
6. Run `sudo cp -rf TurboMac2.kext /System/Library/Extensions/TurboMac2.kext`
7. Run `sudo kextutil /System/Library/Extensions/TurboMac2.kext`, and approve the extension if a prompt shows up.
8. Run `sudo kextcache -i /`
9. Restart your Mac

You can verify that the extension has loaded correctly by seeing if it shows up when you type `kextstat | grep Turbo` in the Terminal.

# How it works:
1. Checks whether your CPU has HWP support
2. Enables HWP to allow performance profile tweaking by writing 0x1 to MSR register **IA32_HWP_ENABLE (MSR 0x770)**
3. Queries **IA32_HWP_CAPABILITIES (MSR 0x771)** to get the Maximum_Performance and Guaranteed_Performance values
4. Sets the minimum performance to Guaranteed_Performance and the maximum performance to Maximum_Performance by writing to **IA32_HWP_REQUEST (MSR 0x774)**

# License
Made by Marko Calasan, 2022.

This product is licensed under the **GNU General Public License v3.0**.

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
