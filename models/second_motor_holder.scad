include <metrics.scad>


module second_motor_holder(){

    difference(){
        //the main mount of the motor
        cube([motor_d + motor_mount_w + motor_hole_w * 2,
            motor_h + mount_wall_thickness,
            motor_d + motor_mount_w + laser_pointer_holder_l]);

        translate([0, -mount_wall_thickness, (motor_d + motor_mount_w + laser_pointer_holder_l) / 2]){
            motor_hole();
        }
        
        //hole for the knob of the motor on the base plate
        translate([(motor_d + motor_mount_w + motor_hole_w * 2) / 2 - motor_ending_h/2,
                (laser_pointer_holder_l) / 2 - motor_ending_w/2,
                -preview_margin]){
            cube([motor_ending_h, motor_ending_w, motor_ending_l]);
        }
    }
}

module motor_hole(){
    //motor (round section)
    translate([(motor_d + motor_mount_w + motor_hole_w*2) / 2,
            0,
            0]){
        rotate([90, 0, 180]){
            cylinder(h=motor_h, d1=motor_d, d2=motor_d);
        }
    }
    //motor (square section)
    translate([(motor_d + motor_mount_w + motor_hole_w*2) / 2 - motor_square_w/2,
           0,
            //middle of circle - diameter of circle / 2 - halfe of the square part / 2
            - motor_d / 2 - motor_square_h/2]){
            cube([motor_square_w, motor_h, motor_square_h]);
    }

    //holes for screws
    space_next_to_hole = (motor_d + motor_mount_w + motor_hole_w * 2 - motor_d) / 2;
    //left
    translate([-motor_hole_w/2 + space_next_to_hole,
            0,
            0]){
        rotate([90, 0, 180]){
            cylinder(h=laser_pointer_holder_l + motor_hole_w + preview_margin*2,
                    d1=motor_mount_w, d2=motor_mount_w,
                    $fn=_fn);
        }
    }
    //right
    translate([motor_hole_w/2 + space_next_to_hole + motor_d,
            0,
            0]){
        rotate([90, 0, 180]){
            cylinder(h=laser_pointer_holder_l + motor_hole_w + preview_margin*2,
                    d1=motor_mount_w, d2=motor_mount_w,
                    $fn=_fn);
        }
    }

}

//test
second_motor_holder();


//animation
$vpt = [(motor_d + motor_mount_w + motor_hole_w * 2) / 2,
            laser_pointer_holder_l / 2,
            (motor_d + motor_mount_w + laser_pointer_holder_l) / 2];

$vpr = [60, 0, 360 * $t];

$vpd = 400;