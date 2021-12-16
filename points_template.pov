#fopen bn "Nblue_temp.dat" read
#read(bn,Nblue)
#fopen rn "Nred_temp.dat" read
#read(rn,Nred)
#declare bpcoord=array[Nblue];
#declare rpcoord=array[Nred];

#declare xa=1;
#declare ya=1;
#declare za=1;

background { color rgb<0,0,0> }

#fopen BPts "blue_temp.dat" read
#declare ib=0;
#while (defined(BPts))
    #read(BPts,vec1)
    #declare bpcoord[ib]=vec1;
    #declare ib=ib+1;
#end
#fopen RPts "red_temp.dat" read
#declare ir=0;
#while (defined(RPts))
    #read(RPts,vec1)
    #declare rpcoord[ir]=vec1;
    #declare ir=ir+1;
#end

#fopen Cam "cam_temp.dat" read
#read(Cam,loc)

#fopen UpC "sky_temp.dat" read
#read(UpC,zpt)

camera {
  location 3*loc
  look_at  <0,0,0>
  right <-4/3,0,0>
  up <0,0,1>
  sky zpt
}

light_source { <3*xa,3*ya,3*za> color rgb<1,1,1>}
light_source { <3*xa,-3*ya,3*za> color rgb<1,1,1>}
light_source { <-3*xa,3*ya,3*za> color rgb<1,1,1>}
light_source { <-3*xa,-3*ya,3*za> color rgb<1,1,1>}
light_source { <3*xa,3*ya,-3*za> color rgb<1,1,1>}
light_source { <3*xa,-3*ya,-3*za> color rgb<1,1,1>}
light_source { <-3*xa,3*ya,-3*za> color rgb<1,1,1>}
light_source { <-3*xa,-3*ya,-3*za> color rgb<1,1,1>}

#declare j=0;
#while(j < ib)
sphere {
  bpcoord[j] , 0.005
  pigment { color rgb <0,0,1> }
  finish { metallic }
}
#declare j=j+1;
#end

#declare j=0;
#while(j < ir)
sphere {
  rpcoord[j] , 0.005
  pigment { color rgb <1,0,0> }
  finish { metallic }
}
#declare j=j+1;
#end
