#pragma once
#include "Employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_did = did;
}

void Employee::showinfo()
{
	cout << "职员编号: " << m_id
		<< "\t姓名: " << m_name
		<< "\t岗位: " << this->getdid()
		<< "\t岗位职责: 完成经理交给的任务" << endl;
}

string Employee::getdid()
{
	return "员工";
}
