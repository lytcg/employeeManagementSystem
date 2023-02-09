#include"Boss.h"
using namespace std;

Boss::Boss(int id, string name, int did)
{
	m_id = id;
	m_name = name;
	m_did = did;
}

void Boss::showinfo()
{
	cout << "职员编号: " << m_id
		<< "\t姓名: " << m_name
		<< "\t岗位: " << this->getdid()
		<< "\t岗位职责: 管理公司所有事务" << endl;
}

string Boss::getdid()
{
	return "老板";
}