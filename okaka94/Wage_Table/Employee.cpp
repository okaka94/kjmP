#include "Employee.h"


Employee::Employee(char* name , int rank, int payroll_scheme, int etc) {

	/*Employee* new_emp = new Employee;*/

	strcpy(m_name, name);
	m_rank = rank;
	m_payroll_scheme = payroll_scheme;
	m_etc = etc;

}
Employee::Employee() {
}
Employee::~Employee() {

	//std::cout << "�θ� Ŭ���� �Ҹ�" << std::endl;
}

const char* Employee::Get_name(int print) {
	if (print == 1)
		std::cout << m_name;

	return m_name;
}


const int Employee::Get_rank(int print) {

	if (print == 1) {
		switch (m_rank)
		{
		case 0: {
			std::cout << " ��� ";
			break;
		}
		case 1: {
			std::cout << " �븮 ";
			break;
		}
		case 2: {
			std::cout << " ���� ";
			break;
		}
		case 3: {
			std::cout << " ���� ";
			break;
		}
		case 4: {
			std::cout << " �̻� ";
			break;
		}
		default:
			break;
		}
	}


	return m_rank;
}

const int Employee::Get_payroll_scheme(int print) {

	if (print == 1) {
		switch (m_payroll_scheme)
		{
		case 0: {
			std::cout << " �ñ��� ";
			break;
		}
		case 1: {
			std::cout << " ������ ";
			break;
		}
		case 2: {
			std::cout << " ������ ";
			break;
		}

		default:
			break;
		}
	}

	return m_payroll_scheme;
}


Hourly::Hourly() {
}

Hourly::Hourly(const char* name, int rank, int payroll_scheme, int etc) {

	//Hourly* new_emp = new Hourly;

	//strcpy(new_emp->m_name, name);
	//new_emp->m_rank = rank;
	//new_emp->m_payroll_scheme = payroll_scheme;
	//new_emp->m_etc = etc;
	//
	strcpy(m_name, name);
	m_rank = rank;
	m_payroll_scheme = payroll_scheme;
	m_etc = etc;
}




const int Hourly::Get_etc(int print) {

	if (print == 1) {
		
		std::cout << "�� " << m_etc << "�ð� �ٹ�\t";
	}
	
	return m_etc;

}
const int Hourly::Calculate() {

	int wage = 1;
	
	wage = pow(2, m_rank) * m_etc;
	
	return wage;
}

Hourly::~Hourly() {
	//std::cout << "�ڽ� Ŭ���� �Ҹ�" << std::endl;
}


//-----------------------------

//Monthly::Monthly() {
//}

Monthly::Monthly(const char* name, int rank, int payroll_scheme, int etc) {

	//Hourly* new_emp = new Hourly;

	//strcpy(new_emp->m_name, name);
	//new_emp->m_rank = rank;
	//new_emp->m_payroll_scheme = payroll_scheme;
	//new_emp->m_etc = etc;
	//
	strcpy(m_name, name);
	m_rank = rank;
	m_payroll_scheme = payroll_scheme;
	m_etc = etc;
}

Monthly::Monthly() {

}

const int Monthly::Get_etc(int print) {

	if (print == 1) {

		std::cout << m_etc << "����\t\t";
	}

	return m_etc;

}
const int Monthly::Calculate() {

	int wage = 200;
	

	wage = wage + (m_rank + 1) * 20 + (m_etc * 5);

	return wage;
}

Monthly::~Monthly() {
	//std::cout << "�ڽ� Ŭ���� �Ҹ�" << std::endl;
}

//---------------------------------------

Yearly::Yearly() {

}


Yearly::Yearly(const char* name, int rank, int payroll_scheme, int etc) {

	//Hourly* new_emp = new Hourly;

	//strcpy(new_emp->m_name, name);
	//new_emp->m_rank = rank;
	//new_emp->m_payroll_scheme = payroll_scheme;
	//new_emp->m_etc = etc;
	//
	strcpy(m_name, name);
	m_rank = rank;
	m_payroll_scheme = payroll_scheme;
	m_etc = etc;
}


const int Yearly::Get_etc(int print) {

	if (print == 1) {

		std::cout << "�ɷ� " << m_etc << "���\t";
	}

	return m_etc;

}
const int Yearly::Calculate() {

	int wage = 2000;
	

	wage = (wage + (m_rank + 1) * 1000 + (m_etc + 1) * 500) / 12;

	return wage;
}

Yearly::~Yearly() {
	//std::cout << "�ڽ� Ŭ���� �Ҹ�" << std::endl;
}