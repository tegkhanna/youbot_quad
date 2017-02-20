// youbot_try.cpp : Defines the entry point for the console application.
//

#include"stdafx.h"
#include<vector>
#include<iostream>
#include<fstream>
#include"YouBot.h"

#include <boost\chrono.hpp>
#include <boost\thread.hpp>
#include"Serial.h"
using namespace youbot;

boost::chrono::duration<double, boost::milli> elapsed;
int main()
{
	// configuration flags for different system configuration (e.g. base without arm)
	
	YouBot Bot;
	Bot.botInit();
	

	// define velocities
	double vLinear = 0.05; //meter_per_second
	double vRotate = 0.2; //radian_per_second
	double timeToReach = 0.00f, timeX = 0.00f, timeY = 0.00f;
	int obstacle = 0;
	int reached = 1;
	//locations
	std::vector<double> currLoc;
	std::vector<double> destLoc;
	currLoc.push_back(0.0000f);
	currLoc.push_back(0.0000f);
	destLoc.push_back(0.0000f);
	destLoc.push_back(0.0000f);
	
	
	try {

		if (Bot.baseAvailable()) {
			//boost quantities
			quantity<si::velocity> vx = 0 * meter_per_second;
			quantity<si::velocity> vy = 0 * meter_per_second;
			quantity<si::angular_velocity> va = 0 * radian_per_second;
			
			
			
			//move loop
			while (true)
			{
				//input from web server

				std::string command = "python server.py ";
				std::string str = "", sData = "";
				std::system(command.c_str());
				std::ifstream fin;
				fin.open("test.txt", std::ios::in);
				fin >> sData;
				std::cout << sData << std::endl;
				fin.close();

				destLoc[0] = std::stof(sData.substr(0, 3));
				destLoc[1] = std::stof(sData.substr(3, 3));
				
				//get location to go;

				//std::cin >> destLoc[0] >> destLoc[1]>>up;
				//calc(comment forward if active)
				timeX = abs(destLoc[0] - currLoc[0]) / vLinear;
				timeY = abs(destLoc[1] - currLoc[1]) / vLinear;


				if (destLoc[0] - currLoc[0] > 0)
					vx = vLinear * meter_per_second;
				else
					vx = -vLinear * meter_per_second;
				if (destLoc[1] - currLoc[1] > 0)
					vy = vLinear * meter_per_second;
				else
					vy = -vLinear * meter_per_second;


				
				

				//y

				Bot.setVelocity(0 * meter_per_second, vy, va);

				LOG(info) << "drive Y";

				SLEEP_MILLISEC(int(round(timeY)) * 1000);
				
				Bot.stopBase();//stop
				//x
				SLEEP_MILLISEC(500);
				Bot.setVelocity(vx, 0 * meter_per_second, va);
				LOG(info) << "drive X";
				SLEEP_MILLISEC(int(round(timeX)) * 1000);

	


				Bot.stopBase();//stop
				LOG(info) << "stop base";

				
				currLoc[0] = destLoc[0];
				currLoc[1] = destLoc[1];


			}

			if (Bot.armAvailable()) {
				// Target position for one arm joint
				//JointAngleSetpoint desiredJointAngle;

				//desiredJointAngle.angle = 2.56244 * radian;
				//myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);
				// unfold arm 
				// all of the following constants are empirically determined to move the arm into the desired position 
				//desiredJointAngle.angle = 2.56244 * radian;
				//myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);
			}
		}

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "unhandled exception" << std::endl;
	}
	std::system("PAUSE");
	return 0;
}