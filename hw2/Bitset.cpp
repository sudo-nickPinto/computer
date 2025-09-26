#include <iostream>
#include <string>
#include <cassert>
using namespace std;

/*
    Nick Pinto
    Ivaylo Illinkin
    CS221 Assembly
    09/11/2025

    I affirm I have upheld the highest principles of honesty and integrity in my academic work and have not committed/witnessed 
    a violation of the honor code
*/


class Bitset {
private:
    const unsigned short ZERO = 0; // zero-constant (only use this)
    unsigned short bitset;

public:
    // explicit constructor to initialize bitset with given value (why must we use explicit?)
    explicit Bitset( unsigned short theBits ){
        bitset = theBits;
    }

    // returns the value of bitset
    unsigned short getValue() {
        return bitset;
    }


    // returns true if all bits are 0
    bool none(){
        return bitset == ZERO;
    }

    // returns true if at least one bit is set to 1
    bool any(){
        return bitset != ZERO;
    }
    

    // returns true if all bits have value 1
    bool all(){
        return bitset == (unsigned short)~ZERO; // cast to u.s (~ZERO with no cast flips to 32 bit int (0xFFFFFFFF))
    }
    
    

    // inverts the bits in the set (0s to 1s and 1s to 0s)
    void flip(){
        unsigned short mask = (unsigned short) ~ZERO; 
                                      // data ^ all_ones = ~data
        bitset = bitset ^ mask;
    }
    
    

    // returns true if the bit at the given index is set to 1
    bool get(int index) {
        unsigned short mask = 1 << index; // 1 * i^2 = 1-bit mask @ index

        // check if index at bit pos is a 0 --> return false.
        return (bitset & mask) != ZERO;
        
    }

    // sets all bits to 1
    // use "or" operator 0 or 1 = 1; 1 or 1 = 1
    void set() {
        unsigned short mask = (unsigned short)~ZERO;
        bitset = bitset | mask;
    }

    // sets the bit at the given index to 1
    // also use "or" operator; 1 * i^2 = 1-bit mask @ index
    // use mask(1) and "or" with 0 or 1 to yield a 1 @ given index.
    void set(int index) {
        unsigned short mask = 1 << index;
        bitset = bitset | mask;
    }

    // sets all bits to 0
    void clear() {
       unsigned short mask = ZERO;
       bitset = bitset & mask;
    }

    // sets the bit at the given index to 0
    // make use of & operator: 0 & 0 = 0; 0 & 1 = 0

    void clear(int index) {
       unsigned short mask = 1 << index;  // mask = 0000..01000 (1 is @ idx of mask)
       mask = ~mask; // invert the mask: 1111...10111; makes original bit 0, and keeps every other bit with '& 1'
       bitset = bitset & mask;
    }

    // swap the values of the two different halves (two different bytes; [0,7] and [8,15]) of the data member
    void swap() {
        // extract bytes
        // mask is in lower byte pos ONLY
        unsigned short mask = 0xFF; // 0000 0000 1111 1111
        // higher byte
        // move higher byte to lower byte pos
        unsigned short hByte = bitset >> 8;
        hByte = hByte & mask;

        // lower byte
        // no need to move as mask is already in lower byte pos
        unsigned short lByte = bitset & mask;

        // combine bytes (lower then higher)
        // now move lByte to higher byte pos (hByte already in lower byte pos)
        bitset = (lByte << 8) | hByte;
    }

    // swaps the two halves in the high byte of the data member
    void swapHi() {
        // high byte = [15:8], need to swap [15:12] and [11:8]
        unsigned short highByte = (bitset >> 8) & 0xFF;  // extract high byte
        unsigned short upperH = (highByte >> 4) & 0x0F;  // extract upper 4 bits of high byte
        unsigned short lowerH = highByte & 0x0F;         // extract lower 4 bits of high byte
        
        // swap the two and put back in high byte position
        unsigned short swappedHigh = (lowerH << 4) | upperH;
        bitset = (bitset & 0x00FF) | (swappedHigh << 8);  
    }

    // swaps the two halves in the low byte of the data member
    void swapLo() {
        // low byte =[7:0], need to swap [7:4] and [3:0]
        unsigned short lowByte = bitset & 0xFF;        
        unsigned short upperL = (lowByte >> 4) & 0x0F;  
        unsigned short lowerL = lowByte & 0x0F;         
        

        unsigned short swappedLow = (lowerL << 4) | upperL;
        bitset = (bitset & 0xFF00) | swappedLow;  // no need to move.
    }

    // returns true if the value stored in the bitset is a power of 2
    bool isPow2() {
        return bitset != ZERO && (bitset & (bitset - 1)) == ZERO; // ZERO is not a power of two, so account for that
    }

    // sets to 0 only the last 1 in the bitset (lowest power of 2)
    void clearLast1() {
        bitset = bitset & (bitset - 1);
    }

    // returns the number of bits that are set to 1
    int count() {
       int count = 0; 

       for (int i = 0; i < 16; i++){
        unsigned short mask = 1 << i;
        if ((bitset & mask) != ZERO) {
            count++;
        }
       }
       return count;
    }

    // prints the binary representation of the data member
    void printBinary() {
        for (int i = 15; i >= 0; i--){
            unsigned short mask = 1 << i;
           cout << " " << ((bitset & mask) != ZERO ? "1" : "0");
        }

        cout << endl;
    }

    // prints the bits in decimal, hexadecimal, octal, and binary
    void print() {
        cout << "decimal: " << "[ " << dec << bitset << endl; // decimal
        cout << "hexadecimal: " << "0x" << hex << bitset << endl; // hexadecimal
        cout << "octal: " << "0" << oct << bitset << endl; // octal
        
        // print binary representation
        for (int i = 15; i >= 0; i--) {
            unsigned short mask = 1 << i;
            cout << ((bitset & mask) != ZERO ? "1" : "0");
        }
        
        cout << " ]" << endl;
        cout << dec;  // reset to decimal
    }
};

unsigned short id( unsigned short val ) {
    return val;
}

// testing
int main() {

    
    {
        Bitset bs(0xC3B0);
        cout << "getValue(): " << hex << bs.getValue() << endl;
    }

    {
        Bitset bs(0xC3B0);
        cout << "none(): " << (bs.none() ? "true" : "false") << endl;
    }

    {
        Bitset bs(0xC3B0);
        cout << "any(): " << (bs.any() ? "true" : "false") << endl;
    }

       
    {// test with 0xFFFF; not 0xC3B0
        Bitset bs(0xFFFF);
        cout << "all(): " << (bs.all() ? "true" : "false") << endl;
    }
    

    {
        Bitset bs(0xC3B0);
        cout << "Before flip(): ";
        bs.printBinary();
        bs.flip();
        cout << "After flip(): ";
        bs.printBinary();
    }

    {
        Bitset bs(0xC3B0);
        cout << "get(0): " << (bs.get(0) ? "1" : "0") << endl;
        cout << "get(4): " << (bs.get(4) ? "1" : "0") << endl;
        cout << "get(8): " << (bs.get(8) ? "1" : "0") << endl;
        cout << "get(15): " << (bs.get(15) ? "1" : "0") << endl;
    }

    {
        Bitset bs(0xC3B0);
        cout << "Before set(): ";
        bs.printBinary();
        bs.set();
        cout << "After set(): ";
        bs.printBinary();
    }

    {
        Bitset bs(0xC3B0);
        cout << "Before set(2): ";
        bs.printBinary();
        bs.set(2);
        cout << "After set(2): ";
        bs.printBinary();
    }

    {
        Bitset bs(0xC3B0);
        cout << "Before clear(): ";
        bs.printBinary();
        bs.clear();
        cout << "After clear(): ";
        bs.printBinary();
    }

    {
        Bitset bs(0xC3B0);
        cout << "Before clear(5): ";
        bs.printBinary();
        bs.clear(5);
        cout << "After clear(5): ";
        bs.printBinary();
    }


    {
        Bitset bs(0xC3B0);
        cout << "Before swap(): ";
        bs.printBinary();
        bs.swap();
        cout << "After swap(): ";
        bs.printBinary();
    }


    {
        Bitset bs(0xC3B0);
        cout << "Before swapHi(): ";
        bs.printBinary();
        bs.swapHi();
        cout << "After swapHi(): ";
        bs.printBinary();
    }


    {
        Bitset bs(0xC3B0);
        cout << "Before swapLo(): ";
        bs.printBinary();
        bs.swapLo();
        cout << "After swapLo(): ";
        bs.printBinary();
    }


    {
        // test with actual power of 2; not 0xC3B0
        Bitset bs(0x0100);
        cout << "isPow2() for 0x0100: " << (bs.isPow2() ? "true" : "false") << endl;
    }


    {
        Bitset bs(0xC3B0);
        cout << "Before clearLast1(): ";
        bs.printBinary();
        bs.clearLast1();
        cout << "After clearLast1(): ";
        bs.printBinary();
    }

    {
        Bitset bs(0xC3B0);
        cout << "count(): " << bs.count() << " bits set" << endl;
    }

    {
        Bitset bs(0xC3B0);
        cout << "printBinary(): ";
        bs.printBinary();
    }

    {
        Bitset bs(0xC3B0);
        cout << "print(): ";
        bs.print();
    }

    return 0;
}

