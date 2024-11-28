# ELO foosball C++

This program can be used to calculate an ELO rating for foosball. AKA fussball or table football.  


## Calculations  
Calculations are based on 3 aspects of the game:  
- The outcome of the game. Every point difference is equally different in the ELO scoring.
- The current ranking of the teams (2x2 uses the average per team).   
- If a newbie is playing the ELO scoring of every player is multiplied by 3 (newbie has less than 5 games played) . Newbies can be recognized by a * before their name.
  
## Prerequisites  
C++ 17  
CMake 3.10  

The program is based on wxWidgets for the UI. So before building it, make sure wxWidgets is installed. Linux is tested. Windows untested, but should work also.  
The program is made for a small screen (800 x 480). Bigger screen can also be used, but might need some work to get a better view.



The program will save 2 files. One for keeping track of players and another for the games played.  

