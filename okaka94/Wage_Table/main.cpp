#include <iostream>
#include "Employee.h"

int main() {

	Employee* employee[] = {
		new Hourly("권상우",0,0,200),
		new Hourly("조인성",0,0,220),
		new Monthly("감우성",1,1,3),
		new Monthly("강동원",1,1,5),
		new Yearly("황정민",2,2,3),
		new Monthly("박중훈",2,1,15),
		new Monthly("최민식",3,1,20),
		new Yearly("정진영",3,2,3),
		new Hourly("안성기",4,0,50),
		new Yearly("송강호",4,2,4)
	};

	for (int i = 0; i < 10; i++) {
		employee[i]->Get_name(1);
		std::cout << "\t";
		employee[i]->Get_rank(1);
		std::cout << "\t";
		employee[i]->Get_payroll_scheme(1);
		std::cout << "\t";
		employee[i]->Get_etc(1);
		std::cout << "\t";
		std::cout << employee[i]->Calculate() << std::endl;
		
		delete employee[i];
	}
	

	return 0;
}
