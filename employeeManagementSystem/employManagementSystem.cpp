#pragma once
#include <iostream>
#include"WorkManager.h"
#include"Employee.h"
#include"Manager.h"
using namespace std;

int main()
{
	int choice;
	while (1)
	{
		WorkManager wm;
		wm.show_menu();
		cin >> choice;

		switch (choice)
		{
		case 0://退出系统 
			wm.exitsystem();
			break;
		case 1://添加员工
			wm.add_emp();
			break;
		case 2://显示员工
			wm.showemp();
			break;
		case 3://删除员工
			wm.del_emp();
			break;
		case 4://修改员工
			wm.mod_emp();
			break;
		case 5://查找员工
			wm.find_emp();
			break;
		case 6://排序员工
			wm.sort_emp();
			break;
		case 7://清空文件
			wm.clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("cls");
	system("pause");
}