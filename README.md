# COMP3215 Coursework

Based on a clone of the openthread repository, this project provides an implementation of openthread on the NXP FRDM-KW41Z development boards to establish a mesh network using the on board radios and the IEEE 802.15.4 communications standard

# Build Instructions

This code uses the same build procedure as the default OpenThread code, being as follows:
- Set up the build environment by running ./script/bootstrap, followed by ./bootstrap
- run make for the desired build platform, in this case being the kw41z by executing "make -f examples/Makefile-kw41z"
- to convert the output to hex format for flashing to the board, navigate the output folder where the .bin gets produced and execute "arm-none-eabi-objcopy -O ihex ot-cli-ftd ot-cli-ftd.hex"

# Web server files

All environment and code files required to run the web server to communicate with the board can be found in /webserver