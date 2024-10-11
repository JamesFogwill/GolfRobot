# GolfRobot for University of Plymouth final project

Golf Robot Project

This project showcases the development of a golf robot capable of autonomously tracking and retrieving a golf ball on a green. The robot utilises OpenCV computer vision techniques to detect and track the golf ball using a PlayStation 2 Eye camera.

Key Components and Functionality:

Computer Vision: OpenCV is employed to process the camera feed, identify the golf ball, and calculate its precise coordinates.
Hardware Interface: Serial communication or USB is used to transmit the calculated coordinates to an STM ARM board.
Robotics Control: The STM ARM board, running C++ mbed code, receives the coordinates and controls a stepper motor to accurately position a collection mechanism.
Autonomous Operation: The robot can independently track and retrieve the golf ball, eliminating the need for manual intervention.
Project Goals and Achievements:

Develop a functional golf robot capable of accurate ball tracking and retrieval.
Demonstrate the application of computer vision and robotics principles in a real-world scenario.
Explore the potential of autonomous systems in sports and leisure activities.
Project Structure:

Computer Vision Code: Contains the OpenCV-based algorithms for ball detection, tracking, and coordinate calculation.
Hardware Interface Code: Handles communication between the computer and the STM ARM board.
Robotics Control Code: Implements the logic for controlling the stepper motor based on the received coordinates.
Documentation: Provides detailed explanations of the project's components, functionality, and implementation.
