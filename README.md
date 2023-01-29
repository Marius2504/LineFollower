# :robot: LineFollower :car:

## :arrow_forward: Introduction
Line follower project for Introduction to Robotics course, taken in 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. The project consists in a concept car that follows a line by itself.

- Team name: <b>RO0314</b>

- Team members:
  * [<b>Ion Luca-Mihail</b>](https://github.com/lucaion)
  * [<b>Dumitrescu Marius-Cristian</b>](https://github.com/Marius2504)

## :memo: Description
The idea behind the project was to develop a concept car that moves by itself on a course. The concept scans the ground and determines the right moment to accelerate or decelerate one of the motors to move left or right along the line. When you press the start button, the concept calibrates itself by repeatedly moving left and right.

## :computer: Implementation
The hard part in this project was for the concept car to cover the route in less than 20 seconds to receive the maximum grade. Maybe not the smartest approach, but we assigned different values to p and d until we agreed that the concept was good enough to test it on the final track. Unfortunately, our concept came up with a time of 21.066 seconds, which was very close to the proposed time.

## :exclamation: Instructions
To use the concept car, you need to restart the Arduino board and place the concept over the black line, noting that the line should be just below the centre of the sensor. After a few seconds, the concept car will start moving along the line. To stop the process, simply disconnect the battery.

## :wrench: Components 
  - Arduino Uno
  - Zip-ties
  - Power source, a LiPo battery
  - Wheels (2)
  - Wires for the line sensor (female - male)
  - QTR-8A reflectance sensor, along with screws
  - Ball caster
  - Extra wires from the Arduino kit
  - Chassis
  - Breadboard - medium (400pts)
  - L293D motor driver
  - DC motors (2)
  
 ## :camera: Setup picture
<p align="center">
 <img src="https://github.com/lucaion/LineFollower/blob/main/ProiectLineFollower/Setup.jpg" width="600">
</p>

## [:movie_camera: Test lap demo](https://www.youtube.com/watch?v=07XBJRnSiZM)
## [:movie_camera: Final lap demo](https://www.youtube.com/watch?v=SWbQZZ5HxOQ)
