#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include <fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public:
	WorkerManager(int empNum, Worker** workerArr);
	WorkerManager();
	~WorkerManager();
	//展示菜单
	void showMenu();
	void ExitSystem();
	void addWorker();
	void save();
	//统计文件中的人数
	int getEmpNum();
	//初始化员工信息
	void initEmp();
	void showWorker();
	void deleteWorker();
	int isExist(int id);


private:
	Worker** workerArr;
	int empNum;
	//判断文件是否为空标志
	bool fileIsEmpty;

};

