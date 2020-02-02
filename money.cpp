/********
 Author: Clay Honeycutt
 Program: Money class - program assignment #1
 Due Date: Feb 3, 2020
 Purpose: Convert between formats expressing money
 ********/
#include "money.h"

// convert current currency values to a string
string Money::toString() {
    // build string5
    stringstream ss;
    ss << hundreds << " hundreds "
        << tens << " tens "
        << fives << " fives "
        << ones << " ones "
        << quarters << " quarters "
        << dimes << " dimes "
        << nickels << " nickels "
        << cents << " pennies";

    return ss.str();
}

// format amount as a local currency and return
string Money::toCurrency(double amount) {
    stringstream ss;
    ss.imbue(locale(""));

    ss << showbase << put_money(amount * 100);

    return ss.str();
}

// convert currency to float
string Money::processChange() {
    cin >> hundreds >> tens >> fives >> ones >> quarters >> dimes >> nickels >> cents;

    stringstream ss;
    ss << toString() << " = " << toCurrency(calculateTotal());

    return ss.str();
}

// convert float to change
string Money::processFloat() {
    double amount;
    cin >> amount;

    calculateChange(amount);

    stringstream ss;
    ss << toCurrency(amount) << " = " << toString() << endl;

    return ss.str();
}

// convert float to dollar words & cents
string Money::processCheck() {
    double amount;
    cin >> amount;

    int dollarsAsInteger = (int) amount; // get amount of dollars as an integer, ex. 25.31 = 25
    int centsAsInteger = ((int) (amount * 100)) % 100; // get amount of cents as integer, ex. 25.31 = 31

    // fix casting error if one occured
    if ((amount - double(centsAsInteger) / 100) - dollarsAsInteger > .009) centsAsInteger++; // if actual amount minus cents is greater than dollar amount by 1 cent, add 1 cent to fix casting error

    stringstream ss;
    ss << "check for " << toCurrency(amount) << " = " << checkForm(dollarsAsInteger);
  
    if (dollarsAsInteger != 1) ss << "dollars and "; // plural
    else ss << "dollar and "; // singular

    ss << checkForm(centsAsInteger);

    if (centsAsInteger != 1) ss << "cents"; // plural
    else ss << "cent"; // singular
         
    ss << endl;

    return ss.str();
}

// calculate difference and compute change values
string Money::processChangeFloat() {
    double paid, cost, change;
    cin >> paid >> cost;

    change = paid - cost;

    calculateChange(change);

    stringstream ss;
    ss << "change back on " << toCurrency(paid) << " for purchase of "
        << toCurrency(cost) << " is " << toCurrency(change) << " which is " << toString() << endl;

    return ss.str();
}

// calculate difference and compute change values
string Money::processChangeChange() {
    double cost;
    cin >> hundreds >> tens >> fives >> ones >> quarters >> dimes >> nickels >> cents;
    cin >> cost;

    double paid = calculateTotal();
    double change = paid - cost;

    // start building string, will use toString() again after changing values for currency
    stringstream ss;
    ss << "change back on " << toString() << " for purchase of " << toCurrency(cost);

    // get change form for change
    calculateChange(change);

    // continue building string
    ss << " is " << toCurrency(change) << " which is " << toString() << endl;

    return ss.str();
}

// calculates amount of each type of currency for float amount
void Money::calculateChange(double amount) {
    int amountAsInteger = (int) (amount * 100); // make total amount an integer by multiplying by 100, ex. 25.31 = 2331 

    // fix casting error if one occured
    if (amount - double(amountAsInteger) / 100 > .009) amountAsInteger++; // if actual amount is 1 cent more than integer amount, add 1 cent to fix 

    // taking advantage of integer division to find smallest possible distribution, multiplied all currency values by 100 to match amountAsInteger
    hundreds = amountAsInteger / 10000;
    amountAsInteger %= 10000;

    tens = amountAsInteger / 1000;
    amountAsInteger %= 1000;

    fives = amountAsInteger / 500;
    amountAsInteger %= 500;

    ones = amountAsInteger / 100;
    amountAsInteger %= 100;

    quarters = amountAsInteger / 25;
    amountAsInteger %= 25;

    dimes = amountAsInteger / 10;
    amountAsInteger %= 10;

    nickels = amountAsInteger / 5;
    amountAsInteger %= 5;

    cents = amountAsInteger; // anything left is pennies
}

// calculate float amount from amount of each type of currency
double Money::calculateTotal() {
    double total = double(hundreds) * 100
        + double(tens) * 10
        + double(fives) * 5
        + double(ones)
        + double(quarters) * .25
        + double(dimes) * .1
        + double(nickels) * .05
        + double(cents) * .01; // casted values to double to avoid casting errors when multiplying

    return total;
}

// convert integer amount into text for check
string Money::checkForm(int amount) {
    stringstream ss;
    
    if (amount >= 100) ss << checkForm(amount / 100) << "hundred "; // recursively call to get amount of hundreds in text form

    // get values of tens in text form
    amount %= 100;
	if (amount >= 10 && amount < 20) {
		if (amount == 10) ss << "ten ";
		else if (amount == 11) ss << "eleven ";
		else if (amount == 12) ss << "twelve ";
		else if (amount == 13) ss << "thirteen ";
		else if (amount == 14) ss << "fourteen ";
		else if (amount == 15) ss << "fifteen ";
		else if (amount == 16) ss << "sixteen ";
		else if (amount == 17) ss << "seventeen ";
		else if (amount == 18) ss << "eighteen ";
		else if (amount == 19) ss << "nineteen ";

		return ss.str(); // return here since numbers 10 - 19 are unique
	}
    else if (amount >= 20 && amount < 30) ss << "twenty ";
    else if (amount >= 30 && amount < 40) ss << "thirty ";
    else if (amount >= 40 && amount < 50) ss << "forty ";
    else if (amount >= 50 && amount < 60) ss << "fifty ";
    else if (amount >= 60 && amount < 70) ss << "sixty ";
    else if (amount >= 70 && amount < 80) ss << "seventy ";
    else if (amount >= 80 && amount < 90) ss << "eighty ";
    else if (amount >= 90) ss << "ninety ";
    
    // get singular values in text form
    amount %= 10;
    if (amount == 0 && ss.str().empty()) ss << "zero "; // only use zero if stringstream object is empty, meaning it is actually zero not just a multiple of 10
    else if (amount == 1) ss << "one ";
    else if (amount == 2) ss << "two ";
    else if (amount == 3) ss << "three ";
    else if (amount == 4) ss << "four ";
    else if (amount == 5) ss << "five ";
    else if (amount == 6) ss << "six ";
    else if (amount == 7) ss << "seven ";
    else if (amount == 8) ss << "eight ";
    else if (amount == 9) ss << "nine ";

    return ss.str();
}