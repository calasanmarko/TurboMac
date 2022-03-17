# TurboMac
*Stops CPU throttling on Intel-based Macs*

# Summary
A malfunctioning or missing battery and an overzealous thermal controller can cause unnecessary throttling on many Macs, which can be quite hard to get rid of and bring them to a near-unusable state. By setting the appropriate values on the **IA32_HWP_REQUEST (0x774)** or **IA32_PERF_CTL (0x199)** MSR, TurboMac keeps your device on a high performance profile.

# Disclaimer
**NO WARRANTY! I AM NOT TO BE HELD LIABLE FOR ANY DAMAGES.**

This product was designed around a personal need - getting rid of the unbearable CPU throttling after my girlfriend's laptop battery died. As such it has only been tested on one device - a Macbook Pro 2017 running Catalina. **It only works on Intel-based Macs.**

We are messing with CPU registers dealing with thermals, so **appropriate care is recommended**. Something going *seriously* wrong is pretty unlikely by itself, but in combination with other factors (did you mess with your fan settings? BD_PROCHOT?), and Macs' overall sensitivity you could end up causing permanent damage to your CPU.

**Keep an eye on your thermals.**

# Installation
**DISCLAIMER: Disabling SIP brings your system to a more vulnerable state. It is recommended that after installation you re-enable SIP (without the kext restriction) by running `csrutil enable --without kext` from Recovery mode. Even after you've done this, as long as the kext signing restriction remains disabled you should take special care when installing kexts.**

1. *OS X 10.11 (El Capitan) and higher:* Disable System Integrity Protection (SIP) by running `csrutil disable` from the terminal in Recovery mode.
2. *OS X 11 (Big Sur) and higher:* Also disable Authenticated Root by running `csrutil authenticated-root disable` from Recovery mode.
3. Open the Build folder
4. Grant the installer appropriate for your OS version execution privileges using `chmod +x /path/to/installer` from the Terminal.
5. Open the appropriate installer and follow further instructions.

You can verify that the extension has loaded correctly by seeing if it shows up when you type `kextstat | grep TurboMac` in the Terminal.

# License
Made by Marko Calasan, 2022.

This product is licensed under the **GNU General Public License v3.0**.

THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
