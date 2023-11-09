# Go Chase It !

## project goal:

    - drive a car robot contains camera to follow the white ball in
    the its world.

## project structure:

    - structure_files preview:
        ![project_structure_files](/src/project_structure.png)
    pacages:
        - my_robot:
            - design: that package contains the robot design xacro file which contains robot consist of chassis and two wheels attached with two hinges and fixed other two casters.
            - sensors: attached to chassis, two sensors: camera and
            hokuyo LIDAR sensor.
            - launch file that contains the xacro design and gazebo plugin (libgazebo_ros_diff_drive) to publish the odometry
            ,camera,laser beam of LIDAR and controller /cmd_vel which
            control tha movement using velocity and angle in x,y,z .
            contain rviz also to show sensor results visually.
        - ball_chaser:
            - contains two nodes:
                - drive_bot: that responsible for publish the DriveToTarget service to the "/cmd_vel" topic to move the robot.
                - process_image: that resposible for analyze the image taken by the camera and detect the white ball and its position, then subscribe to the topic published by drive_bot node, then by the service client callback function made the procecss and finally update the DriveToTarget service with the new velocity and angular properties.

## run the project:

    - running my_robot:
            roslaunch my_robot world.launch
    - running ball_chaser:
            roslaunch ball_chaser ball_chaser.launch
    - move the ball in gazebo simulation, the robot will move to its direction by itself and if not found, it will spin till find it   to drive to it again.
