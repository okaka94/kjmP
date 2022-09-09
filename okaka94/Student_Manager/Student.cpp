#include "Student.h"



Student::Student() {                                 

    s_name[0] = 0;                               // 0 값으로 초기화 (생성자 이용)
    i_age = 0;
    i_kor = 0;
    i_eng = 0;
    i_math = 0;
    i_total = 0;
    i_avg = 0.0;
    p_next = nullptr;
    p_prev = nullptr;

}

Student::~Student() {

 
}