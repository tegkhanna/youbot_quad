#include "stdafx.h"
#include "inputManage.h"


inputManage::inputManage()
{
}


inputManage::~inputManage()
{
}

#include <windows.h>

#include <iostream>

using namespace std;


const short unsigned int Keyleft = 37;
const short unsigned int Keytop = 38;
const short unsigned int Keyright = 39;
const short unsigned int Keydown = 40;
const short unsigned int Keyexit = 81;


int inputManage::getKey()
{
	while (true)
	{
		for (int i = 8; i <= 256; i++)
		{
			if (GetAsyncKeyState(i) & 0x7FFF)
			{

				// This if filters the keys, i want to allow direction arrows
				// and q for quit. If you want to add more just add the code for the key,
				// to know the key code just coment the if line and print the keycode.
				if ((i >= 37 && i <= 40) || i == 81)
					return i;
			}
		}
	}
}


bool inputManage::isKeyDoen(int key)
{
	currKey = getKey();
	if (prevKey == currKey)
	{
		return true;
	}
	else
	{
		prevKey = currKey;
		return false;
	}
}