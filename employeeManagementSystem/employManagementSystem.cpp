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
		case 0://�˳�ϵͳ 
			wm.exitsystem();
			break;
		case 1://���Ա��
			wm.add_emp();
			break;
		case 2://��ʾԱ��
			wm.showemp();
			break;
		case 3://ɾ��Ա��
			wm.del_emp();
			break;
		case 4://�޸�Ա��
			wm.mod_emp();
			break;
		case 5://����Ա��
			wm.find_emp();
			break;
		case 6://����Ա��
			wm.sort_emp();
			break;
		case 7://����ļ�
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