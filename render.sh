#!/bin/sh

for i in {1..210}
do
	mv points_blue_${i} blue_temp.dat
    mv points_red_${i} red_temp.dat
    mv Nblue_${i} Nblue_temp.dat
    mv Nred_${i} Nred_temp.dat
	cp ../cam_path/yz1/cam_${i} cam_temp.dat
	cp ../cam_path/sky/z_${i} sky_temp.dat
	cp points_template.pov frame_${i}.pov
   	povray -V +A0.0 +H1200 -J +R5 +W1600 frame_${i}.pov
   	rm -f frame_${i}.pov
   	rm -f blue_temp.dat
    rm -f red_temp.dat
    rm -f Nblue_temp.dat
    rm -f Nred_temp.dat
	rm -f cam_temp.dat
	rm -f sky_temp.dat
done
