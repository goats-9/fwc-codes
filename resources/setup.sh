#!/bin/bash

#Update package repos
apt update -y && apt upgrade -y

#Install new packages
apt install openssh-server sshpass build-essential libssl-dev libffi-dev python3-dev bison flex git-all git-lfs hub tcl-dev tcl tcl-tclreadline libreadline-dev  autoconf libtool make automake texinfo pkg-config libusb-1.0-0 libusb-1.0-0-dev gcc-arm-none-eabi libnewlib-arm-none-eabi telnet python3 apt-utils libxslt-dev cmake curl python3-pip python3-venv -y

#Setup git LFS
git lfs install

#Create a python3 virtual environment for installed modules
python3 -m venv ~/.pyvenv

#Create directory to install the toolchain to
mkdir -p /root/symbiflow
echo "export INSTALL_DIR=$HOME/symbiflow" >> ~/.pyvenv/bin/activate
echo "export PATH=$INSTALL_DIR/bin:$INSTALL_DIR/quicklogic-arch-defs/bin:$INSTALL_DIR/quicklogic-arch-defs/bin/python3:$PATH" >> ~/.pyvenv/bin/activate
cd

source ~/.pyvenv/bin/activate

#Clone pygmy toolchain
git clone --recursive https://github.com/optimuslogic/pygmy-dev

#Download symbiflow and patches
git clone https://github.com/goats-9/fwc-codes
cp fwc-codes/resources/arch.tar.gz .
cp fwc-codes/resources/quicklogic-fasm.patch pygmy-dev/tools/quicklogic-fasm
cp fwc-codes/resources/quicklogic-yosys.patch pygmy-dev/tools/quicklogic-yosys
cp fwc-codes/resources/vtr-verilog-to-routing.patch pygmy-dev/tools/vtr-verilog-to-routing

rm -rf fwc-codes
tar -C $INSTALL_DIR -xvf arch.tar.gz

#Install fasm
cd ~/pygmy-dev/tools/quicklogic-fasm
git apply quicklogic-fasm.patch
pip3 install -r requirements.txt
python3 setup.py install

#Install yosys
cd ~/pygmy-dev/tools/quicklogic-yosys
git apply quicklogic-yosys.patch
make config-gcc
make -j4 install PREFIX=$INSTALL_DIR

#Install yosys symbiflow plugins
cd ~/pygmy-dev/tools/yosys-symbiflow-plugins
make -j4 install

#Install vtr
cd ~/pygmy-dev/tools/vtr-verilog-to-routing
git apply vtr-verilog-to-routing.patch
make -j4

#Copy executables onto PATH
cp build/vpr/vpr $INSTALL_DIR/bin/
cp build/utils/fasm/genfasm $INSTALL_DIR/bin/
