#pragma once
#include "Manager.h"

Manager::Manager(int id, string name, int did)
{
	m_id = id;
	m_name = name;
	m_did = did;
}

void Manager::showinfo()
{
	cout<< "职员编号: " << m_id
		<< "\t姓名: " << m_name
		<< "\t岗位: " << this->getdid()
		<< "\t岗位职责: 完成老板交给的任务,并下发任务给员工" << endl;
}

string Manager::getdid()
{
	return "经理";
}