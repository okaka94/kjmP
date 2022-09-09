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

	//std::cout << "부모 클래스 소멸" << std::endl;
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
			std::cout << " 사원 ";
			break;
		}
		case 1: {
			std::cout << " 대리 ";
			break;
		}
		case 2: {
			std::cout << " 과장 ";
			break;
		}
		case 3: {
			std::cout << " 부장 ";
			break;
		}
		case 4: {
			std::cout << " 이사 ";
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
			std::cout << " 시급제 ";
			break;
		}
		case 1: {
			std::cout << " 월급제 ";
			break;
		}
		case 2: {
			std::cout << " 연봉제 ";
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
		
		std::cout << "월 " << m_etc << "시간 근무\t";
	}
	
	return m_etc;

}
const int Hourly::Calculate() {

	int wage = 1;
	
	wage = pow(2, m_rank) * m_etc;
	
	return wage;
}

Hourly::~Hourly() {
	//std::cout << "자식 클래스 소멸" << std::endl;
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

		std::cout << m_etc << "년차\t\t";
	}

	return m_etc;

}
const int Monthly::Calculate() {

	int wage = 200;
	

	wage = wage + (m_rank + 1) * 20 + (m_etc * 5);

	return wage;
}

Monthly::~Monthly() {
	//std::cout << "자식 클래스 소멸" << std::endl;
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

		std::cout << "능력 " << m_etc << "등급\t";
	}

	return m_etc;

}
const int Yearly::Calculate() {

	int wage = 2000;
	

	wage = (wage + (m_rank + 1) * 1000 + (m_etc + 1) * 500) / 12;

	return wage;
}

Yearly::~Yearly() {
	//std::cout << "자식 클래스 소멸" << std::endl;
}