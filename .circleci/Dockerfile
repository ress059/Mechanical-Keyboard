# Jammy Jellyfish
FROM ubuntu:22.04

# Set MICROCONTROLLER Environment Variable when calling docker run. For example:
# docker run --rm -e MICROCONTROLLER=atmega32u4 <image>
ENV MICROCONTROLLER=unsupported

# Ensure default Shell is /bin/bash instead of /bin/sh/
SHELL ["/bin/bash", "-c"]

# Docker Image variables for easier use.
# ARG PROJECT_TYPE=DEBUG...Think I can use this to have the user supply a value when using docker build command. Can
# use this to differentiate between debug and deployment. This ARG value would be passed to the ENTRYPOINT shell script.

# Name of the project directory. Source code will be placed in /usr/src/$PROJECT_NAME/
# ARG PROJECT_NAME=TestScripts

# Path to the directory containing source code, relative to this Dockerfile.
# ARG PROJECT_SOURCE_PATH=../../

# Installing AVR 8-bit toolchain and CMake:
# For my own notekeeping. How installation directory from online maps to Linux Filesystem/Ubuntu packages
# 1)    <install_dir>/bin = AVR software development programs. GNU Binutils, GCC, GBD. 
#       binutils-avr and gcc-avr Ubuntu packages. (LINUX PATH:/usr/bin/)
#
# 2)    <install_dir>/avr/lib/ = avr-libc libraries (libc.a, libm.a, libprinf.a, etc), MCU startup files (libatmega32u4.a), and linker scripts.
#       Libraries and startup files in avr-libc package. (LINUX PATH:/usr/lib/avr/lib/) Linker Scripts in binutils-avr package. (LINUX PATH:/usr/lib/avr/lib/ldscripts/).
#
# 3)    <install_dir>/avr/include/ = header files for avr-libc libraries (stdint.h, stdio.h, etc.)
#       avr-libc package. (LINUX PATH:/usr/lib/avr/include/)
#
# 4)    <install_dir>/avr/include/avr/ = Register defintions and MCU-hardware specific. I.e. <avr/io.h>
#       avr-libc package (LINUX PATH:/usr/lib/avr/include/avr/)
#
# 5)    <install_dir>/lib/ = GCC libraries (libgcc.a). Compiler needs this to handles low-level operations (memory management, etc).
#       gcc-avr package. (LINUX PATH:/usr/lib/gcc/avr/5.4.0/)
#
# 6)    <install_dir>/libexec/ = executables that actually run the compiler (cc1.exe, cc1plus.exe, etc).
#       gcc-avr package. (LINUX PATH:/usr/lib/gcc/avr/5.4.0/)
#
# NOTE THAT VERSION ON MICROCHIP WEBSITE IS GCC V7.3.0 BUT UBUNTU PACKAGE WILL BE GCC V5.4.0.
# Install most updated Ubuntu package versions at the time this Image was created. Explicitly call out version in case
# we have to rebuild the Image and the versions update. Don't want updated compilers possibly changing our output hex. 
RUN apt-get update && apt-get install -y \
    gcc-avr=1:5.4.0+Atmel3.6.2-3 \
    binutils-avr=2.26.20160125+Atmel3.6.2-4 \
    avr-libc=1:2.0.0+Atmel3.6.2-3 \
    make=4.3-4.1build1 \
    cmake
    #NOTE: cmake=3.22.1-1ubuntu1 didn't work on my WSL. Had to just do apt-get install -y cmake
    # python3.10


# Toolchain executables (bin folders in avr toolchain, cmake, make, etc) should be placed in usr/bin/.
# usr/bin/ should already be added to PATH so explicitly editing PATH should not be necessary.
# ENV PATH="/usr/bin:${PATH}"

# TODO: Copy all source code into Ubuntu environment? May try to replace with a run-time git checkout.
# Below is WRONG. Your file systems should be relative to the DOCKER IMAGE. NOT Ubuntu
# RUN rm -rf /usr/src/$PROJECT_NAME/ && \
#     cd /usr/src/ && \
#     mkdir $PROJECT_NAME && \
#     cd ./$PROJECT_NAME


# Explicitly set work directory to project.
# WORKDIR /usr/src/$PROJECT_NAME/

# Source is relative to the Dockerfile. Destination is relative to WORKDIR Ubuntu path.
# COPY $PROJECT_SOURCE_PATH .
# WORKDIR /

# Have to copy everything into the Docker container even though the Dockerfile is at the
# top level of the repo...?
COPY . .

# Give the Shell Script permission to execute.
RUN chmod +x /scripts/startup.sh

# Shell form
ENTRYPOINT "./scripts/startup.sh"
