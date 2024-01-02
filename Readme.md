# Go Chase It!

## Project Goal

The goal of this project is to develop a car robot equipped with a camera that can autonomously track and follow a white ball within its simulated environment.

## Project Structure

### Project Files Preview
![Project Structure](/src/images/project_structure.png)

The project consists of two main packages:

#### `my_robot`
- `design`: This package contains the robot's design Xacro file, which defines the robot's structure, including the chassis, two wheels attached with two hinges, and two fixed casters.
- `sensors`: These sensors are attached to the robot's chassis, including a camera and a Hokuyo LIDAR sensor.
- `launch`: Contains launch files that bring up the robot in the Gazebo simulation environment, incorporating the Xacro design and the Gazebo plugin `libgazebo_ros_diff_drive` for publishing odometry data, camera images, LIDAR data, and the controller for velocity and angular control in the x, y, and z directions. It also includes an RViz configuration to visualize sensor data.

#### `ball_chaser`
- This package contains two nodes:
  - `drive_bot`: Responsible for publishing the `DriveToTarget` service to the `/cmd_vel` topic, enabling the robot to move based on the provided velocity and angular properties.
  - `process_image`: Analyzes images captured by the camera, detects the white ball's position, subscribes to the topic published by the `drive_bot` node, and, through a service client callback function, updates the `DriveToTarget` service with new velocity and angular properties.

## Running the Project

To run the project, follow these steps:

1. Launch the robot simulation:
   ```bash
   roslaunch my_robot world.launch
2. Launch bll_chaser node (drive_bot,process_image) simulation:
   ```bash
   roslaunch ball_chaser ball_chaser.launch
### Output images:
![Project Structure](/src/images/full.png)
![terminal](/src/images/terminal.png)
![full](/src/images/project_structure.png)
