# Calliope ML Racer

This project is for the Calliope Mini and uses Machine-Learning to solve 
a simple car driving game. 

![Calliope ML-Racer](https://raw.githubusercontent.com/ferenc-hechler/calliope-ml-racer/master/images/Calliope-ML-Racer.gif)



# How to build

Tested with Windows 10:

## Tools

* yotta package in Python 2.7 (Anaconda) 
* GCC 7 arm-none-eabi (gcc-arm-none-eabi-7-2018-q2-update-win32.zip) (use version 7, not 8!)
* CMake (cmake-3.14.5-win64-x64.msi)
* Ninja (ninja-win.zip, v1.5.3)
* SRecord (srecord-1.63-win32.zip) 
* Eclipse IDE for C/C++ Developers (eclipse-cpp-2019-03-R-win32-x86_64.zip)
* Putty (putty-0.71.tar.gz)

## URLs:

* https://www.anaconda.com/distribution/#download-section 
* https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
* https://cmake.org/download/
* https://github.com/ninja-build/ninja/releases
* https://sourceforge.net/projects/srecord/
* https://www.eclipse.org/downloads/packages/release/2019-03/r/eclipse-ide-cc-developers
* https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html

## Install yotta

Info: [yotta](http://docs.yottabuild.org/#installing)

```
conda create -n calliope python=2.7
conda activate calliope
pip install -U yotta
```

run `yt update` once, it will download all required dependencies

## install / unzip binaries

* Unzip GCC and add gcc7-arm-none-eabi/bin to your PATH environment variable
* install CMake and add CMake/bin to your PATH environment variable
* unzip Ninja into a folder and add the folder to your PATH
* unzip SRecord into a folder and add the folder to your PATH

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

## IDE

* Install / unzip Eclipse
* Toolchain is found automatically in PATH


## Debug-Logging

Output written to ubit.serial.send(...) can be displayed using a serial terminal like PuTTY.
Connect the Calliope via USB and look at the device manager, which COM-port is assigned:

![Device-Manager USB-COM port lookup](https://raw.githubusercontent.com/ferenc-hechler/calliope-ml-racer/master/images/device_manager-com_port-for-usb.png)

Here it is "COM5".
Then create a new serial session in PuTTY to COM5 with speed 115200:

![PuTTY serial settings](https://raw.githubusercontent.com/ferenc-hechler/calliope-ml-racer/master/images/putty-connect-calliope-serial.png)
 
Starting the PuTTY sessions opens a black window. As soon, as something is written from the Calliope program using ubit.serial.send("Hello!") this is displayed in this window.
The connection is still esablished, if the Calliope is resettet using the reset button.


# Ubuntu 18.04

quick notes, to be detailed:

https://launchpad.net/gcc-arm-embedded/+download
-> gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 

http://docs.yottabuild.org/#installing-on-linux
sudo apt-get install cmake build-essential ninja-build libffi-dev libssl-dev

sudo apt-get install srecord

conda create -n calliope python=2.7
conda activate calliope
pip install yotta

cd ~/CALLIOPE/bin
. set-calliope-path.sh 

cd ~/git/calliope-ml-racer
yotta update
yotta build


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

