Automated cat-Laser-Pointer toy

I made this for the 2020 ["Pets Speed Challenge"]((https://www.instructables.com/id/An-Automated-Cat-laser-pointer-toy/) ) on instructables (The instructable has more images for the setup of the hardware).
See it in action by clicking on the image below. <br>
[![See it in action](https://img.youtube.com/vi/vp5igMt3IM0/0.jpg)](https://www.youtube.com/watch?v=vp5igMt3IM0)

Download the current release from [here](https://github.com/CaptainDario/Automated-Cat-Laser-Pointer-toy/releases).

## Instructions

## Software
Currently you have to build the firmware from source. This is necessary because you have to enter you wifi credentials.
Get the latest release from [here](https://github.com/CaptainDario/Automated-Cat-Laser-Pointer-toy/releases/tag/v1.0). Compile it and falsh it to your D1 mini.
*note:*
*I hope to provide a ready made image in the future where you can enter the credentials per webserver.*

But for now you have to do the following:You need to rename the file “REMOVE_credentials.h” in the “src” folder to “credentials.h”. And replace “YOUR SSID” and “YOUR PWD” in this file with your wifi SSID and password.
After completing this first step you have to upload the file system to the esp and than compile and upload the software.

## Hardware
You need following hardware for this project:

* [3.3V laser pointer](https://www.aliexpress.com/item/32676284654.html?spm=a2g0s.9042311.0.0.27424c4dB5clXD)
* [ESP D1 mini](https://www.aliexpress.com/item/33036965281.html?spm=a2g0o.productlist.0.0.4ccc4b07HOS6x9&algo_pvid=bc3ef8fe-2a08-46af-b766-844a65c69a65&algo_expid=bc3ef8fe-2a08-46af-b766-844a65c69a65-8&btsid=0b0a0ad815928792906667495eca52&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
* Some jumper wires
* [barrel jack for power](https://www.aliexpress.com/item/32883658107.html?spm=a2g0s.9042311.0.0.27424c4dngOKlg)
* 2x [ULN2003 stepper motors with driver board](https://www.aliexpress.com/item/32962476866.html?spm=a2g0o.productlist.0.0.6ad63f4eT367Qu&algo_pvid=4c8276b2-4e30-4886-951e-bd294634acb4&algo_expid=4c8276b2-4e30-4886-951e-bd294634acb4-12&btsid=0b0a187b15928792542952779e343a&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
* [5V 2A PSU](https://www.aliexpress.com/item/4000102102421.html?spm=a2g0o.productlist.0.0.c70945e3c7KZNP&s=p&ad_pvid=202006222023487857474908802500001954491_4&algo_pvid=c8b813d4-ded6-4fb1-b736-55e24e119589&algo_expid=c8b813d4-ded6-4fb1-b736-55e24e119589-3&btsid=0b0a050115928826284412892e2f08&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
* 1x M4×10 screw and nut
* 2x M4×20 screw, nut and washer
* 3D printer
(All those components are just examples)

First you need to print the mounts for the motors. To do this print
[these files](https://github.com/CaptainDario/Automated-Cat-Laser-Pointer-toy/tree/master/models).
*I will be doing a model for the base case in the future too. But for now follow the instructions below...*

A little bit harder will be the making of the base case. I made the case out of wood to provide more structural rigidity (and I think it looks nicer too). The base case has one large hole on the top and a small one on the side. The large hole is for the stepper motor and the small one for the power input. Make sure that the motor-hole is large enough to fit the cables of two stepper motors and also the two wires of the laser pointer (they need space to move freely as the wires will move due to the rotation).

Now connect the components as shown in this image:

![circuit.png](https://github.com/CaptainDario/Automated-Cat-Laser-Pointer-toy/blob/master/instructions/wiring/circuit.png)

Now it is time to assemble it. First put the laser pointer in the mount and use the M4x10 screw and nut to fix it in place.
Next up is the power jack. Put it in the small hole and fasten it with its nut.
The first motor has to be put in the 3D printed mount and secured with the two M4×20 screws, nuts and washers.
In the second last step the other motor has to be placed in the large hole of the wood case while routing all the cables through the hole too.
Finally put the motors in their holes and also stick them together. If they do not fit tightly put some hot glue on them to secure everything in place.


#### Caution
* Double check that the cables have enough space to move while the motors are rotating. 
* NEVER rotate the motors by hand! You can and most probably will damage them.
* Motors tend to overheat during extend usage. Since this is a cat toy, stop it if it is not in use to prevent it from overheating.




## Project Ideas and next steps
You can take a look at the planned tasks [here](https://github.com/CaptainDario/Automated-Cat-Laser-Pointer-toy/projects/1).
If you have ideas for new features or improvments feel free to open a request.


##Developer notes
This project uses [Circuit Daiagram](https://www.circuit-diagram.org/) for wiring images.
