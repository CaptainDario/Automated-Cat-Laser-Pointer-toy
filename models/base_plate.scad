include <metrics.scad>

use <second_motor_holder.scad>

component_cut_out_depth = 1.5;
wall_thickness = 6.5;

driver_board_w = 33;
driver_board_l = 35;

gap_between_components = 5;

base_plate_w = driver_board_w * 2 + gap_between_components * 4 + motor_d;
base_plate_base_h = component_cut_out_depth + 1;
base_plate_h = component_cut_out_depth + motor_h;


//d1 mini dimensions
esp_w = 36;
esp_l = 26;

usb_c_jack_w = 9;
usb_c_jack_h = 4.5;

//the amount of magnets per side
amount_of_magnets = 3;
magnet_d = 5.5;
magnet_h = 2.5;



difference(){
    //base case(body)
    cube([base_plate_w + 2*wall_thickness, base_plate_w + 2*wall_thickness, component_cut_out_depth + 1 + motor_h]);
    //remove inside
    translate([wall_thickness, wall_thickness, component_cut_out_depth + 1]) {
        cube([base_plate_w, base_plate_w, base_plate_h]);
    }

    translate([0, 0, base_plate_base_h - component_cut_out_depth + preview_margin]){
        //space for USB jack
        translate([base_plate_w/2, -preview_margin, component_cut_out_depth]){
            cube([usb_c_jack_w, wall_thickness + 2*preview_margin, usb_c_jack_h]);
        }
        //holes for the motor-drivers
        //left
        translate([wall_thickness,
                    base_plate_w/2 + wall_thickness - driver_board_l/2,
                    0]){
            cube([driver_board_w, driver_board_l, component_cut_out_depth]);
        }
        //right
        translate([wall_thickness + base_plate_w -driver_board_w,
                    base_plate_w/2 + wall_thickness - driver_board_l/2,
                    0]){
            cube([driver_board_w, driver_board_l, component_cut_out_depth]);
        } 
        //hole for the esp
        translate([wall_thickness + base_plate_w/2 - esp_w/2,
                    wall_thickness + base_plate_w - esp_l,
                    0]){
            cube([esp_w, esp_l, component_cut_out_depth]);
        }
        //motor hole
        translate([wall_thickness + base_plate_w/2 - motor_d,
                wall_thickness + base_plate_w/2,
                0]) {
            rotate([90, 0, 0]){
                motor_hole();
            }
        }
    }

    //top magnets
    translate([0, 0, component_cut_out_depth + 1 + motor_h - magnet_h + preview_margin]) {
        magnets();
    }

    //bottom magnets
    translate([0, 0, -preview_margin]) {
        magnets();
    }
}


module magnets(){
    //magnet holes
    magnet_spacing = ((base_plate_w + 2*wall_thickness - magnet_d) / amount_of_magnets) - (wall_thickness/2 - magnet_d/2)/(amount_of_magnets-1);
    for (x = [0:amount_of_magnets]) {
        for (y = [0:amount_of_magnets]){
            if (y == 0 || y == amount_of_magnets || x == 0 || x ==amount_of_magnets) {
                translate([(wall_thickness/2 - magnet_d/2 + magnet_d/2) + x * magnet_spacing,
                        (wall_thickness/2 - magnet_d/2 + magnet_d/2) + y * magnet_spacing,
                        0]){
                    cylinder(h=magnet_h, d1=magnet_d, d2=magnet_d);
                }
            }
        }
    }
}