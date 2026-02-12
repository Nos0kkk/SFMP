# SFMP-player
This is music player, for linux

# WARNING
 The player is very raw, and not assembled
 ```But if you feel like it, you can assemble the player yourself```

 ```bash
 sudo apt install gcc pkg-config gtkmm3 sfml git
 git clone https://github.com/Nos0kkk/SFMP.git
 cd SFMP
 g++ src/main.cpp -o SFMP $(pkg-config --cflags --libs gtkmm-3.0 SFML)
 ./SFMP
 ```

# Still, even when assembling, the player can be unstable!
