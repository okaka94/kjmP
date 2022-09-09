#include <iostream>
#include "Employee.h"

int main() {

	Employee* employee[] = {
		new Hourly("�ǻ��",0,0,200),
		new Hourly("���μ�",0,0,220),
		new Monthly("���켺",1,1,3),
		new Monthly("������",1,1,5),
		new Yearly("Ȳ����",2,2,3),
		new Monthly("������",2,1,15),
		new Monthly("�ֹν�",3,1,20),
		new Yearly("������",3,2,3),
		new Hourly("�ȼ���",4,0,50),
		new Yearly("�۰�ȣ",4,2,4)
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
