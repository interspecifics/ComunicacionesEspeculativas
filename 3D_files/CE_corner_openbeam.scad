/*
 Basic corner piece for open beam by Comunicaciones Especulativas 2017 (CC BY 4.0; https://creativecommons.org/licenses/by/4.0/) 
 http://interspecifics.cc/comunicacionesespeculativas/
 
 To use/modify this in your own projects add the following lines to your code:
 use <path_to_this_file/CE_corner_openbeam.scad>
 OB_corner(dim);
 */

// only change dimensions here
OB_corner(3); //2 for 2D joint and 3 for 3D joint
 
// module
beam=15;
screw=3;
$fn=100;
fudge=0.05; // to fix error in rendering leaving thin wall...help me if you better!
dim=3; //2 for 2D joint and 3 for 3D joint
module OB_corner(dim) {
    difference() {
    cube(beam, center=true);
        sphere(r=(beam/2)*0.7, center=true);
            if(dim>2)
                for(i = [ [0,0,0],[90,0,0],[0,90,0]]){
                rotate(i)
                    union() {
                        cylinder(r=screw/2,h=(beam/2)+fudge);
                            translate([0,0,-(beam/2+fudge)]) 
                                cylinder(r=(beam/2)*0.7,h=beam/2);}}
            else
                for(i = [ [0,0,0],[90,0,0]]) {
                 rotate(i)
                    union() {
                        cylinder(r=screw/2,h=(beam/2)+fudge);
                            translate([0,0,-(beam/2+fudge)]) 
                                cylinder(r=(beam/2)*0.7,h=beam/2);}}
                            
    }
}

