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
	cout<< "ְԱ���: " << m_id
		<< "\t����: " << m_name
		<< "\t��λ: " << this->getdid()
		<< "\t��λְ��: ����ϰ彻��������,���·������Ա��" << endl;
}

string Manager::getdid()
{
	return "����";
}