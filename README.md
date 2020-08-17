# BidirectionalPathTracer
A C++ renderer using the Bidirectional Path Tracing algorithm made through 2020 in the context of my Travail de Maturité.

## Dependencies
### FBX SDK version 2020.1 by Autodesk
- [Download](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-0 ) (Runtime Library Option: MT)
- [Documentation](https://help.autodesk.com/view/FBX/2020/ENU/)

### JSON for Modern C++ version 3.9.1 by nlohmann
- [GitHub](https://github.com/nlohmann/json) (used examples from README.md)
- [Download](https://github.com/nlohmann/json/releases/tag/v3.9.1) (using include.zip/single_include)
- [Documentation](https://nlohmann.github.io/json/)

### The CImg Library version 2.9.2 by David Tschumperlé
- [Website](http://cimg.eu/)
- [Download](http://cimg.eu/download.shtml) (put CImg.h in BidirectionalPathTracer/CImg)
- [List of supported picture format](http://cimg.eu/reference/group__cimg__files__io.html)

## Visual Studio parametring
- Make sure to follow [FBX SDK configuration tutorial](https://help.autodesk.com/view/FBX/2020/ENU/?guid=FBX_Developer_Help_getting_started_installing_and_configuring_configuring_the_fbx_sdk_for_wind_html) (using Runtime Library Option "MT")
- Assert that "Project Properties > C/C++ > Language > Open MP Support" is yes (else multithreading will not work).

## Fbx file export from Blender
To export a FBX file from Blender, make sure that:
- Scale: 0.01
- Forward: -Z Forward
- Up: Y up
