#pragma once
#include <iostream>
#include<string>
using namespace std;

class Worker
{
public:
	virtual void showinfo() = 0;
	virtual string getdid() = 0;

	int m_id;
	string m_name;
	int m_did;
};