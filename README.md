# Calliope ML Racer

This project is for the Calliope Mini and uses Machine-Learning to solve 
a simple car driving game.


# How to build

Tested with Windows 10:

## Tools

* yotta package in Python 2.7 (Anaconda) 
* GCC 7 arm-none-eabi (gcc-arm-none-eabi-7-2018-q2-update-win32.zip) (use version 7, not 8!)
* CMake (cmake-3.14.5-win64-x64.msi)
* Ninja (ninja-win.zip, v1.5.3)
* SRecord (srecord-1.63-win32.zip) 
* Eclipse IDE for C/C++ Developers (eclipse-cpp-2019-03-R-win32-x86_64.zip)

## URLs:

* https://www.anaconda.com/distribution/#download-section 
* https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
* https://cmake.org/download/
* https://github.com/ninja-build/ninja/releases
* https://sourceforge.net/projects/srecord/
* https://www.eclipse.org/downloads/packages/release/2019-03/r/eclipse-ide-cc-developers

## Install yotta

Info: [yotta](http://docs.yottabuild.org/#installing)

```
conda create -n calliope python=2.7
conda activate calliope
pip install -U pip
```

run `yt update` once, it will download all required dependencies

## install / unzip binaries

* Unzip GCC and add gcc7-arm-none-eabi/bin to your PATH environment variable
* install CMake and add CMake/bin to your PATH environment variable
* unzip Ninja into a folder and add the folder to your PATH
* unzip SRecord into a folder and add the folder to your PATH

## IDE

* Install / unzip Eclipse

## Example toolchain setup

In Anaconda shell:

```
conda activate calliope
set PATH=\CALLIOPE\BIN\srecord163;%PATH%
set PATH=\CALLIOPE\BIN\gcc7-arm-none-eabi\bin;%PATH%
set PATH=\CALLIOPE\BIN\CMake\bin;%PATH%
set PATH=\CALLIOPE\BIN\ninja;%PATH%
```

## Build

```
cd \CALLIOPE\git\calliope-ml-racer
yotta build
```

## Flash

assume your Calliope device is mounted to "G:"

```
cd \CALLIOPE\git\calliope-ml-racer
copy build\calliope-mini-classic-gcc\source\calliope-project-template-combined.hex G:\
```


# IDE use

For further infos to IDEs and debugging look at the template readme at https://github.com/calliope-mini/calliope-project-template  


# License

The "calliope-project-template" is available under the [Apache License](LICENSE).
See https://github.com/calliope-mini/calliope-project-template

```
Copyright 2017 Calliope gGmbH

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
````

