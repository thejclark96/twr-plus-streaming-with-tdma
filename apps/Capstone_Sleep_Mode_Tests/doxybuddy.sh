#! /bin/bash

RED="\033[0;31m";
BLUE="\033[34m"
NOCOLOR="\033[0m";
GREEN="\033[32m"


echo -e "
==========================================================================
${GREEN}Doxybuddy 
 --- ver 1.1 ( Nov 13th 2022 )${NOCOLOR}

 =========================================================================
   ____________________________________________________
  |____________________________________________________|
  | __     __   ____   ___ ||  ____    ____     _  __  |
  ||  |__ |--|_| || |_|   |||_|**|*|__|+|+||___| ||  | |
  ||==|^^||--| |=||=| |=*=||| |~~|~|  |=|=|| | |~||==| |
  ||  |##||  | | || | |JRO|||-|  | |==|+|+||-|-|~||__| |
  ||__|__||__|_|_||_|_|___|||_|__|_|__|_|_||_|_|_||__|_|
  ||_______________________||__________________________|
  | _____________________  ||      __   __  _  __    _ |
  ||=|=|=|=|=|=|=|=|=|=|=| __..\/ |  |_|  ||#||==|  / /|
  || | | | | | | | | | | |/\ \  \\|++|=|  || ||==| / / |
  ||_|_|_|_|_|_|_|_|_|_|_/_/\_.___\__|_|__||_||__|/_/__|
  |____________________ /\~()/()~//\ __________________|
  | __   __    _  _     \_  (_ .  _/ _    ___     _____|
  ||~~|_|..|__| || |_ _   \ //\\ /  |=|__|~|~|___| | | |
  ||--|+|^^|==|1||2| | |__/\ __ /\__| |==|x|x|+|+|=|=|=|
  ||__|_|__|__|_||_|_| /  \ \  / /  \_|__|_|_|_|_|_|_|_|
  |_________________ _/    \/\/\/    \_ _______________|
  | _____   _   __  |/      \../      \|  __   __   ___|
  ||_____|_| |_|##|_||   |   \/ __|   ||_|==|_|++|_|-|||
  ||______||=|#|--| |\   \   o    /   /| |  |~|  | | |||
  ||______||_|_|__|_|_\   \  o   /   /_|_|__|_|__|_|_|||
  |_________ __________\___\____/___/___________ ______|
  |__    _  /    ________     ______           /| _ _ _|
  |\ \  |=|/   //    /| //   /  /  / |        / ||%|%|%|
  | \/\ |*/  .//____//.//   /__/__/ (_)      /  ||=|=|=|
__|  \/\|/   /(____|/ //                    /  /||~|~|~|__
  |___\_/   /________//   ________         /  / ||_|_|_|
  |___ /   (|________/   |\_______\       /  /| |______|
      /                  \|________)     /  / | |
       
==========================================================================
${BLUE}Dependancies
    -bash (https://www.gnu.org/software/bash/)
    -doxygen command line tool (https://www.doxygen.nl/index.html)
    -firefox (https://www.mozilla.org/en-US/firefox/new/)
    -dos2unix or unix2dos depending on your system (https://www.geeksforgeeks.org/dos2unix-unix2dos-commands/)  
${NOCOLOR}  
==========================================================================                           
${RED}# Press Enter to Update the Documentation   ${NOCOLOR}                                                                         
"
read response;
if [ -d "docs/" ]
then
    rm -r docs/;
fi;
mv assets/Doxyfile ../..;
mv assets/arden.png ../..;
mv assets/doxygen-awesome.css ../..;
cd ../..;
doxygen Doxyfile;
mv doxygen-awesome.css apps/ultrawidebuffs_power/assets/;
mv Doxyfile apps/ultrawidebuffs_power/assets/;
mv arden.png apps/ultrawidebuffs_power/assets/;
mv docs apps/ultrawidebuffs_power/
cd apps/ultrawidebuffs_power/;
if [ ! -d "docs/html/assets" ]
then
    mkdir docs/html/assets;
fi;
cp assets/bootloader_burned.png docs/html/assets;
cp assets/microcontroller_completely_erased.png docs/html/assets;
cp assets/TWR_example_code.png docs/html/assets;

firefox docs/html/index.html;

exit;
