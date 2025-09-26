#include <iostream>
#include <cassert>
using namespace std;

class Bitset {
private:
    unsigned short data;
    const unsigned short ZERO = 0;

public:
    // Constructor
    explicit Bitset(unsigned short theBits) : data(theBits) {}
    
    // Basic getter for testing
    unsigned short getValue() { return data; }
    
    // Print methods
    void print() {
        cout << hex << data << endl;
        cout << dec;
    }
    
    // QUIZ EXAMPLE METHODS - Study these patterns!
    
    // 1. NONE - all bits are 0
    bool none() {
        return data == ZERO;
    }
    
    // 2. ANY - at least one bit is 1
    bool any() {
        return data != ZERO;
    }
    
    // 3. ALL - all bits are 1 (16 ones for unsigned short)
    bool all() {
        return data == ~ZERO;  // All bits set to 1
    }
    
    // 4. FLIP - invert all bits without using ~data
    void flip() {
        data = data ^ ~ZERO;  // XOR with all 1s flips all bits
    }
    
    // 5. GET - check if bit at index is set
    bool get(int index) {
        unsigned short mask = 1;
        mask = mask << index;
        return (data & mask) != ZERO;
    }
    
    // 6. SET ALL - set all bits to 1
    void set() {
        data = ~ZERO;
    }
    
    // 7. SET INDEX - set specific bit to 1
    void set(int index) {
        unsigned short mask = 1;
        mask = mask << index;
        data = data | mask;
    }
    
    // 8. CLEAR ALL - set all bits to 0
    void clear() {
        data = data & ZERO;  // ANDing with 0 clears everything
    }
    
    // 9. CLEAR INDEX - set specific bit to 0
    void clear(int index) {
        unsigned short mask = 1;
        mask = mask << index;
        data = data & ~mask;
    }
    
    // 10. SWAP - swap upper and lower bytes
    void swap() {
        unsigned short upperByte = data >> 8;           // Get upper 8 bits
        unsigned short lowerByte = data << 8;           // Move lower 8 bits up
        data = upperByte | lowerByte;
    }
    
    // 11. SWAP HI - swap halves of upper byte
    void swapHi() {
        unsigned short upperByte = data & 0xFF00;       // Extract upper byte
        unsigned short upperNibbles = upperByte >> 8;   // Get the byte
        unsigned short swapped = ((upperNibbles & 0x0F) << 4) | ((upperNibbles & 0xF0) >> 4);
        data = (data & 0x00FF) | (swapped << 8);        // Combine with lower byte
    }
    
    // 12. SWAP LO - swap halves of lower byte  
    void swapLo() {
        unsigned short lowerByte = data & 0x00FF;       // Extract lower byte
        unsigned short swapped = ((lowerByte & 0x0F) << 4) | ((lowerByte & 0xF0) >> 4);
        data = (data & 0xFF00) | swapped;               // Combine with upper byte
    }
    
    // 13. IS POWER OF 2 - check if value is power of 2
    bool isPow2() {
        return (data != ZERO) && ((data & (data - 1)) == ZERO);
    }
    
    // 14. CLEAR LAST 1 - clear rightmost set bit
    void clearLast1() {
        data = data & (data - 1);
    }
    
    // 15. COUNT - count number of 1 bits (loop required)
    int count() {
        int counter = 0;
        unsigned short mask = 1;
        for (int i = 0; i < 16; i++) {
            if ((data & mask) != ZERO) {
                counter++;
            }
            mask = mask << 1;
        }
        return counter;
    }
};

// Helper function for testing
unsigned short id(unsigned short value) {
    return value;
}

int main() {
    cout << "=== BITSET QUIZ EXAMPLES ===" << endl;
    
    // EXAMPLE 1: Basic operations on 0xA5C3 (1010010111000011)
    cout << "\n--- Example 1: Working with 0xA5C3 ---" << endl;
    Bitset bits1(0xA5C3);
    cout << "Original value: 0x"; bits1.print();
    
    cout << "none(): " << bits1.none() << " (should be 0 - has 1s)" << endl;
    cout << "any(): " << bits1.any() << " (should be 1 - has 1s)" << endl;
    cout << "all(): " << bits1.all() << " (should be 0 - not all 1s)" << endl;
    cout << "get(0): " << bits1.get(0) << " (bit 0 = 1)" << endl;
    cout << "get(2): " << bits1.get(2) << " (bit 2 = 0)" << endl;
    cout << "count(): " << bits1.count() << " 1-bits" << endl;
    cout << "isPow2(): " << bits1.isPow2() << " (not a power of 2)" << endl;
    
    // EXAMPLE 2: Testing set/clear operations
    cout << "\n--- Example 2: Set/Clear Operations ---" << endl;
    Bitset bits2(0x0000);
    cout << "Starting with 0x"; bits2.print();
    
    bits2.set(3);  // Set bit 3
    cout << "After set(3): 0x"; bits2.print(); // Should be 0x8
    
    bits2.set(7);  // Set bit 7  
    cout << "After set(7): 0x"; bits2.print(); // Should be 0x88
    
    bits2.clear(3); // Clear bit 3
    cout << "After clear(3): 0x"; bits2.print(); // Should be 0x80
    
    // EXAMPLE 3: Flip operations
    cout << "\n--- Example 3: Flip Operations ---" << endl;
    Bitset bits3(0x00FF); // Lower byte all 1s
    cout << "Original: 0x"; bits3.print();
    
    bits3.flip();
    cout << "After flip(): 0x"; bits3.print(); // Should be 0xFF00
    
    // EXAMPLE 4: Swap operations
    cout << "\n--- Example 4: Swap Operations ---" << endl;
    Bitset bits4(0x1234);
    cout << "Original: 0x"; bits4.print();
    
    Bitset swapTest(0x1234);
    swapTest.swap();
    cout << "After swap(): 0x"; swapTest.print(); // Should be 0x3412
    
    Bitset swapHiTest(0x1234);
    swapHiTest.swapHi();
    cout << "After swapHi(): 0x"; swapHiTest.print(); // Should be 0x2134
    
    Bitset swapLoTest(0x1234);
    swapLoTest.swapLo();
    cout << "After swapLo(): 0x"; swapLoTest.print(); // Should be 0x1243
    
    // EXAMPLE 5: Power of 2 tests
    cout << "\n--- Example 5: Power of 2 Tests ---" << endl;
    unsigned short powerValues[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    unsigned short nonPowerValues[] = {3, 5, 6, 7, 9, 10, 15, 17, 33};
    
    cout << "Powers of 2:" << endl;
    for (int i = 0; i < 11; i++) {
        Bitset test(powerValues[i]);
        cout << "  " << powerValues[i] << ": " << test.isPow2() << endl;
    }
    
    cout << "Non-powers of 2:" << endl;
    for (int i = 0; i < 9; i++) {
        Bitset test(nonPowerValues[i]);
        cout << "  " << nonPowerValues[i] << ": " << test.isPow2() << endl;
    }
    
    // EXAMPLE 6: clearLast1 operation
    cout << "\n--- Example 6: clearLast1 Operations ---" << endl;
    unsigned short testValues[] = {0b1010, 0b1100, 0b1111, 0b1000};
    for (int i = 0; i < 4; i++) {
        Bitset test(testValues[i]);
        cout << "Before clearLast1(): " << testValues[i] << " (binary)";
        test.clearLast1();
        cout << " -> After: " << test.getValue() << endl;
    }
    
    return 0;
}
