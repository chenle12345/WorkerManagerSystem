#pragma once
#include <string>
#include <iostream>
using namespace std;
#include "Worker.h"

class Employee : public Worker
{
public:
	Employee(int id, string name, int dId);

	virtual void showInfo();

	virtual string getDeptName();

};

