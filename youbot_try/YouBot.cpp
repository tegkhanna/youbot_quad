#include "stdafx.h"
#include "YouBot.h"

using namespace youbot;
YouBot::YouBot()
{
}


YouBot::~YouBot()
{
}

void YouBot::botInit()
{

	try {
		myYouBotBase = new YouBotBase("youbot-base", YOUBOT_CONFIGURATIONS_DIR);
		myYouBotBase->doJointCommutation();

		youBotHasBase = true;
	}
	catch (std::exception& e) {
		LOG(warning) << e.what();
		youBotHasBase = false;
	}
	//AGET ARM
	try {
		myYouBotManipulator = new YouBotManipulator("youbot-manipulator", YOUBOT_CONFIGURATIONS_DIR);
		myYouBotManipulator->doJointCommutation();
		myYouBotManipulator->calibrateManipulator();

		youBotHasArm = true;
	}
	catch (std::exception& e) {
		LOG(warning) << e.what();
		youBotHasArm = false;
	}

	stopBase();
}


void YouBot::setVelocity(quantity<si::velocity> vx, quantity<si::velocity> vy, quantity<si::angular_velocity> va)
{
	_vx = vx;
	_vy = vy;
	_va = va;
	myYouBotBase->setBaseVelocity(_vx, _vy, _va);
}
void YouBot::stopBase()
{
	_vx = 0 * meter_per_second;
	_vy = 0 * meter_per_second;
	_va = 0 * radian_per_second;
	myYouBotBase->setBaseVelocity(_vx, _vy, _va);
}