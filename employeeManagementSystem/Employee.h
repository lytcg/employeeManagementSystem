#pragma once
#include <iostream>
#include<string>
#include"Worker.h"
using namespace std;

class Employee : public Worker
{
public:
	void showinfo();

	string getdid();

	Employee(int id, string name, int did);
};