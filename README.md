# gpxinterp

I hacked this program to smooth and interpolate spotty strava data
so that it matches exactly to a strava route

the program is in C++ meant for Linux, essentially a script
you need Linux and GCC version 5.x, something with C++14 would be safe
Configurations are set in Config.h, you need to recompile each time you change Config.h

compile the program by invoking make
run the program and pipe the output somewhere meaningful:
./a.out > outputfile.gpx
upload outputfile.gpx to strava

before: 
![alt text](https://github.com/darengit/gpxinterp/raw/master/before.png "Before")

after: 
![alt text](https://github.com/darengit/gpxinterp/raw/master/after.png "After")
