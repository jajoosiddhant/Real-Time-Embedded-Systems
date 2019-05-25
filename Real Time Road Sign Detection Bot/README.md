# Real Time Road Sign Detection. [(DEMO VIDEO)](https://www.youtube.com/watch?v=5pxvPxIWPSY&feature=youtu.be)
## Author: Siddhant Jajoo, Satya Mehta and Ayush Dhoot.
<p align="middle">
<img src="Images/Bot%20Image.PNG">
</p>

This project was completed in the course Real Time Embedded Systems at University of Colorado, Boulder under the guidance of Professor Timothy Scherr in May 2019.

## Hardware Components:
- Raspberry Pi 3B+
- Raspberry Pi Camera V2.1
- DC Motor and Motor Driver
- Ultrasonic Sensor HCSR04

## Software Components:
- Linux
- Multithreading
- Thread Safety
- OpenCv
- Rate Monotonic Scheduling Policy
- Scheduler thread
- Mutexes/Semaphores

## Features:
- The Bot detects road sign and takes subsequent appropriate steps. This Bot detects only a single **YIELD** sign due to processor constraints.
- The bot stops on detecting a **YIELD** sign.
- The bot also stops in case of any interference in its path using an Ultrasonic sensor and resumes its operation on removal of an obstacle.
- Implements priorities based on Rate Monotonic Scheduling Policy.
- Implemented a Scheduler.

## Block Diagram:
<p align="middle">
<img src="Images/Block Diagram.PNG">
</p>

## Overview:
The Project is aimed at designing a bot that captures certain symbols and subsequently carries out certain actions based on the symbols. The project design includes motors, ultrasonic sensor and Pi-Camera Module V2. The board used for processing is the Raspberry Pi. 

The Camera would search for this sign in its frame:
<p align="middle">
<img src="Images/YIELD.png">
</p>

When the Camera detects the **YIELD** sign, the motors stop. In case of an obstacle in the path of the bot, the care is taken that it does not crash onto the object. For this purpose, an ultrasonic sensor is attached onto the bot which would constantly detect for any obstacles in its path. If an obstacle is detected, it will immediately stop and resume its operation if the object is removed from its path.
The Scheduling policy that would be used for this project on Linux is SCHED_FIFO. The priorities are assigned on the frequency of operation of different tasks, thus following the Rate Monotonic Policy. In order to determine which task runs at a particular point of time, a scheduler is designed which posts the semaphores for the respective tasks. All the tasks are blocked on their respective semaphores which would be released by the scheduler.


The **Demo Video** of the Project can be found [HERE](https://www.youtube.com/watch?v=5pxvPxIWPSY&feature=youtu.be).

The Project Code and Makefile can be viewed [HERE](https://github.com/jajoosiddhant/Real-Time-Embedded-Systems-RTES/tree/master/Real%20Time%20Road%20Sign%20Detection%20Bot/Project%20Code).

The Code Zip file for the Project can be found [HERE](https://github.com/jajoosiddhant/Real-Time-Embedded-Systems-RTES/tree/master/Real%20Time%20Road%20Sign%20Detection%20Bot/Code%20Zip%20File).

The Entire Project Report can be found [HERE](https://github.com/jajoosiddhant/Real-Time-Embedded-Systems-RTES/tree/master/Real%20Time%20Road%20Sign%20Detection%20Bot/Report).

