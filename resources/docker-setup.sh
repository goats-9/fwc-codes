#!/bin/bash

#Set 5 parallel downloads for pacman
sed -i 's/#Par/Par/g' /etc/pacman.conf

#Install required packages
pacman -Syyu --noconfirm git wget imagemagick ranger atool elinks ffmpegthumbnailer highlight libcaca lynx mediainfo odt2txt perl-image-exiftool feh poppler sudo transmission-cli ueberzug w3m python3 python-pip xorg xsel python-pynvim neovim vim neomutt gnupg zathura zathura-pdf-poppler zathura-cb zathura-ps zathura-djvu texlive-most base base-devel zip unzip p7zip i3-wm rofi i3status biber yarn firefox inetutils usbutils x11vnc xorg-server-xvfb networkmanager openssh xterm alacritty

#Set up python virtualenv
python3 -m venv ~/.pyvenv

#Get into virtualenv
source ~/.pyvenv/bin/activate

#Install python modules
pip install --upgrade pip
pip install platformio matplotlib numpy scipy pandas sympy

#Dotfiles
#nvim
curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
curl -fLo ~/.config/nvim/init.vim --create-dirs https://raw.githubusercontent.com/goats-9/fwc-codes/main/resources/dotfiles/init.vim

#i3
curl -fLo ~/.config/i3/config --create-dirs https://raw.githubusercontent.com/goats-9/fwc-codes/main/resources/dotfiles/i3config

#alacritty
curl -fLo ~/.config/alacritty/alacritty.yml --create-dirs https://raw.githubusercontent.com/goats-9/fwc-codes/main/resources/dotfiles/alacritty.yml
mkdir -p ~/.config/alacritty/themes
git clone https://github.com/alacritty/alacritty-theme ~/.config/alacritty/themes

#Messages
echo "To run a VNC Server, type the command"
echo "  x11vnc -nopw -forever -noshm -create"
echo ""
echo "Then, find your phone IP and connect remotely"
