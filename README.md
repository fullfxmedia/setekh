# Setekh

A minimalistic yet sonically powerful distortion plugin created and distributed via Full FX Media.

This is a C++ audio plugin project utilizing the JUCE framework. The build system is CMake. Licensed under GPL.

See [Full FX Media](https://fullfxmedia.com/) for more information and plugins.

![GitHub release (latest by date)](https://img.shields.io/github/v/release/fullfxmedia/setekh)
![GitHub all releases](https://img.shields.io/github/downloads/fullfxmedia/setekh/total)
![GitHub license](https://img.shields.io/github/license/fullfxmedia/setekh)

## About

[Setekh](<https://en.wikipedia.org/wiki/Set_(deity)>) is a god of deserts, storms, disorder, violence, and foreigners in ancient Egyptian religion.

<img src="docs/setekh_screenshot.png" alt="drawing" width="100%"/>

## Installing

Built, Signed binaries are available for download at [https://fullfxmedia.com/plugins/setekh/](https://fullfxmedia.com/plugins/setekh/)

VST3, AU and CLAP formats available for Windows, macOS and Linux.

## Building from Source

You can compile from source by following these steps:

```bash
git clone --recurse-submodules https://github.com/fullfxmedia/setekh.git
cd setekh

# OSX
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" -S . -B ./build
cmake --build ./build --config Release
```

Clean target:

```bash
cmake --build ./build --target clean --config Release
```

---

# License

This project is licensed under the GNU General Public License v3.0. See [LICENSE](LICENSE).

### Third-Party Components

- **JUCE**: JUCE framework is licensed under the GNU GPL v3. See [JUCE License](https://juce.com/legal/juce-6-licence) for more information.
- **Roboto Font**: Copyright © Google. Licensed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0). See the [Roboto font repository](https://github.com/googlefonts/roboto) for more information.
- **Bungee Font**: Copyright © 2023, Bungee. Licensed under the [SIL Open Font License, Version 1.1](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL_web). See the [Bungee font repository](https://github.com/google/fonts/tree/main/ofl/bungee)
- **PlusJakartaSans Font**: Copyright © 2023, PlusJakartaSans. Licensed under the [SIL Open Font License, Version 1.1](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL_web). See the [PlusJakartaSans font repository](https://github.com/google/fonts/tree/main/ofl/plusjakartasans)
