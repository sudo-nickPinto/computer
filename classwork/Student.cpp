#include <iostream>
using namespace std;

// no public (as in Java)
class Student {
    private: 
        // unasigned: just positive; sign doesn't come into play regarding bitshifts
                                //        unused  gpa   major   credits     year
                                //          ##  xxxxxx     x    xxxxx         xx
        unsigned short data;    // 2 bytes


    public: 
        Student() // or Student() : data(0); as soon as it initializes data member, it auto-puts value (doesn't need to execute two instructions)
        {        
            data = 0;
        }

        explicit Student( unsigned short year) : data(0) // go over explicit keyword
        {    
            setYear(year);

        }

        // how to get specific bits from our BIG data (2 bytes)
        int getYear() {
            unsigned short mask = 0b11;     // or '3', 0x3

            unsigned short year = data & mask;

            ++year;
            return year;
        }

        void setYear(unsigned short year){
            --year;
            // 1. clear the last two digits (xxxxxxxxxx -> xxxxxxx00)
            unsigned short mask = 0b11;     // 00..00011

            data = data & ~mask;

            // 2. replace the last two bits (no shift needed)
            data = data | year;
        }


        int getCredits(){
            unsigned short mask = 0b11111; // not correct (yet); wrong position... or 0x1F (1 plus 5 '1's)
            // shift to left by 2
            mask = mask << 2; // or mask<<=2

            unsigned short credits = mask & data;

            // must shift back. since we extracted 00...xxxxx00 (two additional zeroes)
            credits = credits >> 2;

            ++credits;
            return credits; 
        }

        void setCredits(unsigned short credits) {
            --credits;

            unsigned short mask = 0x1F;     // 000...011111
            mask = mask << 2;               // 000...01111100
                                            // 111...10000011 ~mask
            data = data & ~mask;            // xxx...x00000xx

            // 2. replace last two bits AND shift
            credits = credits << 2;          // 000...0xxxxx00 (go back as to why we shift them?)
            data = data | credits;
        }

        float getGPA(){

        }

        void setGPA(unsigned short gpa){

        }


}; // class must end with semi-colon

int main() {
    Student s1; // default constructor
    Student s2(2); // second constructor

    cout << "year " << s2.getYear() << endl;
    return 0;
}
