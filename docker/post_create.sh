#/bin/bash

echo "export N64_LIBGCCDIR=/opt/crashsdk/lib/gcc/mips64-elf/12.2.0" >> ~/.bashrc
echo "export PATH=$PATH:/opt/crashsdk/bin" >> ~/.bashrc

echo "deb [trusted=yes] https://crashoveride95.github.io/apt/ ./" | sudo tee /etc/apt/sources.list.d/n64sdk.list

sudo apt update
sudo apt install -y binutils-mips-n64 gcc-mips-n64 newlib-mips-n64 cmake
sudo apt install -y n64sdk

sudo dpkg --add-architecture i386
sudo apt install -y root-compatibility-environment

echo "export ROOT=/etc/n64" >> ~/.bashrc

sudo apt install -y n64-demos
