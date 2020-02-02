/********
 Author:
 Program: Money class - program assignment #1
 Due Date: Feb 3, 2020
 Purpose:
 ********/
#ifndef MONEY_H
#define MONEY_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <locale>

using namespace std;
class Money
{
private:
    int hundreds, tens, fives, ones, quarters, dimes, nickels, cents;
    string toString();
    string toCurrency(double amount);
    void calculateChange(double amount);
    double calculateTotal();
    string checkForm(int amount);
public:
    string processChange();
    string processFloat();
    string processCheck();
    string processChangeFloat();
    string processChangeChange();
};
#endif