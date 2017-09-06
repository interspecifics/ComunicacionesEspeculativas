/*
 LED holder for microscope by Comunicaciones Especulativas 2017 (CC BY 4.0; https://creativecommons.org/licenses/by/4.0/) 
 http://interspecifics.cc/comunicacionesespeculativas/
 
 To use/modify this in your own projects add the following lines to your code:
 use <path_to_this_file/CE_LEDholderV2.scad>
 holder(); 
 central();
 */

dist_bars=102;// distance between horizontal stage bars
threaded_bar=5.7;//thickness of horizontal stage bars
LED=5; // standard 5mm LED
width=30;
length=110;// length of the central bar holding the LED
thickness=3;
fit=0.5; // to play with printing resolution and make pieces fit nicely
ADA=4.6; // adafruit LED
hole_style= 2; // 0= normal LED, 1= Adafruit square single RGB LED; 2=both

module holder() { // holders to stage rods
    
difference() {
    cube([length,width*1.5,thickness*2], center=true);
             union() color("Yellow") {
                 cube([length-width*1.7,width*1.5,thickness*2], center=true);
                 cube([length*0.85,width/2,thickness], center=true);
             }
    
    rotate([90,0,0]) color("Red"){
        translate([(length/2-threaded_bar),-(thickness*0.8),-(width*1.5)/2]) {
                cylinder(r=threaded_bar/2,h=width*1.5, $fn=100);  
    }
}
    
    rotate([90,0,0]) color("Blue"){
        translate([-(length/2-threaded_bar),-(thickness*0.8),-(width*1.5)/2]) {
                cylinder(r=threaded_bar/2,h=width*1.5, $fn=100);  
    }
}
    translate([(length/2)-threaded_bar,0,0]) color("Green"){
    cube([width/2,width,thickness*2], center=true);
}
    translate([-((length/2)-threaded_bar),0,0]) color("Red"){
    cube([width/2,width,thickness*2], center=true);
}
}
}

module CentralLED() { // for normal LED
    difference() {
    cube([length,(width/2)-fit,thickness-fit], center=true);
            translate([0,0,-thickness*2]) 
               cylinder(r=LED/2,h=thickness*3, $fn=100);
        translate([length*0.2,0,-thickness*2]) 
               cylinder(r=LED/2,h=thickness*3, $fn=100);
    }
} 

module CentralADA() { //for Adafruit RGB square single LED
    difference() {
    cube([length,(width/2)-fit,thickness-fit], center=true);
               cube([ADA,ADA,ADA], center=true);
         translate([length*0.2,0,0]) 
              cube([ADA,ADA,ADA], center=true);
}
}

module central(){
    if(hole_style == 0) {
			translate([-100,0,0]) { CentralLED();} //normal LED
	} else if(hole_style == 1) {
			translate([100,0,0]) { CentralADA();} //Adafruit square LED
	}
        else if(hole_style == 2) {
			translate([100,0,0]) { CentralADA(); } translate([-100,0,0])  CentralLED();} // print both 
    }

holder(); 
central();


	
        
        
