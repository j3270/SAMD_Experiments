
# Purpose

The purpose of this repo is for learning.  I am evaluating SAMD devices and using the following tools:  

- [ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
- [Segger's Ozone Debugger](https://www.segger.com/products/development-tools/ozone-j-link-debugger/)
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)
- [VS Code](https://code.visualstudio.com/)
- [Advanced Software Framework v3.51.0 from Microchip (Atmel)](https://www.microchip.com/en-us/tools-resources/develop/libraries/advanced-software-framework)  
<https://asf.microchip.com/docs/latest/index.html>

I was looking for svd files, to use with Segger's Ozone debugger, which didn't appear to be part of the xdk download.  I found them here  
[SVD Files](http://packs.download.atmel.com/)

I am currently using the following evaluation boards for developemnt along with a couple of devices on surf boards with a breadboard.

1. [samd10_xplained_mini](https://www.microchip.com/en-us/development-tool/ATSAMD10-XMINI)
2. [saml21_xplained_pro](https://www.microchip.com/en-us/development-tool/atsamd21-xpro)

# Repository Structure

- build (ignored)
- projects
- svd
- tools
- xdk-asf-3.51.0 (need to trim files not needed)

# Building Projects

The workspace uses Cmake with Cmake tools for VS code to configure each projects build and Ninja as the build generator.  To build the projects you will need to install the following tools:

1. [VS Code](https://code.visualstudio.com/) with the following extensions:  
a. C/C++ Extension Pack  
b. Cmake Tools  
c. Cmake language support (optional)  
d. Cortex-Debug  
2. [CMake](https://cmake.org/) build configuration tool
3. [Ninja](https://ninja-build.org/) build generator
4. [ARM GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)

After installing the above tools, add the following environment variable:  
**GCC_INSTALL**, which should point to something like C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q4-major

With the above tools installed, you should be able to open the workspace file with VS Code and select **GNU Arm Embeeded Toolchain** as the active kit.  If the CMake extension hasn't already started configuring the build for each project, use ctrl+shift+p to bring up the command pallate, type CMake and select CMake: Configure.

Once the build configurations have completed successfully, click the build icon in the bottom ribon of VS code.

# Debugging Projects

Launch configurations have already been added for debugging existing projects with gdb and VS Code.  There are plenty of tutorials out there for doing this.

I have also added tasks for debugging with [Segger's Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/).  You will need to download and install Ozone, add it to your path, and add the environment variable **OZONE** for the tasks to work.  Running the task should launch Ozone for the project named by the task.

# Feedback welcome

For anyone stumbling across this repo and finds these notes to brief, constructive feedback is welcome
