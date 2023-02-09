#include"workManager.h"

using namespace std;
WorkManager::WorkManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ����������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;//�������

		this->m_emparr = NULL;//��ʼ������ָ��
		this->m_num = 0;//��ʼ������
		this->fileisemply = true;

		ifs.close();
		return;
	}
	
	//�ļ����ڵ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())//�ж��Ƿ���βλ
	{
		//cout << "�ļ�Ϊ��" << endl;//�������
		this->m_emparr = NULL;//��ʼ������ָ��
		this->m_num = 0;//��ʼ������
		this->fileisemply = true;

		ifs.close();
		return;
	}

	//�ļ��������м�¼
	int num = this->getnum();
	//cout << "ְ������Ϊ: " << num << endl;//���Դ���
	this->m_num = num;//���³�Ա����

	this->m_emparr = new Worker * [this->m_num];//����ְ������������

	this->init_emp();//��ʼ������

	ifs. close();
}

WorkManager::~WorkManager()
{

}

void WorkManager::show_menu()
{
	
		cout << "********************************************" << endl;
		cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
		cout << "*************  0.�˳��������  *************" << endl;
		cout << "*************  1.����ְ����Ϣ  *************" << endl;
		cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
		cout << "*************  3.ɾ����ְְ��  *************" << endl;
		cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
		cout << "*************  5.����ְ����Ϣ  *************" << endl;
		cout << "*************  6.���ձ������  *************" << endl;
		cout << "*************  7.��������ĵ�  *************" << endl;
		cout << "********************************************" << endl;
		cout << endl;
	
}

void WorkManager::exitsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkManager::add_emp()
{
	cout << "��������ӵ�ְ������" << endl;
	int addnum;
	cin >> addnum;

	if (addnum > 0)
	{
		int newsize = this->m_num + addnum;//�����¿ռ��С

		Worker** newspace = new Worker * [newsize*sizeof(Worker)];//�����¿ռ�//-------------��[newsize]��Ϊ[newsize*sizeof(Worker)],����������������

		if (this->m_emparr != NULL)//��ԭ�ռ������ݷŵ��¿ռ���
		{
			for (int i = 0; i < this->m_num; i++)
			{
				newspace[i] = this->m_emparr[i];
			}
		}

		//����������
		for (int i = 0; i < addnum; i++)
		{
			int id;
			string name;
			int did;

			cout << "�������" << i + 1 << "����ְ�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ������" << endl;
			cin >> name;
			cout << "��ѡ��ְ����λ: " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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

			newspace[this->m_num + i] = worker;//�������ݴ��浽������----------------------�������������

			//delete worker;//----------------���ܴ�������
			//worker = NULL;
		}

		delete[] this->m_emparr;//�ͷ�ԭ�пռ�

		this->m_emparr = newspace;//�����µĿռ�ָ��------------��newspace���������ݸ�emparr,���ڵ�һ�μ�¼�н�emparrתΪ����

		this->m_num = newsize;//��������

		this->save();//���浽txt

		this->fileisemply = false;//����Ա����Ϊ��

		cout << "�ɹ����" << addnum << "��Ա��,����Ա��" << this->m_num << "��" << endl;
	}
	else
	{
		cout << "�������" << endl;
	}

	system("pause");
	system("cls");
}

void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//д�ļ�/��λ���ļ�β/׷��д��------bug:ÿ�����ж��ǽ��ļ��е�����ȫ�����Ƴ���,����ʱ��ȫ���Ż�ȥ,���ʹ��Ϊ׷��,�����������ظ�

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
		//��¼����
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

	int index = 0;//����������λ��
	while (ifs >> id && ifs >> name && ifs >> did)//���ļ��е����ݵ��뵽������/����whileѭ��
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
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
			return i;//�����������е�λ��
		}
	}
	return -1;
}

void WorkManager::del_emp()
{
	if (this->fileisemply)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫɾ����ְ�����" << endl;
		int id;
		cin >> id;

		int judge= this->isexist(id);

		if (judge !=-1)
		{
			this->m_emparr[judge]->showinfo();//---------------------�޷�չʾ��ϸ��Ϣ,δ֪����**********************--��֪,[id]��Ϊ[id-1]//�α겻�α�
			//�뷨:����ηŵ�forѭ����****
			//����isexist
			cout << "����1ȷ��ɾ��,����2ȡ��ɾ��" << endl;
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
				cout << "ɾ���ɹ�" << endl;
			}
			else
			{
				cout << "ɾ��ȡ��" << endl;
			}
		}
		else
		{
			cout << "ɾ��ʧ��,δ�ҵ���Ա��" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkManager::mod_emp()
{
	if (this->fileisemply)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ�����" << endl;
		int id;
		cin >> id;

		int ret = this->isexist(id);
		if (ret!=-1)//�ɹ����ҵ���ְ��
		{
			this->m_emparr[ret]->showinfo();//��ʾԱ������Ϣ
			delete this->m_emparr[ret];

			int newid, newdid;
			string newname;

			cout << "�鵽��" << id << "��Ա������������Ա����" << endl;
			cin >> newid;
			cout << "��������������" << endl;
			cin >> newname;
			cout << "�������¸�λ�� " << endl;
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
			this->m_emparr[ret] = worker;//���޸ĺ�����ݴ��浽����ԭλ����

			cout << "�޸ĳɹ�" << endl;

			this->save();
		}
		else
		{
			cout << "���޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::find_emp()
{
	cout << "1.��Ա��id����" << endl;
	cout << "2.����������" << endl;//�������Լ�����ʾ��ְͬλԱ���Ĺ���
	int way;
	cin >> way;

	if (way == 1)
	{
		cout << "������Ա��id��" << endl;
		int id;
		cin >> id;

		int ret = isexist(id);
		if (ret != -1)
		{
			this->m_emparr[ret]->showinfo();
		}
		else
		{
			cout << "����ʧ��,��Чid" << endl;
		}
	}
	else if (way == 2)
	{
		cout << "����������" << endl;
		string name;
		cin >> name;

		int ret;
		bool flag = false;//�鵽�ı�־
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
		if (flag == false)//������ʾ���ȺŴ��󣬲����ظ�if��0
		{
			cout << "����ʧ�ܣ���Ч����" << endl;
		}
		cout << "1" << endl;
	}
	else
	{
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");
}

void WorkManager::sort_emp()
{
	if (this->fileisemply)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.����id������������" << endl;
		cout << "2.����id���н�������" << endl;
		int select;
		cin >> select;

		for (int i = 0; i < this->m_num; i++)//�����㷨-----------------------------------------
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

		cout << "����ɹ���������Ϊ�� " << endl;
		this->save();
		this->showemp();
	}
	//system("pause");
	//system("cls");//��showemp���Ѵ���
}

void WorkManager::clean_file()
{
	cout << "ȷ�����?" << endl;
	cout << "����1ȷ�����" << endl;
	cout << "����2ȡ�����" << endl;
	int select;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);//�������ɾ���ļ����´���
		ofs.close();

		if (this->m_emparr != NULL)
		{
			for (int i = 0; i < this->m_num; i++)
			{
				if (this->m_emparr[i] != NULL)//һ��ָ���ÿգ���һ��ָ������ݻ������ڶ���ָ����
				{
					delete this->m_emparr[i];
				}
			}
			delete this->m_emparr;
			this->m_emparr = NULL;//�ÿն�������ָ��
			this->m_num = 0;//��ʼ������
			this->fileisemply = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}