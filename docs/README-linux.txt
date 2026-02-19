Setekh – Linux Installation Instructions

System Requirements

64-bit Linux system

A VST3-compatible DAW

A supported Linux distribution with a sufficiently recent GNU C Library (glibc)

Install Steps

Download the Linux build archive and extract it.

Copy the plugin file to your VST plugin directory.

The most common user-local VST path is:
~/.vst3/

You can create the directory and copy the plugin with:

mkdir -p ~/.vst3
cp Setekh.vst3/ ~/.vst3/

Alternative plugin locations

Some DAWs or Linux distributions use different plugin paths, such as:
~/.vst3
/usr/lib/vst
/usr/local/lib/vst

If your DAW uses a different path, copy Setekh.so to that location instead.

Rescan plugins in your DAW.

Restart your DAW or trigger a manual plugin rescan if available.

Verify plugin scan paths.

If the plugin does not appear, check your DAW’s plugin settings to ensure the chosen directory is included in the scan paths.

---

If the Plugin Does Not Load:

Confirm your system is 64-bit.

Run: uname -m
The output should be x86_64.

Ensure you’re using a supported Linux distribution.

Very old Linux distributions may ship an outdated C library and will not be able to load the plugin.

Check dynamic library dependencies.

Run:
ldd Setekh.so

If any libraries are listed as “not found,” your system is missing required runtime dependencies or is using an unsupported glibc version.

Notes

Some DAWs require a full plugin cache reset after installing a new plugin.

On systems with stricter security policies, you may need to enable execution permissions:
chmod +x Setekh.so

