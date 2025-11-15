#include <iostream>
using namespace std;
#include "workerManager.h"
#include "Employee.h"
#include "Worker.h"
#include "Manager.h"
#include "Boss.h"

int main()
{
	// 实例化管理者对象
	WorkerManager wm;

	int choice = 0;

	while (true)
	{
		// 调用展示菜单成员函数
		wm.showMenu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: // 退出系统
			wm.ExitSystem();
			break;
		case 1: // 增加职工
			wm.addWorker();
			break;
		case 2: // 显示职工
			wm.showWorker();
			break;
		case 3: // 删除职工
			wm.deleteWorker();
			break;
		case 4: // 修改职工
			break;
		case 5: // 查找职工
			break;
		case 6: // 排序职工
			break;
		case 7: // 清空文档
			break;
		default:
			system("cls"); // 清屏操作
			break;
		}

	}

	/*Worker* worker = NULL;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "王五", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "赵柳", 3);
	worker->showInfo();
	delete worker;*/

	system("pause");
	return 0;
}