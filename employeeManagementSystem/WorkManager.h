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

	int getnum();//返回现有数据中的人数

	void init_emp();//初始化员工数组

	void showemp();

	int isexist(int id);

	void del_emp();

	void mod_emp();//根据id修改

	void find_emp();

	void sort_emp();

	void clean_file();

	bool fileisemply;//记录文件是否为空

	int m_num;//记录人数

	Worker** m_emparr;//员工数组的指针
};
