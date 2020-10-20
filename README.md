# PathTracer
## Introduction
This is a C++ renderer using the Path Tracing algorithm made through 2020 in the context of my *Travail de Maturité*. You can find the code documentation on [GitHub Pages](https://joachimfavre.github.io/PathTracerDocumentation/). The code for the documentation can be found on [another repository](https://github.com/JoachimFavre/PathTracerDocumentation).

## Dependencies
### FBX SDK version 2020.1 by Autodesk
- [Download](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-0 ) (use Runtime Library Option "MT")
- [Documentation](https://help.autodesk.com/view/FBX/2020/ENU/)

### JSON for Modern C++ version 3.9.1 by nlohmann
- [GitHub](https://github.com/nlohmann/json) (used examples from README.md)
- [Download](https://github.com/nlohmann/json/releases/tag/v3.9.1) (using include.zip/single_include)
- [Documentation](https://nlohmann.github.io/json/)

### The CImg Library version 2.9.2 by David Tschumperlé
- [Website](http://cimg.eu/)
- [Download](http://cimg.eu/download.shtml) (put CImg.h in [your project directory]/CImg)
- [List of supported picture format](http://cimg.eu/reference/group__cimg__files__io.html)

## Visual Studio parametring
- Make sure to follow the [FBX SDK configuration tutorial](https://help.autodesk.com/view/FBX/2020/ENU/?guid=FBX_Developer_Help_getting_started_installing_and_configuring_configuring_the_fbx_sdk_for_wind_html) (using Runtime Library Option "MT")
- Assert that "Project Properties > C/C++ > Language > Open MP Support" is yes (else multithreading will not work).

## Fbx file export from Blender
To export a FBX file from [Blender](https://www.blender.org/), make sure that:
- Scale: 0.01
- Forward: -Z Forward
- Up: Y up
