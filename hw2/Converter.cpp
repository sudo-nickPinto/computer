/*
 * 
 * Nick Pinto
 * hw2
 * Ivalyo Illinkin
 * Due: 09/11/2025
 * 
 * I affirm I have upheld the highest principles of honesty and integrity in my academic work and did not commit/see any violation
 * of the Honor Code
 */

#include <iostream> // for testing only (at end of main())
#include <string>
#include <map>
using namespace std;

// given helper-methods (provided in assignment)
string to_string(const string& str) // '&' signifies str is a REFERENCE to the string object without copying it
{
    return str;
}


template<typename E1, typename E2>
void assertEquals(E1 a, E2 b)
{
    string strA = to_string(a);
    string strB = to_string(b);

    if (strA != strB) {
        cout << "failed: " << a << " != " << b << endl;
    }
}

/**
 * returns the hexadecimal symbol for values 0..15 (provided in assignment).
 */
char getSymbol(long digit)
{
    if (digit >= 0 && digit <= 9) {
        return (char)('0' + digit);
    }
    else {
        return (char)('A' + (digit - 10));
    }
}

/**
 * returns the decimal values 0..15 for hexadecimal digit 0..F (provided in assignment).
 */
long getValue(char symbol)
{
    if (symbol >= '0' && symbol <= '9') {
        return symbol - '0';
    }
    else {
        return (symbol - 'A') + 10;
    }
}

/**
 * converts a Base 10 number to the given base in [2..10].
 */
long from10(long number, int base)
{
    if (base < 2 || base > 10) { // C++ doesn't have IllegalArgumentExceptions, so just return -1
        return -1;
    }

    if (number == 0) {
        return 0;
    }

    long position = 1;
    long result = 0;
    long n = number;

    while (n > 0) {
        long remainder = n % base;
        result = result + (remainder * position);
        position = position * 10;
        n = n / base;
    }
    return result;
}

/**
 * converts a Base10 number to base 16 and returns a String result
 */
string from10(long number)
{
    if (number == 0) {
        return "0";
    }

    char remainders[16]; // max 16 digits for long type
    int digitCount = 0;

    while (number > 0) {
        long remainder = number % 16;
        remainders[digitCount] = getSymbol(remainder);
        digitCount++;
        number = number / 16;
    }

    // reverse order of hexDigit array filled with remainders (read right to left)
    string result = "";
    for (int i = digitCount - 1; i >= 0; i--) {
        result += remainders[i];
    }

    return result;
}

/**
 * converts a number from the given base in [2..10] (inclusive) to Base10
 */
long to10(long number, int base)
{
    if (base < 2 || base > 10) {
        return -1; // same reasoning as "from10" method conditional
    }

    long result = 0;
    long power = 1;

    while (number > 0) {
        long digit = number % 10;
        result = result + (digit * power);
        power = power * base;
        number = number / 10;
    }
    return result;
}

/**
 * converts a hexadecimal string to Base10
 */
long to10(string number)
{
    if (number.length() == 0) {
        return -1;
    }

    // TODO:  convert to uppercase(?) -- ask in Office Hours. I know converting to upper isnt needed, but am curious nonetheless. 
    // For transparency, used stack overflow for toupper() method
    // Errors with different size: 'int' and 'size_type' aka unsigned long
    for (int i = 0; i < number.length(); i++){
        number[i] = toupper(number[i]);
    }
    
     
    long result = 0;
    long power = 1;

    for (int i = number.length() - 1; i >= 0; i--) {
        char c = number[i];
        long digit = getValue(c);
        result = result + (digit * power);
        power = power * 16;
    }
    return result;
}

/**
 * builds and returns a map with the single Roman "digits" and their decimal equivalents 
 */
map<char, int> buildRomanMap()
{
    map<char, int> romanMap = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    return romanMap;
}

/**
 * converts a Roman numeral string to Base10.
 */
int fromRoman(string number)
{
    if (number.length() == 0) {
        return -1;
    }

    // convert to uppercase
     for (int i = 0; i < number.length(); i++){
        number[i] = toupper(number[i]);
    }
    

    map<char, int> romanMap = buildRomanMap();
    int result = 0;

    // loop through all but last character in input
    for (int i = 0; i < number.length() - 1; i++) { // learned size_t in OS
        char currChar = number[i];
        char nextChar = number[i + 1];

        int currNum = romanMap[currChar];
        int nextNum = romanMap[nextChar];

        if (currNum < nextNum) {
            result = result - currNum; // subtractive case
        }
        else {
            result = result + currNum; // additive case
        }
    }

    // handle last character
    char last = number[number.length() - 1];
    int lastInt = romanMap[last];
    result = result + lastInt;
    
    return result;
}

// test cases
int main()
{
    // from 10 to base b cases

    // 120 in different bases
    assertEquals(from10(120, 2), 1111000L);
    assertEquals(from10(120, 3), 11110L);
    assertEquals(from10(120, 7), 231L);
    assertEquals(from10(120, 8), 170L);
    assertEquals(from10(120, 10), 120L);

    // 12345 in different bases
    assertEquals(from10(12345, 2), 11000000111001L);
    assertEquals(from10(12345, 3), 121221020L);
    assertEquals(from10(12345, 7), 50664L);
    assertEquals(from10(12345, 8), 30071L);
    assertEquals(from10(12345, 10), 12345L);

    // to10 from base b cases
    // convert numbers aforementioned from different bases
    assertEquals(to10(1111000, 2), 120L);
    assertEquals(to10(11000000111001L, 2), 12345L);

    assertEquals(to10(11110, 3), 120L);
    assertEquals(to10(121221020, 3), 12345L);

    assertEquals(to10(231, 7), 120L);
    assertEquals(to10(50664, 7), 12345L);

    assertEquals(to10(170, 8), 120L);
    assertEquals(to10(30071, 8), 12345L);

    assertEquals(to10(120, 10), 120L);
    assertEquals(to10(12345, 10), 12345L);

    // from 10 to hex cases
    assertEquals(from10(120), string("78"));
    assertEquals(from10(12345), string("3039"));

    // from hex to 10 cases
    assertEquals(to10(string("78")), 120L);
    assertEquals(to10(string("3039")), 12345L);

    // roman cases

    // 13 example numbers
    assertEquals(fromRoman("XXXIX"), 39);
    assertEquals(fromRoman("CCXLVI"), 246);
    assertEquals(fromRoman("DCCLXXXIX"), 789);
    assertEquals(fromRoman("MMCDXXI"), 2421);
    assertEquals(fromRoman("CLX"), 160);
    assertEquals(fromRoman("CCVII"), 207);
    assertEquals(fromRoman("MIX"), 1009);
    assertEquals(fromRoman("MLXVI"), 1066);
    assertEquals(fromRoman("MMMCMXCIX"), 3999);
    assertEquals(fromRoman("MDCCLXXVI"), 1776);
    assertEquals(fromRoman("MCMXVIII"), 1918);
    assertEquals(fromRoman("MCMXLIV"), 1944);
    assertEquals(fromRoman("MMXXV"), 2025);

    // rows 4 and 6 from the table
    assertEquals(fromRoman("CD"), 400);
    assertEquals(fromRoman("XL"), 40);
    assertEquals(fromRoman("IV"), 4);

    assertEquals(fromRoman("DC"), 600);
    assertEquals(fromRoman("LX"), 60);
    assertEquals(fromRoman("VI"), 6);

    cout << "Testing complete and passed" << endl;
    return 0;
}

