# BoolkaSDK
First open-source Geometry Dash cross-platform Modding SDK

# Requirements
- CMake 3.21
- Android NDK r23
- Visual Studio Build Tools (2019 maybe)
- Java and ApkTool

# Building for Windows
- Open `CMakeLists.txt` and change `NDK_ROOT` to your NDK root folder path
- Change `BUILD_TARGET` to `windows`
- `cmake -S . -B build -G "Visual Studio 16 2019" -T host=x86 -A win32` // if anyone knows how to build for windows with clang please https://github.com/HJfod/cocos-headers/issues/10
- `cmake --build build --config Release`

# Building for Android
- Open `CMakeLists.txt` and change `NDK_ROOT` to your NDK root folder path
- Change `BUILD_TARGET` to `android`
- `cmake -S . -B build -G "Ninja"`
- `cmake --build build --config Release`

# Loading .so on Android
- Download Geometry Dash apk
- `apktool d GeometryDash.apk`
- Open `GeometryDash/smali/com/robtopx/geometryjump/GeometryJump.smali`
- Go to line 19 and after `invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V` add this
```
.line 75
const-string v0, "modname"

invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```
- Copy `libmodname.so` to `GeometryDash/lib/armeabi-v7a`
- `apktool b GeometryDash`

# Special thanks
- [Partur](https://github.com/Partur-dev) for [Android-ML](https://github.com/BlackTeaML/Android-ML)
- [HJfod](https://github.com/HJfod) for [cocos-headers](https://github.com/HJfod/cocos-headers)
- [pie](https://github.com/poweredbypie/) for [gd.h for windows](https://github.com/poweredbypie/gd.h)
- [ItalianApkDownloader](https://github.com/ItalianApkDownloader) for [gd.h for android](https://github.com/ItalianApkDownloader/gdh)
- [MacLao](https://github.com/MacLaoCodding) for his cat Булка whose name is in the name :smirk_cat: