# Introduction

This project is carried out within the Baccalauréat (French high school final exam, this is why all the comments and functions are in French... :/), and led by a team of four students. It permits to air instructors to introduce the basics of flight mechanics to their students.

# Why ?

I personally love aeronautics, and my friends were enthusiastic about the idea of helping beginners to understand how the flight commands influence the behaviour of a plane.

# What is the goal of this project ?

As I said in the Introduction, this project is carried out within the high school final exam. It represents a quarter of our Engineering grade.
Our high school gives the chance to students to learn the basics of aeronautics in special courses, given by an air instructor. Our project aims to help him to explain how a plane is controlled, and how it moves depending on the angle of the control surfaces.

# Concretely...

The project consists of two mains parts : the Plane and the Flight Commands.
The plane we use isn't a real plane (joke). It is an out of order RC Plane (photos coming soon). All its control surfaces are attached to servomotors which are commanded by an Arduino card (but powered by an external power source, as the Arduino can't provide as much current as the motors require). It is also customized with LEDs for a better visibility
The flight commands contain a joystick (for pitch and roll), a potentiometer (for yaw, didn't find a smarter way) and two pushbuttons (for flaps). It also contains the Arduino which is connected to all these devices.
The two parts are linked by a ball joint which allows the plane to rotate in two axis (the third is blocked by what we call in France a "finger").

When the user moves the joystick or the potentiometer, it moves in the same time the plane. Control surfaces are moved proportionnaly to the joystick tilt, and the entire plane moves. The rotation speed of the plane is set depending the joystick tilt : the more the joystick is moved, the more the plane will rotate fast.
When control surfaces are not at their normal angle, LEDs attached to them turn on, to see them further.

Precise illustrations of the behaviour are to come.
