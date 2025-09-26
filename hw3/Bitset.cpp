        #include <iostream>
        #include <string>
        #include <cassert>
        using namespace std;

        /*
        Nick Pinto
        Ivaylo Illinkin
        CS221 Assembly
        09/18/2025

        I affirm I have upheld the highest principles of honesty and integrity in my academic work and have not committed/witnessed 
        a violation of the honor code
        */

        // template (generic) version of Bitset class
        template <typename T> class Bitset {

        private:
        // const unsigned short ZERO = 0; // zero-constant (only use this)
        // unsigned short bitset;

        // had const before
        // need static const (looked up) 
        // when a class contains non-static data members, compiler deleted = operator
        // because those members can't be assigned
        static const int BITS = 8 * sizeof(T);
        static const T ZERO = T(0);
        static const T ONE = T(1);
        static const T ALL_ONES = T(~T(0));

        T data; // replaces 'bitset'

        public:
        // explicit constructor to initialize bitset with given value (why must we use explicit?)
        explicit Bitset(T value){
            data = value;
        }

        T getValue() const {
            return data;
        }


        bool none() const {
            return data == ZERO;
        }

        bool any() const {
            return data != ZERO;
        }

        bool all() const {
            return data == ALL_ONES;
        }




        // inverts the bits in the set (0s to 1s and 1s to 0s)
        void flip(){
            data = T(~data);
        }



        // returns true if the bit at the given index is set to 1
        bool get(int index) const {
            return (data & T(ONE << index)) != ZERO;
        }

        // sets all bits to 1
        void set() {
            data = ALL_ONES;
        }

        // sets the bit at the given index to 1
        void set(int index) {
            data = T(data | T(ONE << index)); // ONE << idx promotes to int; must T cast
        }

        // sets all bits to 0
        void clear() {
            data = ZERO;
        }

        // sets the bit at the given index to 0
        // make use of & operator: 0 & 0 = 0; 0 & 1 = 0

        void clear(int index) {
            // unsigned short mask = 1 << index;  // mask = 0000..01000 (1 is @ idx of mask)
            // mask = ~mask; // invert the mask: 1111...10111; makes original bit 0, and keeps every other bit with '& 1'
            // bitset = bitset & mask;
            data = T(data & T(~(ONE << index)));
        }

        // swap the values of the two different halves (two different bytes; [0,7] and [8,15]) of the data member
        void swap() {
            // // extract bytes
            // // mask is in lower byte pos ONLY
            // unsigned short mask = 0xFF; // 0000 0000 1111 1111
            // // higher byte
            // // move higher byte to lower byte pos
            // unsigned short hByte = bitset >> 8;
            // hByte = hByte & mask;

            // // lower byte
            // // no need to move as mask is already in lower byte pos
            // unsigned short lByte = bitset & mask;

            // // combine bytes (lower then higher)
            // // now move lByte to higher byte pos (hByte already in lower byte pos)
            // bitset = (lByte << 8) | hByte;

            // split into two equal halves
            int half = BITS / 2;

            // lower mask (should be set to all 1s)
            T maskHalf = T(T(ONE) << half) - ONE;

            // extract lower and ipper halves
            T lower = data & maskHalf;
            T upper = (data >> half) & maskHalf;
            data = T((lower << half) | upper);


        }

        // swaps the two halves in the high byte of the data member
        // couldnt figure out for the life of me. Test cases failing. Cannot do generic!
        void swapHi() {
            // // high byte = [15:8], need to swap [15:12] and [11:8]
            // unsigned short highByte = (bitset >> 8) & 0xFF;  // extract high byte
            // unsigned short upperH = (highByte >> 4) & 0x0F;  // extract upper 4 bits of high byte
            // unsigned short lowerH = highByte & 0x0F;         // extract lower 4 bits of high byte
            
            // // swap the two and put back in high byte position
            // unsigned short swappedHigh = (lowerH << 4) | upperH;
            // bitset = (bitset & 0x00FF) | (swappedHigh << 8);  

            if (BITS < 8) {return;} // if one byte, cannot swap 1 byte with another (non-existent) byte

            // start with  extracting high byte
            int half = BITS/2;
            int quarter = BITS/4;

            T maskHalf = T(T(ONE) << half) - ONE;
            T maskQuarter = T(T(ONE) << half) - ONE;

            // high-half byte
            T highHalf = (data >> half) & maskHalf;
            
            // extract upper and lower from highHalf
            T upper = T(highHalf >> quarter) & maskQuarter;
            T lower = highHalf & maskQuarter;

            // swap two and put into high byte position
            T swappedHigh = T(lower << quarter) | upper;

            // move swappedHigh back into high byte position
            data = T(data & T(maskHalf)) | swappedHigh << half;

        }

        // swaps the two halves in the low byte of the data member
        // couldnt figure out for the life of me. Cannot do generic!
        void swapLo() {
            // // low byte =[7:0], need to swap [7:4] and [3:0]
            // unsigned short lowByte = bitset & 0xFF;        
            // unsigned short upperL = (lowByte >> 4) & 0x0F;  
            // unsigned short lowerL = lowByte & 0x0F;         
            

            // unsigned short swappedLow = (lowerL << 4) | upperL;
            // bitset = (bitset & 0xFF00) | swappedLow;  // no need to move.

            if (BITS < 8) {return;}

            int half = BITS/2;
            int quarter = BITS/4;

            T maskHalf = T(T(ONE) << half) - ONE;
            T maskQuarter = T(T(ONE) << half) - ONE;

            T lowByte = data & maskHalf;
            T upper = T(lowByte >> quarter) & maskQuarter; 
            T lower = lowByte & maskQuarter;

            T swappedLow = T((lower << quarter) | upper);

            // ~maskHalf refers to 0xFF00 in 16-bit terms from comments above
            data = T((data & T(~maskHalf)) | swappedLow);


        }

        // returns true if the value stored in the bitset is a power of 2
        bool isPow2() const {
            return data != ZERO && T(data & T(data - ONE)) == ZERO; 
        }

        // sets to 0 only the last 1 in the bitset (lowest power of 2)
        void clearLast1() {
            data = T(data & T(data - ONE));
        }

        // returns the number of bits that are set to 1
        int count() const {
            int count = 0; 

            for (int i = 0; i < BITS; i++){
                if ((data & T(ONE << i)) != ZERO) {
                    count++;
                }
            }
            return count;
        }

        // prints the binary representation of the data member
        // for output / debugging purposes. Should put const
        void printBinary()  const {
            for (int i = BITS - 1; i >= 0; i--){
                cout << " " << ((data & T(ONE << i)) != ZERO ? "1" : "0");
            }

            cout << endl;
        }

        // prints the bits in decimal, hexadecimal, octal, and binary
        // for output / debugging purposes. Should put const
        void print() const {
            cout << "decimal: " << "[ " << dec << data << endl; // decimal
            cout << "hexadecimal: " << "0x" << hex << data << endl; // hexadecimal
            cout << "octal: " << "0" << oct << data << endl; // octal
            

            // SAID IN SPECIFICATION TO NOT DO BINARY REPRESENTATION!
            // // print binary representation
            // for (int i = 15; i >= 0; i--) {
            //     unsigned short mask = 1 << i;
            //     cout << ((bitset & mask) != ZERO ? "1" : "0");
            // }
            
            cout << " ]" << endl;
            cout << dec;  // reset to decimal
        }


        // operator overloading part 1:

        // member methods (within the class)
        bool operator==(const Bitset& other) const {
            return data == other.data;
        }


        Bitset operator&(const Bitset& other) const {
            return Bitset(T(data & other.data));
        }

        Bitset operator~() const {
            return Bitset(T(~data));
        }

        Bitset operator<<(int positions) const {
            return Bitset(T(data << positions));
        }

        bool operator<(const Bitset& other) const {
            return data < other.data;
        }


        // no const methods here and below (where applicable). THIS is modified (as per specification)
        Bitset operator^=(const Bitset& other) {
            data = T(data ^ other.data);
            return *this;
        }

        Bitset operator>>=(int positions){
        data = T(data >> positions);
            return *this;
        }

        Bitset operator++(){
        data = T(data + 1);
            return *this;
        }


        };


        // external function (outside the class)
        // can we use method call (of operator==) within the external methods

        template<typename T>
        bool operator!=(const Bitset<T>& left, const Bitset<T>& right) {
            return !(left.getValue() == right.getValue());
        }

        // no De Morgan's Law -- simple
        // commented out as it won't compile (infinite recursion)- but asked in specification
        // template<typename T>
        // Bitset<T> operator|(const Bitset<T>& left, const Bitset<T>& right){
        //     return Bitset<T>(left | right);
        // }

        // De Morgan's Law: A|B = ~(~A & ~B))
        template<typename T>
        Bitset<T> operator|(const Bitset<T>& left, const Bitset<T>& right){
            return Bitset<T>(~(~left & ~right));
        }
        template<typename T>
        Bitset<T> operator^(const Bitset<T>& left, const Bitset<T>& right){
            return Bitset<T>(T(left.getValue() ^ right.getValue()));
        }

        // template<typename T>
        // Bitset<T> operator~(const Bitset<T>& bs) {
        //     return Bitset<T>(~bs.getValue());
        // }
        template<typename T>
        Bitset<T> operator>>(const Bitset<T>& bs, int positions){
            return Bitset<T>(bs.getValue() >> positions);
        }
        template<typename T>
        bool operator>=(const Bitset<T>& left, const Bitset<T>& right){
            return !(left.getValue() < right.getValue());
        }

        // left operand is ostream (cout), not Bitset, thus it cannot be a member method of Bitset class. 
        // member requires bitset to be left operand (e.g bs << cout) which is wrong ordering.

        // ostream& returns the same (not copied) stream. 
        // ostream& os is not const since we are modifying it directly, unlike the bitset in this method.


        // do you want this multi-lined? or one line like your format
        template<typename T>
        ostream& operator<<(ostream& os, const Bitset<T>& bs){
            T value = bs.getValue(); // ostream<<bs would be infinitely recursive

            os << "decimal: " << "[ " << dec << value << endl; // decimal
            os << "hexadecimal: " << "0x" << hex << value << endl; // hexadecimal
            os << "octal: " << "0" << oct << value << endl; // octal

            os << " ]" << endl;
            os << dec;  // reset to decimal

            return os; // return this stream, not copy. 
        }

        unsigned short id( unsigned short val ) {
            return val;
        }


    int main() {
        // 1 byte
        Bitset<unsigned char> bitset(0x00);
        
        // none()
        bitset = Bitset<unsigned char>(0x00);
        assert( bitset.none() == true );
        bitset = Bitset<unsigned char>(0xC3);
        assert( bitset.none() == false );
        
        // any()
        bitset = Bitset<unsigned char>(0xC3);
        assert( bitset.any() == true );
        bitset = Bitset<unsigned char>(0x00);
        assert( bitset.any() == false );
        
        // all()
        bitset = Bitset<unsigned char>(0xFF);
        assert( bitset.all() == true );
        bitset = Bitset<unsigned char>(0xC3);
        assert( bitset.all() == false );
        
        // get(i)
        bitset = Bitset<unsigned char>(0xC3);           // 1100 0011
        assert( bitset.get(0) == true );
        assert( bitset.get(1) == true );
        assert( bitset.get(2) == false );
        
        // count()
        bitset = Bitset<unsigned char>(0xC3);
        assert( bitset.count() == 4 );
        
        // isPow2()
        bitset = Bitset<unsigned char>(0x80);
        assert( bitset.isPow2() == true );
        bitset = Bitset<unsigned char>(0xC3);
        assert( bitset.isPow2() == false );
        
        // set()  
        bitset = Bitset<unsigned char>(0xC3);
        bitset.set();
        assert( bitset == Bitset<unsigned char>(0xFF) );
        
        // set(i) 
        bitset = Bitset<unsigned char>(0x00);
        bitset.set(5);
        assert( bitset == Bitset<unsigned char>(0x20) );
        
        // clear() 
        bitset = Bitset<unsigned char>(0xC3);
        bitset.clear();
        assert( bitset == Bitset<unsigned char>(0x00) );
        
        // clear(i) 
        bitset = Bitset<unsigned char>(0xC3);           // 1100 0011
        bitset.clear(0);                                // 1100 0010
        assert( bitset == Bitset<unsigned char>(0xC2) );
        
        // flip() 
        bitset = Bitset<unsigned char>(0xC3);           // 1100 0011
        bitset.flip();                                  // 0011 1100
        assert( bitset == Bitset<unsigned char>(0x3C) );
        
        // clearLast1() 
        bitset = Bitset<unsigned char>(0x34);           // 0011 0100
        bitset.clearLast1();                            // 0011 0000
        assert( bitset == Bitset<unsigned char>(0x30) );
        
        // swap() 
        bitset = Bitset<unsigned char>(0xC3);           // 1100 0011
        bitset.swap();                                  // 0011 1100
        assert( bitset == Bitset<unsigned char>(0x3C) );
        
        // swapHi() 
        bitset = Bitset<unsigned char>(0xC3);
        bitset.swapHi();
        assert( bitset == Bitset<unsigned char>(0x3C) );
        
        // swapLo() 
        bitset = Bitset<unsigned char>(0xC3);
        bitset.swapLo();
        assert( bitset == Bitset<unsigned char>(0x3C) );

        // 8 byte

        Bitset<unsigned long long> bitset64(0x00);
        
        // none / any / all
        bitset64 = Bitset<unsigned long long>(0x0000000000000000);
        assert( bitset64.none() == true );
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        assert( bitset64.any() == true );
        bitset64 = Bitset<unsigned long long>(0xFFFFFFFFFFFFFFFF);
        assert( bitset64.all() == true );
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        assert( bitset64.all() == false );
        
        // get(i)  (0xC3B0C3B0 bytes: C3 B0 C3 B0)
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        assert( bitset64.get(5) == true );   // bit 5 in low byte B0 (1011 0000)
        assert( bitset64.get(4) == false );  // bit 4 in low byte

        
        // count()
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);  // C3=4 ones, B0=3 ones repeated => 14
        assert( bitset64.count() == 14 );
        
        // isPow2()
        bitset64 = Bitset<unsigned long long>(0x0000000000000100);
        assert( bitset64.isPow2() == true );
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        assert( bitset64.isPow2() == false );
        
        // set() 
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        bitset64.set();
        assert( bitset64 == Bitset<unsigned long long>(0xFFFFFFFFFFFFFFFF) );
        
        // clear() 
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        bitset64.clear();
        assert( bitset64 == Bitset<unsigned long long>(0x0000000000000000) );
        
        // set(index) 
        bitset64 = Bitset<unsigned long long>(0x0000000000000000);
        bitset64.set(40);
        assert( bitset64 == Bitset<unsigned long long>( (unsigned long long)1 << 40 ) );
        
        // clear(index) 
        bitset64 = Bitset<unsigned long long>(0x00000000000000FF);
        bitset64.clear(7);
        assert( bitset64 == Bitset<unsigned long long>(0x000000000000007F) );
        
        // flip()
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        bitset64.flip();
        assert( bitset64 == Bitset<unsigned long long>(0xFFFFFFFF3C4F3C4F) );
        
        // clearLast1() 
        bitset64 = Bitset<unsigned long long>(0xC3B0C3B0);
        bitset64.clearLast1();
        assert( bitset64 == Bitset<unsigned long long>(0xC3B0C3A0) );
        
        // swap()
        bitset64 = Bitset<unsigned long long>(0x12345678ABCDEF01);
        bitset64.swap();
        assert( bitset64 == Bitset<unsigned long long>(0xABCDEF0112345678) );

        // swapLo()
        bitset64 = Bitset<unsigned long long>(0x00000000000000AB);
        bitset64.swapLo();
        assert( bitset64 == Bitset<unsigned long long>(0x00000000000000BA) );

        // swapHi()
        bitset64 = Bitset<unsigned long long>(0x4D000000000000AB);
        bitset64.swapHi();
        assert( bitset64 == Bitset<unsigned long long>(0xD4000000000000AB) );

        return 0;
    }

