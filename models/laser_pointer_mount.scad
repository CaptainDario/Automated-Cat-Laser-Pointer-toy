include <metrics.scad>



module laser_pointer_holder(){
    union(){

        //motor mount
        difference(){
            //holder
            translate([-(motor_mount_thickness + laser_pointer_d/2),
                        -laser_pointer_d/4,
                        0]){
                cube([motor_mount_thickness, laser_pointer_d/2, laser_pointer_holder_l]);
            }

            //hole
            translate([- laser_pointer_d/2 - motor_mount_thickness - preview_margin,
                        -motor_ending_w/2,
                        laser_pointer_holder_l/2 + motor_ending_h/2]) {

                rotate([0, 90, 0]){
                    cube([motor_ending_h, motor_ending_w, motor_ending_l]);
                }
            }
        }

        //laser pointer hole
        difference(){
            //shell
            cylinder(h=laser_pointer_holder_l,
                    d1=laser_pointer_d + mount_wall_thickness*2, d2=laser_pointer_d + mount_wall_thickness*2, $fn=_fn);

            //remove space for the pointer
            translate([0, 0, -preview_margin]) {
                cylinder(h=laser_pointer_holder_l + preview_margin*2, d1=laser_pointer_d, d2=laser_pointer_d, $fn=_fn);
            };

            //space for the screw to fasten
            translate([0, -mount_wall_thickness/2, -preview_margin]){
                cube([laser_pointer_d/2 + mount_wall_thickness, mount_wall_thickness, laser_pointer_holder_l + 2*preview_margin]);
            }
        }

        //fastener
        difference(){
            union(){
                //left side of the screw terminal
                translate([laser_pointer_d/2, -mount_wall_thickness * 3/2 - preview_margin, 0]){
                    cube([screw_terminal_length, mount_wall_thickness, laser_pointer_holder_l]);
                }

                //right side of the screw terminal
                translate([laser_pointer_d/2, mount_wall_thickness/2 + preview_margin, 0]){
                    cube([screw_terminal_length, mount_wall_thickness, laser_pointer_holder_l]);
                }
            }

            //cut out a screw
            translate([laser_pointer_d/2 + screw_terminal_length/2, laser_pointer_d/2, laser_pointer_holder_l/2]) {
                rotate([90, 0, 0]){
                    cylinder(h=laser_pointer_d, d1=screw_d, d2=screw_d, $fn=_fn);
                }
            }
        }
    }
}

//main
laser_pointer_holder();
//animation
$vpt = [0, 0, laser_pointer_holder_l/2];

$vpr = [60, 0, 360 * $t];

$vpd = 200;