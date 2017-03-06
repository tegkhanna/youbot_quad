#pragma once
#include "youbot_driver/youbot/YouBotBase.hpp"
#include<youbot_driver\youbot\YouBotManipulator.hpp>

using namespace youbot;
class YouBot
{

	quantity<si::velocity> _vx;
	quantity<si::velocity> _vy;
	quantity<si::angular_velocity> _va;
	float _ang[5];
	YouBotBase* myYouBotBase = 0;
	YouBotManipulator* myYouBotManipulator = 0;
	JointAngleSetpoint desiredJointAngle;
	bool youBotHasBase = false;
	bool youBotHasArm = false;
public:



	YouBot();
	void botInit();
	void setVelocity(quantity<si::velocity> vx, quantity<si::velocity> vy, quantity<si::angular_velocity> va);
	void setArmAngle(int arm, float angle);
	void stopBase();
	bool baseAvailable() { return youBotHasBase; }
	bool armAvailable() { return youBotHasArm; }
	~YouBot();
};

