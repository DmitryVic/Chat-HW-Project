#pragma once
#include <vector>
using namespace std;

//��������� ���� �� ������� � �������, ���� ��, �� ���������� true, false - ���
template <typename T>
bool contains(const std::vector<T>& vec, const T& value){
    for (const auto& el: vec)
    {
        if (el == value)
        {
            return true;
        }
    }
    return false;
}