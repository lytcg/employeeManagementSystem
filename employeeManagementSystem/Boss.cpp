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
	cout << "ְԱ���: " << m_id
		<< "\t����: " << m_name
		<< "\t��λ: " << this->getdid()
		<< "\t��λְ��: ����˾��������" << endl;
}

string Boss::getdid()
{
	return "�ϰ�";
}