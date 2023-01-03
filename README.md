# ChapstickRobot
A small, tracked robot with a claw for picking up and moving Chapstick around. Communicates over MQTT

# Purpose

This project was intended to be an introduction to MQTT and it's inner workings. The project then evolved into a fun little robot that could run
and grab me chapstick from accross my desk upon a command being sent to it. 

The *ChapstickRobot* then turned into just a passion project for fun & giggles.

I highly recommend taking a look at the [project collage](/ChapstickRobotProject.png) which shows everything in a lot more detail than the brief overview here (and it's got *PICTURES*)

# Directory Description

"ChapstickRobotFirmware" is the PlatformIO project directory which holds the `platformio.ini` file, for opening it in vscode with the PlatformIO extension.
[Here](https://platformio.org) is a link to PlatformIO if you are unfamiliar with this IDE. You can use the build tasks in PlatformIO to upload the firmware to a 
esp32 microcontroller board. 

Most esp32 boards will work with this projects current configuration without much fuss. [This was the board I used](https://www.amazon.com/dp/B0718T232Z?ref=nb_sb_ss_w_as-reorder-t1_ypp_rep_k1_1_8&amp=&crid=2ZCSUPRHXB4RT&amp=&sprefix=hiletgo+),
it's just a cheap ESP-32S dev board from amazon, and suited my needs well enough. If a board doesn't work, try looking if PlatformIO has it in the list of boards.

> If you want to run this firmware, make sure to change the broker IP and your network creds in `ChapstickRobotFirmware/include/Constants.h`

"ChapsterInterface" Contains a file `interface.py` and is used to connect to the mqtt broker, and uses the q,a,w,e,z,x and arrow keys to give commands to the robot.
This file requires two packages, [keyboard](https://pypi.org/project/keyboard/) and [paho-mqtt](https://pypi.org/project/paho-mqtt/). It's recommended to create a 
virtual environment, then use the "requirements.txt" file to install these packages.

> Make sure to change the IP of the broker in `interface.py` as well before use

"Parts" contains the STL files for the different parts on the robot, including the claw/elevator-arm, moveable "finger" and the two brackets for mounting the elevator
servo and electronics

"Docs" Contains everything you would need to know about this project, and also contains the source draw.io file for the project collage in the repository root.
"Docs" also contains a couple demo videos of the [robot working](/Docs/VideoDemos/RobotDemo.mp4), and it's [cad](/Docs/VideoDemos/RobotCad.mp4) respectively. 

# ChapsterInterface Controls

The following table lists the different commands that are sent with the `interface.py` file when run on keybaord presses

> Note that by default, the command sent is the SetSpeed 0 command, stopping movement.

| key | Command |
| --- | --- |
| "up" | Set speed forward 0.5 |
| "down" | Set speed backward 0.5 |
| "left" | Set turn counter clock-wise |
| "right" | Set turn clock wise |
| "q" | Elevator up |
| "a" | Elevator down |
| "w" | Claw close |
| "e" | Claw open |
| "z" | Retrieve Command |
| "x" | Place Command |

> Review [The Protocol Docs](/Docs/ProtocolDocs.xml) to see details about these commands, and all the command current implimented and available.
