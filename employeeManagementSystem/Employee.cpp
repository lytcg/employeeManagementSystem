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
	cout << "ְԱ���: " << m_id
		<< "\t����: " << m_name
		<< "\t��λ: " << this->getdid()
		<< "\t��λְ��: ��ɾ�����������" << endl;
}

string Employee::getdid()
{
	return "Ա��";
}
