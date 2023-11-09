#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "ball_chaser/DriveToTarget.h"

ros::ServiceClient client;
ros::Subscriber sub1;

void drive_bot(float velocity_linear_x, float angle_z)

{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = velocity_linear_x;
    srv.request.angular_z = angle_z;

    if (!client.call(srv))
        ROS_ERROR(" service failed to call ");
}

enum location
{
    RIGHT,
    LEFT,
    MID
};

location locatePixel(const int pixelIndex, const int imageSize)
{
    location pixelLocation;
    int lefBoundry = imageSize / 3 - 1,
        midBoundry = (imageSize * 2) / 3 - 1;

    if (pixelIndex < lefBoundry)
        pixelLocation = LEFT;
    else if (pixelIndex < midBoundry)
        pixelLocation = MID;
    else
        pixelLocation = RIGHT;

    return pixelLocation;
}

void driveTo(const location pixelLocation)
{
    float velocity = 0.3, angle = 0;

    switch (pixelLocation)
    {
    case RIGHT:
        angle = 0.3;
        break;
    case LEFT:
        angle = -0.3;
        break;
    default:
        break;
    }

    drive_bot(velocity, angle);
}

void stopRobot()
{
    float velocity = 0, angle = 0;
    return drive_bot(velocity, angle);
}

void process_image_callback(const sensor_msgs::Image img)
{
    int FULLPIXELUNIT = 255;

    for (int redUnit = 0; redUnit < img.data.size(); redUnit++)
    {
        bool isWhitePixel = true;
        if (img.data[redUnit] == FULLPIXELUNIT)
        {
            for (int j = 1; j < 3; j++, redUnit += j)
                if (img.data[redUnit] != FULLPIXELUNIT)
                    isWhitePixel = false;

            if (isWhitePixel)
            {
                int pixelIndex = redUnit / 3;
                int pixelIndexInRow = pixelIndex % img.width;
                location pixelLocation = locatePixel(pixelIndexInRow, img.width);
                return driveTo(pixelLocation);
            }
        }
    }

    stopRobot();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "process_image");
    ros::NodeHandle nh;
    client = nh.serviceClient<ball_chaser::DriveToTarget>("ball_chaser/command_robot");
    sub1 = nh.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
    ros::spin();
    return 0;
}
