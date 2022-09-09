#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <cmath>

class Employee
{
protected:
	char m_name[10];
	int	 m_rank;
	int  m_payroll_scheme;
	int  m_etc;

public:
	Employee();
	Employee(char*, int, int, int); 
	const char* Get_name(int print = 0);
	const int Get_rank(int print = 0);
	const int Get_payroll_scheme(int print = 0);

	virtual ~Employee();

	virtual const int Calculate() = 0;
	virtual const int Get_etc(int num)=0;
};

class Hourly : public Employee {

public : 
	//const char* Get_name(int print = 0);
	//const int Get_rank(int print = 0);
	//const int Get_payroll_scheme(int print = 0);
	const int Get_etc(int print = 0);
	const int Calculate();


	Hourly();
	Hourly(const char*, int, int, int);
	~Hourly();

};

class Monthly : public Employee {

public:
	//const char* Get_name(int print = 0);
	//const int Get_rank(int print = 0);
	//const int Get_payroll_scheme(int print = 0);
	const int Get_etc(int print = 0);
	const int Calculate();

	Monthly();
	Monthly(const char*, int, int, int);
	~Monthly();

};

class Yearly : public Employee {

public:
	//const char* Get_name(int print = 0);
	//const int Get_rank(int print = 0);
	//const int Get_payroll_scheme(int print = 0);
	const int Get_etc(int print = 0);
	const int Calculate();

	Yearly();
	Yearly(const char*, int, int, int);
	~Yearly();

};