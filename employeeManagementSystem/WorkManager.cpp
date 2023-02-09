#include"workManager.h"

using namespace std;
WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;//测试输出

		this->m_emparr = NULL;//初始化数组指针
		this->m_num = 0;//初始化人数
		this->fileisemply = true;

		ifs.close();
		return;
	}
	
	//文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())//判断是否在尾位
	{
		//cout << "文件为空" << endl;//测试输出
		this->m_emparr = NULL;//初始化数组指针
		this->m_num = 0;//初始化人数
		this->fileisemply = true;

		ifs.close();
		return;
	}

	//文件存在且有记录
	int num = this->getnum();
	//cout << "职工个数为: " << num << endl;//测试代码
	this->m_num = num;//更新成员属性

	this->m_emparr = new Worker * [this->m_num];//根据职工数创建数组

	this->init_emp();//初始化数组

	ifs. close();
}

WorkManager::~WorkManager()
{

}

void WorkManager::show_menu()
{
	
		cout << "********************************************" << endl;
		cout << "*********  欢迎使用职工管理系统！ **********" << endl;
		cout << "*************  0.退出管理程序  *************" << endl;
		cout << "*************  1.增加职工信息  *************" << endl;
		cout << "*************  2.显示职工信息  *************" << endl;
		cout << "*************  3.删除离职职工  *************" << endl;
		cout << "*************  4.修改职工信息  *************" << endl;
		cout << "*************  5.查找职工信息  *************" << endl;
		cout << "*************  6.按照编号排序  *************" << endl;
		cout << "*************  7.清空所有文档  *************" << endl;
		cout << "********************************************" << endl;
		cout << endl;
	
}

void WorkManager::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkManager::add_emp()
{
	cout << "请输入添加的职工数量" << endl;
	int addnum;
	cin >> addnum;

	if (addnum > 0)
	{
		int newsize = this->m_num + addnum;//计算新空间大小

		Worker** newspace = new Worker * [newsize*sizeof(Worker)];//开辟新空间//-------------将[newsize]改为[newsize*sizeof(Worker)],解决缓冲区溢出警告

		if (this->m_emparr != NULL)//将原空间下内容放到新空间下
		{
			for (int i = 0; i < this->m_num; i++)
			{
				newspace[i] = this->m_emparr[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addnum; i++)
		{
			int id;
			string name;
			int did;

			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;
			cout << "请选择职工岗位: " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> did;

			Worker* worker = NULL;
			switch (did)
			{
			case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id,name,2);
				break;
			case 3:
				worker = new Boss(id,name,3);
				break;
			default:
				break;
			}

			newspace[this->m_num + i] = worker;//将新数据储存到数组中----------------------缓冲区溢出警告

			//delete worker;//----------------可能存在问题
			//worker = NULL;
		}

		delete[] this->m_emparr;//释放原有空间

		this->m_emparr = newspace;//更改新的空间指向------------将newspace的数组数据给emparr,并在第一次记录中将emparr转为数组

		this->m_num = newsize;//更新人数

		this->save();//保存到txt

		this->fileisemply = false;//更新员工不为空

		cout << "成功添加" << addnum << "名员工,现有员工" << this->m_num << "名" << endl;
	}
	else
	{
		cout << "输入错误" << endl;
	}

	system("pause");
	system("cls");
}

void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//写文件/定位到文件尾/追加写入------bug:每次运行都是将文件中的内容全部复制出来,结束时再全部放回去,如果使用为追加,则会出现数据重复

	for (int i = 0; i < this->m_num; i++)
	{
		ofs << this->m_emparr[i]->m_id << " "
			<< this->m_emparr[i]->m_name << " "
			<< this->m_emparr[i]->m_did << endl;
	}

	ofs.close();
}

int WorkManager::getnum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id, did;
	string name;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)//------------------------------------------------------------------------
	{
		//记录人数
		num++;
	}
	ifs.close();
	return num;
}

void WorkManager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id, did;
	string name;

	int index = 0;//数组中引索位置
	while (ifs >> id && ifs >> name && ifs >> did)//将文件中的数据导入到数组中/利用while循环
	{
		Worker* worker = NULL;

		if (did == 1)
		{
			worker = new Employee(id, name, did);
		}

		else if (did == 2)
		{
			worker = new Manager(id, name, did);
		}

		else if (did == 3)
		{
			worker = new Boss(id, name, did);
		}


		this->m_emparr[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkManager::showemp()
{
	if (this->fileisemply)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_num; i++)
		{
			this->m_emparr[i]->showinfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkManager::isexist(int id)
{
	for (int i = 0; i < this->m_num; i++)
	{
		if (this->m_emparr[i]->m_id == id)
		{
			return i;//返回在数组中的位置
		}
	}
	return -1;
}

void WorkManager::del_emp()
{
	if (this->fileisemply)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入要删除的职工编号" << endl;
		int id;
		cin >> id;

		int judge= this->isexist(id);

		if (judge !=-1)
		{
			this->m_emparr[judge]->showinfo();//---------------------无法展示详细信息,未知错误**********************--已知,[id]改为[id-1]//治标不治本
			//想法:把这段放到for循环中****
			//调用isexist
			cout << "输入1确认删除,输入2取消删除" << endl;
			int z;
			cin >> z;
			if (z == 1)
			{
				for (int i = judge; i < this->m_num - 1; i++)
				{
					this->m_emparr[i] = this->m_emparr[i + 1];
				}
				this->m_num--;
				this->save();
				cout << "删除成功" << endl;
			}
			else
			{
				cout << "删除取消" << endl;
			}
		}
		else
		{
			cout << "删除失败,未找到该员工" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkManager::mod_emp()
{
	if (this->fileisemply)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号" << endl;
		int id;
		cin >> id;

		int ret = this->isexist(id);
		if (ret!=-1)//成功查找到该职工
		{
			this->m_emparr[ret]->showinfo();//显示员工旧信息
			delete this->m_emparr[ret];

			int newid, newdid;
			string newname;

			cout << "查到第" << id << "号员工，请输入新员工号" << endl;
			cin >> newid;
			cout << "请输入新姓名：" << endl;
			cin >> newname;
			cout << "请输入新岗位： " << endl;
			cin >> newdid;

			Worker* worker = NULL;

			switch (newdid)
			{
				case 1:
					worker = new Employee(newid, newname, newdid);
					break;
				case 2:
					worker = new Manager(newid, newname, newdid);
					break;
				case 3:
					worker = new Boss(newid, newname, newdid);
					break;
				default:
					break;
			}
			this->m_emparr[ret] = worker;//将修改后的数据储存到数组原位置中

			cout << "修改成功" << endl;

			this->save();
		}
		else
		{
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::find_emp()
{
	cout << "1.按员工id查找" << endl;
	cout << "2.按姓名查找" << endl;//后续可以加入显示不同职位员工的功能
	int way;
	cin >> way;

	if (way == 1)
	{
		cout << "请输入员工id：" << endl;
		int id;
		cin >> id;

		int ret = isexist(id);
		if (ret != -1)
		{
			this->m_emparr[ret]->showinfo();
		}
		else
		{
			cout << "查找失败,无效id" << endl;
		}
	}
	else if (way == 2)
	{
		cout << "请输入姓名" << endl;
		string name;
		cin >> name;

		int ret;
		bool flag = false;//查到的标志
		for (int i = 0; i < this->m_num; i++)
		{
			if (name == this->m_emparr[i]->m_name)
			{
				ret = i;
				this->m_emparr[ret]->showinfo();
				flag = true;
				break;
			}
		}
		if (flag == false)//不会提示单等号错误，并返回给if：0
		{
			cout << "查找失败，无效姓名" << endl;
		}
		cout << "1" << endl;
	}
	else
	{
		cout << "输入错误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkManager::sort_emp()
{
	if (this->fileisemply)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.按照id进行升序排序" << endl;
		cout << "2.按照id进行降序排序" << endl;
		int select;
		cin >> select;

		for (int i = 0; i < this->m_num; i++)//排序算法-----------------------------------------
		{
			int minormax = i;
			for (int j = i + 1; j < this->m_num; j++)
			{
				if (select == 1)
				{
					if (this->m_emparr[minormax]->m_id > this->m_emparr[j]->m_id)
					{
						minormax = j;
					}
				}
				else
				{
					if (this->m_emparr[minormax]->m_id < this->m_emparr[j]->m_id)
					{
						minormax = j;
					}
				}
			}
			if (i != minormax)
			{
				Worker* tmp = m_emparr[i];
				m_emparr[i] = m_emparr[minormax];
				m_emparr[minormax] = tmp;
			}
		}

		cout << "排序成功，排序结果为： " << endl;
		this->save();
		this->showemp();
	}
	//system("pause");
	//system("cls");//在showemp中已存在
}

void WorkManager::clean_file()
{
	cout << "确认清空?" << endl;
	cout << "输入1确认清空" << endl;
	cout << "输入2取消清空" << endl;
	int select;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//如果存在删除文件重新创建
		ofs.close();

		if (this->m_emparr != NULL)
		{
			for (int i = 0; i < this->m_num; i++)
			{
				if (this->m_emparr[i] != NULL)//一级指针置空，但一级指针的数据还保留在二级指针中
				{
					delete this->m_emparr[i];
				}
			}
			delete this->m_emparr;
			this->m_emparr = NULL;//置空二级数组指针
			this->m_num = 0;//初始化人数
			this->fileisemply = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}