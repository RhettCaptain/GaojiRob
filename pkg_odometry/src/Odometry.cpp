#include "Odometry.h"

void Odometry::Odometry(double x,double y,double th){
	odometerSub = nHandle.subscribe("topic_odometer_sensor",10,&Odometry::onRecOdometerMsg,this);
	odometryPub = nHandle.advertise<nav_msgs::Odometry>("odom",10);
	odometryPose.position.x = x;
	odometryPose.position.y = y;
	odometryPose.position.z = 0;
	odometryPose.orientation = tf::createQuaternionFromYaw(th);
}

void Odometry::Odometry(const geometry_msgs::Pose& initPose){
	odometerSub = nHandle.subscriber("topic_odometer_sensor",10,&Odometry::onRecOdometerMsg,this);
	odometryPub = nHandle.advertise<nav_msgs::Odometry>("odom",10);
	odometryPose = initPose;
}

void Odometry::onRecOdometerMsg(const nav_msgs::Odometry::ConstPtr& msg){
	double deltaDis = msg->pose.pose.position.x;
	double deltaAng = msg->pose.pose.orientation.z;
	odometryPose.position.x += deltaDis * cos(deltaAng / 2 + odometryPose.orientation.z);
	odometryPose.position.y += deltaDis * sin(deltaAng / 2 + odometryPose.orientation.z);
	odometryPose.orientation.z += deltaAng;
}
