#pragma once
#include "Worker.h"
#include <iostream>
#include<string>

class Boss :public Worker
{
public:
	Boss(int id, string name, int did);

	void showinfo();

	string getdid();

};