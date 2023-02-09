#pragma once
#include <iostream>
#include"Boss.h"
#include"Employee.h"
#include"Manager.h"
#include"Worker.h"
#include<fstream>
#define FILENAME "empFile.txt"


class WorkManager
{
public:
	WorkManager();

	~WorkManager();

	void show_menu();

	void exitsystem();

	void add_emp();

	void save();

	int getnum();//�������������е�����

	void init_emp();//��ʼ��Ա������

	void showemp();

	int isexist(int id);

	void del_emp();

	void mod_emp();//����id�޸�

	void find_emp();

	void sort_emp();

	void clean_file();

	bool fileisemply;//��¼�ļ��Ƿ�Ϊ��

	int m_num;//��¼����

	Worker** m_emparr;//Ա�������ָ��
};
