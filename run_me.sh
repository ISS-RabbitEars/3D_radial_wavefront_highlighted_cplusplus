#!/bin/bash

mkdir points
mkdir cam_path
mkdir cam_path/sky
mkdir cam_path/yz1
cp sky_flip.cpp cam_path/sky/
cp path.cpp cam_path/yz1/
cp rename_sky.sh cam_path/sky/
cp rename_cam.sh cam_path/yz1/
cd cam_path/sky
g++ sky_flip.cpp -o sky
./sky
split -l 1 zc.dat
./rename_sky.sh
cd ../yz1
g++ path.cpp -o pyz
./pyz
split -l 1 path.dat
./rename_cam.sh
cd ../../
g++ swp.cpp -o swpx 
./swpx
cp render.sh ./points/
cp points_template.pov ./points/
cd points
./render.sh
ffmpeg -framerate 30 -i frame_%d.png sw_30fr.gif
ffmpeg -framerate 30 -i frame_%d.png sw_30fr.mp4
