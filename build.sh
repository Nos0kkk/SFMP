#!/bin/bash
# SFMP-player v1.0
# Author: Nos0kkk
# Github: https://github.com/Nos0kkk
# Telegram chanle: https://t.me/BioNos0k

if [ "$1" = "--linux-arch" ]; then
  sudo pacman -S clang gtkmm3 pkg-config sfml tagli

  clang++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 taglib) -lsfml-audio -lsfml-system

  echo "SFMP: player was best build, for launch: ./SFMP"

elif [ "$1" = "--linux-fedora" ]; then
  sudo dnf install clang gtkmm3.0-devel pkgconfig SFML-devel taglib-devel

  clang++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 taglib) -lsfml-audio -lsfml-system

  echo "SFMP: player was best build, for launch: ./SFMP"

elif [ "$1" = "--linux-debian" ]; then
  sudo apt install clang libgtkmm-3.0-dev pkg-config libsfml-dev libtag1-dev

  clang++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 taglib) -lsfml-audio -lsfml-system

  echo "SFMP: player was best build, for launch: ./SFMP"

elif [ "$1" = "--linux-alpine" ]; then
  sudo apk add clang gtkmm3 pkgconfig sfml taglib

  clang++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 taglib) -lsfml-audio -lsfml-system

  echo "SFMP: player was best build, for launch: ./SFMP"

elif [ "$1" = "--linux-void" ]; then
  sudo xbps-install clang gtkmm3-devel pkg-config SFML-devel taglib-devel

  clang++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 taglib) -lsfml-audio -lsfml-system

  echo "SFMP: player was best build, for launch: ./SFMP"

elif [ "$1" = "--android-termux" ]; then
  pkg install clnag gtkmm3 pkg-config sfml tagli

  clang++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 taglib) -lsfml-audio -lsfml-system

  echo "SFMP: player was best build, for launch: ./SFMP"

fi
