#pragma once
#include "Worker.h"
using namespace std;


class Boss:public Worker
{
public:
	Boss(int id, string name, int dId);
	
	void showInfo();

	string getDeptName();

};
