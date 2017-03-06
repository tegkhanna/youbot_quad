#pragma once
class inputManage
{

	char currKey = 0;
	char prevKey = 0;
	int getKey();
public:
	bool isKeyDoen(int key);
	inputManage();
	~inputManage();
};

