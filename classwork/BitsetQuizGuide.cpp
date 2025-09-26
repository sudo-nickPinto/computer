/*
 * BITSET QUIZ PRACTICE GUIDE
 * CS 221 - Computer Organization and Assembly Language Programming
 * 
 * This file contains quiz-style problems and solutions to help you master
 * the Bitset class methods and bitwise operations.
 */

#include <iostream>
#include <cassert>
using namespace std;

/*
 * QUIZ STRATEGY GUIDE:
 * 
 * 1. Know your bit positions: 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 * 2. Remember: rightmost bit is index 0, leftmost is index 15
 * 3. Hex to binary conversion is crucial
 * 4. Understand masking patterns for each operation
 */

// === QUIZ PROBLEM PATTERNS ===

void quizProblem1() {
    cout << "\n=== QUIZ PROBLEM 1: Basic State Analysis ===" << endl;
    cout << "Given: Bitset bits(0x8080)" << endl;
    cout << "Binary: 1000000010000000" << endl;
    cout << "Predict the outcomes:" << endl;
    
    // Create the bitset
    // Bitset bits(0x8080);  // You would have this in your quiz
    
    cout << "bits.none() = ?" << endl;
    cout << "Answer: false (has 1s at positions 7 and 15)" << endl;
    
    cout << "bits.any() = ?" << endl;  
    cout << "Answer: true (has at least one 1)" << endl;
    
    cout << "bits.all() = ?" << endl;
    cout << "Answer: false (not all bits are 1)" << endl;
    
    cout << "bits.count() = ?" << endl;
    cout << "Answer: 2 (exactly two 1s)" << endl;
    
    cout << "bits.get(7) = ?" << endl;
    cout << "Answer: true (bit 7 is 1)" << endl;
    
    cout << "bits.get(6) = ?" << endl;
    cout << "Answer: false (bit 6 is 0)" << endl;
    
    cout << "bits.isPow2() = ?" << endl;
    cout << "Answer: false (0x8080 is not a power of 2)" << endl;
}

void quizProblem2() {
    cout << "\n=== QUIZ PROBLEM 2: Operations Sequence ===" << endl;
    cout << "Given: Bitset bits(0x000F)" << endl;
    cout << "Binary: 0000000000001111" << endl;
    cout << "Apply operations in sequence:" << endl;
    
    unsigned short value = 0x000F;
    cout << "1. Initial value: 0x" << hex << value << dec << endl;
    
    // Operation 1: set(8)
    cout << "2. After bits.set(8):" << endl;
    value |= (1 << 8);  // Set bit 8
    cout << "   Result: 0x" << hex << value << dec << " (added bit 8)" << endl;
    
    // Operation 2: clear(2)  
    cout << "3. After bits.clear(2):" << endl;
    value &= ~(1 << 2);  // Clear bit 2
    cout << "   Result: 0x" << hex << value << dec << " (cleared bit 2)" << endl;
    
    // Operation 3: flip()
    cout << "4. After bits.flip():" << endl;
    value ^= 0xFFFF;  // Flip all bits
    cout << "   Result: 0x" << hex << value << dec << " (all bits flipped)" << endl;
    
    cout << "Final binary: ";
    for (int i = 15; i >= 0; i--) {
        cout << ((value >> i) & 1);
    }
    cout << endl;
}

void quizProblem3() {
    cout << "\n=== QUIZ PROBLEM 3: Swap Operations ===" << endl;
    cout << "Given: Bitset bits(0xABCD)" << endl;
    cout << "Binary: 1010101111001101" << endl;
    cout << "Upper byte: AB (10101011), Lower byte: CD (11001101)" << endl;
    
    unsigned short original = 0xABCD;
    
    // swap() - swap upper and lower bytes
    cout << "1. After bits.swap():" << endl;
    unsigned short swapped = ((original & 0xFF) << 8) | ((original & 0xFF00) >> 8);
    cout << "   Result: 0x" << hex << swapped << dec << " (bytes swapped: CD AB)" << endl;
    
    // swapHi() - swap halves of upper byte
    cout << "2. After bits.swapHi() on original:" << endl;
    unsigned short upperByte = (original & 0xFF00) >> 8;  // Get AB
    unsigned short swappedUpper = ((upperByte & 0x0F) << 4) | ((upperByte & 0xF0) >> 4);  // A<->B
    unsigned short result1 = (original & 0x00FF) | (swappedUpper << 8);
    cout << "   Result: 0x" << hex << result1 << dec << " (upper nibbles swapped: BA CD)" << endl;
    
    // swapLo() - swap halves of lower byte  
    cout << "3. After bits.swapLo() on original:" << endl;
    unsigned short lowerByte = original & 0x00FF;  // Get CD
    unsigned short swappedLower = ((lowerByte & 0x0F) << 4) | ((lowerByte & 0xF0) >> 4);  // C<->D
    unsigned short result2 = (original & 0xFF00) | swappedLower;
    cout << "   Result: 0x" << hex << result2 << dec << " (lower nibbles swapped: AB DC)" << endl;
}

void quizProblem4() {
    cout << "\n=== QUIZ PROBLEM 4: Power of 2 and clearLast1 ===" << endl;
    
    unsigned short testValues[] = {0x0008, 0x0010, 0x0018, 0x0100, 0x0101};
    const char* descriptions[] = {"8", "16", "24", "256", "257"};
    
    for (int i = 0; i < 5; i++) {
        cout << "\nValue: " << descriptions[i] << " (0x" << hex << testValues[i] << dec << ")" << endl;
        
        // Binary representation
        cout << "Binary: ";
        for (int bit = 15; bit >= 0; bit--) {
            cout << ((testValues[i] >> bit) & 1);
            if (bit % 4 == 0 && bit > 0) cout << " ";
        }
        cout << endl;
        
        // isPow2 test
        bool isPower = (testValues[i] != 0) && ((testValues[i] & (testValues[i] - 1)) == 0);
        cout << "isPow2(): " << (isPower ? "true" : "false") << endl;
        
        // clearLast1 result
        unsigned short cleared = testValues[i] & (testValues[i] - 1);
        cout << "After clearLast1(): 0x" << hex << cleared << dec << endl;
        
        // Explanation for clearLast1
        if (testValues[i] != 0) {
            cout << "Explanation: " << testValues[i] << " & " << (testValues[i] - 1) 
                 << " = " << cleared << endl;
        }
    }
}

void quizProblem5() {
    cout << "\n=== QUIZ PROBLEM 5: Complex Bit Manipulation ===" << endl;
    cout << "Given: Bitset bits(0x5A3C)" << endl;
    cout << "Binary: 0101101000111100" << endl;
    
    unsigned short value = 0x5A3C;
    
    // Count 1s manually for verification
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if ((value >> i) & 1) count++;
    }
    cout << "Number of 1-bits: " << count << endl;
    
    // Test specific bit positions
    int testPositions[] = {0, 2, 3, 4, 5, 9, 11, 12, 14, 15};
    cout << "Bit positions that are 1: ";
    for (int i = 0; i < 10; i++) {
        if ((value >> testPositions[i]) & 1) {
            cout << testPositions[i] << " ";
        }
    }
    cout << endl;
    
    // After setting bit 1
    cout << "After set(1): 0x" << hex << (value | (1 << 1)) << dec << endl;
    
    // After clearing bit 5
    cout << "After clear(5): 0x" << hex << (value & ~(1 << 5)) << dec << endl;
}

// COMPREHENSIVE QUIZ SIMULATION
void simulateQuiz() {
    cout << "\n" << string(50, '=') << endl;
    cout << "BITSET QUIZ SIMULATION" << endl;
    cout << string(50, '=') << endl;
    
    cout << "\nINSTRUCTIONS:" << endl;
    cout << "- Read each problem carefully" << endl;
    cout << "- Convert hex to binary when needed" << endl;
    cout << "- Think through each operation step by step" << endl;
    cout << "- Remember bit indexing starts at 0 from the right" << endl;
    
    quizProblem1();
    quizProblem2();
    quizProblem3();
    quizProblem4();
    quizProblem5();
    
    cout << "\n" << string(50, '=') << endl;
    cout << "QUICK REFERENCE FOR QUIZ:" << endl;
    cout << string(50, '=') << endl;
    
    cout << "\nKEY PATTERNS:" << endl;
    cout << "• none(): data == 0" << endl;
    cout << "• any(): data != 0" << endl;
    cout << "• all(): data == 0xFFFF (all 16 bits set)" << endl;
    cout << "• get(i): (data & (1 << i)) != 0" << endl;
    cout << "• set(i): data |= (1 << i)" << endl;
    cout << "• clear(i): data &= ~(1 << i)" << endl;
    cout << "• isPow2(): (data != 0) && ((data & (data-1)) == 0)" << endl;
    cout << "• clearLast1(): data &= (data - 1)" << endl;
    
    cout << "\nHEX TO BINARY QUICK REFERENCE:" << endl;
    cout << "0x0=0000, 0x1=0001, 0x2=0010, 0x3=0011" << endl;
    cout << "0x4=0100, 0x5=0101, 0x6=0110, 0x7=0111" << endl;
    cout << "0x8=1000, 0x9=1001, 0xA=1010, 0xB=1011" << endl;
    cout << "0xC=1100, 0xD=1101, 0xE=1110, 0xF=1111" << endl;
    
    cout << "\nPOWERS OF 2 TO MEMORIZE:" << endl;
    cout << "2^0=1, 2^1=2, 2^2=4, 2^3=8, 2^4=16" << endl;
    cout << "2^5=32, 2^6=64, 2^7=128, 2^8=256" << endl;
    cout << "2^9=512, 2^10=1024, 2^11=2048, 2^12=4096" << endl;
}

int main() {
    simulateQuiz();
    return 0;
}
