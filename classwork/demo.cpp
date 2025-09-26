#include <iostream> // cannot print if not included; printf comes from another library import
using namespace std; // if you don't do this, must do std::{cout/endl; or others} -- interviews: DON'T use this (for some reason?)

int main() {
    // Basic output with cout - concatenates with << operator
    cout << 3.14 << " Hello, world!" << endl; // or << " " for a manual space if not truncated in "Hello, world!"

    // Different ways to represent the number 25 in different number systems
    int a = 25;         // Standard decimal representation
    int b = 0b11001;    // use 0b to indicate it is a binary number; binary 25
    int c = 031;        // '0' for octal; octal 25
    int d = 0x19;       // hexadecimal 25

    // Setting output format to hexadecimal - affects all subsequent numeric output
    cout << hex;
    cout << a << ' ' << b << ' ' << c << ' ' << d << endl; // All will print as hex: 19 19 19 19

    // Setting output format to octal - affects all subsequent numeric output
    cout << oct;
    cout << a << ' ' << b << ' ' << c << ' ' << d << endl; // All will print as octal: 31 31 31 31

    // Setting output format back to decimal - affects all subsequent numeric output
    cout << dec;
    cout << a << ' ' << b << ' ' << c << ' ' << d << endl; // All will print as decimal: 25 25 25 25

    // Character manipulation using ASCII values
    char ch = 'A'; // ASCII value 65

    char ch1 = ch + 32; // lower 'a'; looks a little strange - ASCII 'A' + 32 = ASCII 'a' (97)

    // Bitwise Boolean Operators: &, |, ^, ~
    // '&&' '||' 'xor' '!'(not) in cs111 terms, respectively 

    // Using bitwise OR to convert uppercase to lowercase
    char ch2 = ch | 0b00100000; // preserve the same number (adding 32); lower 'a'
                                // OR with bit 5 set (32 in decimal) flips case bit
    
    // Same operation but using hexadecimal notation
    char ch3 = ch | 0x20; // 0x20 = 32 in decimal = 0b00100000 in binary

    cout << ch << ' ' << ch1 << ' ' << ch2 << ' ' << ch3 << endl; // Prints: A a a a

    // xor properties 
    // X ^ X --> 0 (xor with itself yields zero)
    // X ^ 11....111 --> 00...0000 (flips everything; similar to ~ (!))

    // Converting from lowercase to uppercase using bitwise AND
    char upper = ch1 & 0xDF; // 0xDF = 11011111 in binary - clears bit 5 (the case bit)
                             // AND with mask that has case bit cleared converts to uppercase
    
    cout << upper << endl; // Prints: A

    // Bitshift operators - these multiply/divide by powers of 2

    // Left shift: y = x << #pos
    // Each position shifted left multiplies by 2
    // ex: 
    // int a = 25;
    // int b = a << 3; b is 200 (shifted by 3 positions (2^3) 25 * 8 = 200)

    // Right shift: y = x >> #pos  
    // Each position shifted right divides by 2 (integer division)
    // ex:
    // int a = 25;
    // int b = a >> 2; b is 6 (shifted to the right by 2 positions (2^2) 25 / 4 = (int) 6.25 == 6)

    return 0; // Standard return value indicating successful program execution
}