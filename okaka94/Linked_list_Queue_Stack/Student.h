#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <assert.h>


class Student                       // 학생 정보 양식 자체는 오픈해도 됨 (입력,출력을 다른 곳에서 할거니까)
{
public:
    char s_name[4];
    int i_age;
    int i_kor;
    int i_eng;
    int i_math;
    int i_total;
    float i_avg;
    //Student* p_next;
    //Student* p_prev;


    Student();
    ~Student();
   
};