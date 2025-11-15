#include "workerManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"



WorkerManager::WorkerManager(int empNum, Worker** workerArr)
{
	this->empNum = empNum;
	this->workerArr = workerArr;
}

WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->empNum = 0;
		this->workerArr = NULL;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->empNum = 0;
		this->workerArr = NULL;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在且不为空
	int num = this->getEmpNum();
	//cout << "职工人数为：" << num << endl;
	this->empNum = num;
	//开辟空间
	this->workerArr = new Worker*[this->empNum];
	//将文件中的数据存到数组中
	this->initEmp();
	/*for (int i = 0; i < this->empNum; i++)
	{
		cout << "职工编号： "  << this->workerArr[i]->m_Id
			<< " 职工姓名： " << this->workerArr[i]->m_Name
			<< " 职工岗位： " << this->workerArr[i]->m_DeptId << endl;
	}*/
	
}


WorkerManager::~WorkerManager()
{
	if (this->workerArr != nullptr)
	{
		delete[] this->workerArr;
		this->workerArr = nullptr;
	}
}

void WorkerManager::showWorker()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->empNum; i++)
		{
			this->workerArr[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::deleteWorker()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->isExist(id);
		if (index > -1)
		{
			for (int i = 0; i < this->empNum - 1; i++)
			{
				if (id == this->workerArr[i]->m_Id)
				{
					this->workerArr[i] = this->workerArr[i + 1];
				}
			}
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");	
}

int WorkerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->empNum; i++)
	{
		if (this->workerArr[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::modifyWorker()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要修改的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->isExist(id);
		if (index > -1)
		{
			delete this->workerArr[index];
			int newId = 0;
			string newName = "";
			int newType = 0;
			cout << "查到该职工，请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请输入新岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> newType;
			Worker* worker = nullptr;
			switch (newType)
			{
			case 1:
				worker = new Employee(newId, newName, newType);
				break;
			case 2:
				worker = new Manager(newId, newName, newType);
				break;
			case 3:
				worker = new Boss(newId, newName, newType);
				break;
			default:
				break;
			}
			this->workerArr[index] = worker;
			this->save();
			cout << "修改成功" << endl;
		}
		else
		{
			cout << "修改失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->empNum; i++)
	{
		ofs << this->workerArr[i]->m_Id << " "
			<< this->workerArr[i]->m_Name << " "
			<< this->workerArr[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while(ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	this->workerArr = new Worker * [this->empNum];
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		this->workerArr[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkerManager::showMenu()
{
	cout << "*******************************************" << endl;
	cout << "********   欢迎使用职工管理系统！ *********" << endl;
	cout << "********   0.退出管理程序！ ***************" << endl;
	cout << "********   1.增加职工信息！ ***************" << endl;
	cout << "********   2.显示职工信息！ ***************" << endl;
	cout << "********   3.删除离职职工！ ***************" << endl;
	cout << "********   4.修改职工信息！ ***************" << endl;
	cout << "********   5.查找职工信息！ ***************" << endl;
	cout << "********   6.按照编号排序！ ***************" << endl;
	cout << "********   7.清空所有文档！ ***************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;

}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0); // 退出程序
}


void WorkerManager::addWorker()
{
	cout << "请问需要添加几人？" << endl;
	int num = 0;
	cin >> num;
	if (num > 0)
	{
		int newSize = this->empNum + num;
		Worker ** newSpace = new Worker*[newSize]();
		if (this->workerArr != NULL)
		{
			for (int i = 0; i < this->empNum; i++)
			{
				newSpace[i] = this->workerArr[i];
			}
		}

		for (int i = 0; i < num; i++)
		{
			int id = 0;
			string name = "";
			int type = 0;
			cout << "请输入" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请输入添加人员的类型：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> type;

			Worker* worker = nullptr;
			switch (type)
			{
			case 1:
				worker = new Employee(id, name, type);
				
				break;
			case 2:
				worker = new Manager(id, name, type);
				break;
			case 3:
				worker = new Boss(id, name, type);
				break;
			default:
				break;
			}
			newSpace[this->empNum + i] = worker;
		}

		delete[] this->workerArr;
		this->workerArr = newSpace;
		this->empNum = newSize;
		this->fileIsEmpty = false;
		cout << "成功添加" << num << "名新职工" << endl;
		save();
		
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");

}