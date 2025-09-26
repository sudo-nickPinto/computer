#include <iostream>
#include <cassert>
#include <type_traits>
#include <iomanip>

template<typename T>
class Bitset {
    static_assert(std::is_unsigned<T>::value, "Bitset requires an unsigned integer type");

private:
    static constexpr int BITS = 8 * sizeof(T);
    static constexpr T ZERO = static_cast<T>(0);
    static constexpr T ONE  = static_cast<T>(1);
    static constexpr T ALL_ONES = static_cast<T>(~ZERO);

    T data;

public:
    explicit Bitset(T v) : data(v) {}

    T getValue() const { return data; }

    bool none() const { return data == ZERO; }
    bool any()  const { return data != ZERO; }
    bool all()  const { return data == ALL_ONES; }

    void flip() { data = static_cast<T>(~data); }

    bool get(int index) const {
        if (index < 0 || index >= BITS) return false;
        return (data & static_cast<T>(ONE << index)) != ZERO;
    }

    void set() { data = ALL_ONES; }
    void set(int index) {
        if (index < 0 || index >= BITS) return;
        data = static_cast<T>(data | static_cast<T>(ONE << index));
    }

    void clear() { data = ZERO; }
    void clear(int index) {
        if (index < 0 || index >= BITS) return;
        data = static_cast<T>(data & static_cast<T>(~(ONE << index)));
    }

    // generic byte-reverse (works for any width that is whole bytes)
    void swap() {
        const int bytes = sizeof(T);
        T out = ZERO;
        for (int i = 0; i < bytes; ++i) {
            T b = static_cast<T>((data >> (8 * i)) & static_cast<T>(0xFF));
            out |= static_cast<T>(b << (8 * (bytes - 1 - i)));
        }
        data = out;
    }

    // For 16-bit behavior only: perform swap of nibbles in high byte (no-op for other widths)
    void swapHi() {
        if (BITS != 16) return;
        T high = static_cast<T>((data >> 8) & static_cast<T>(0xFF));
        T upper = static_cast<T>((high >> 4) & static_cast<T>(0x0F));
        T lower = static_cast<T>(high & static_cast<T>(0x0F));
        T swappedHigh = static_cast<T>((lower << 4) | upper);
        data = static_cast<T>((data & static_cast<T>(0x00FF)) | (swappedHigh << 8));
    }

    void swapLo() {
        if (BITS != 16) return;
        T low = static_cast<T>(data & static_cast<T>(0xFF));
        T upper = static_cast<T>((low >> 4) & static_cast<T>(0x0F));
        T lower = static_cast<T>(low & static_cast<T>(0x0F));
        T swappedLow = static_cast<T>((lower << 4) | upper);
        data = static_cast<T>((data & static_cast<T>(0xFF00)) | swappedLow);
    }

    bool isPow2() const {
        return data != ZERO && (static_cast<T>(data & static_cast<T>(data - ONE))) == ZERO;
    }

    void clearLast1() { data = static_cast<T>(data & static_cast<T>(data - ONE)); }

    int count() const {
        int c = 0;
        for (int i = 0; i < BITS; ++i) {
            if ((data & static_cast<T>(ONE << i)) != ZERO) ++c;
        }
        return c;
    }

    void printBinary() const {
        for (int i = BITS - 1; i >= 0; --i) {
            std::cout << ((data & static_cast<T>(ONE << i)) != ZERO ? '1' : '0');
        }
        std::cout << '\n';
    }

    void print() const {
        // simple human-readable multi-line debug print (not used in assert tests)
        std::cout << "decimal: [ " << std::dec << static_cast<unsigned long long>(data) << " ]\n";
        std::cout << "hex: 0x" << std::hex << static_cast<unsigned long long>(data) << '\n';
        std::cout << "oct: 0"   << std::oct << static_cast<unsigned long long>(data) << '\n';
        std::cout << std::dec;
    }

    // Part I member operators
    bool operator==(const Bitset& other) const { 
        return data == other.data; }

    Bitset operator&(const Bitset& other) const { 
        return Bitset(static_cast<T>(data & other.data)); }

    Bitset operator~() const { 
        return Bitset(static_cast<T>(~data)); }

    Bitset operator<<(int positions) const {
        if (positions >= BITS || positions < 0) return Bitset(ZERO);
        return Bitset(static_cast<T>(static_cast<T>(data << positions) & ALL_ONES));
    }
    
    bool operator<(const Bitset& other) const { 
        return data < other.data; }

    // Part II member (assignment-style and prefix)
    Bitset& operator^=(const Bitset& other) {
        data = static_cast<T>(data ^ other.data);
        return *this;
    }

    Bitset& operator>>=(int positions) {
        if (positions >= BITS || positions < 0) { data = ZERO; return *this; }
        data = static_cast<T>(data >> positions);
        return *this;
    }

    Bitset& operator++() {
        data = static_cast<T>(data + ONE);
        return *this;
    }
};

// External operators (templated to match class)

template<typename T>
bool operator!=(const Bitset<T>& left, const Bitset<T>& right) {
    return !(left == right);
}

template<typename T>
Bitset<T> operator^(const Bitset<T>& left, const Bitset<T>& right) {
    return Bitset<T>( static_cast<T>( left.getValue() ^ right.getValue() ) );
}

template<typename T>
Bitset<T> operator|(const Bitset<T>& left, const Bitset<T>& right) {
    return ~(~left & ~right); // De Morgan: avoids direct '|' on Bitset which could recurse
}

template<typename T>
Bitset<T> operator>>(const Bitset<T>& b, int positions) {
    if (positions >= Bitset<T>::BITS || positions < 0) return Bitset<T>(static_cast<T>(0));
    return Bitset<T>( static_cast<T>( b.getValue() >> positions ) );
}

template<typename T>
bool operator>=(const Bitset<T>& left, const Bitset<T>& right) {
    return !(left < right);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Bitset<T>& bs) {
    T v = bs.getValue();
    os << '[' << std::dec << static_cast<unsigned long long>(v) << ", ";
    os << "0x" << std::hex << static_cast<unsigned long long>(v) << ", ";
    os << '0' << std::oct << static_cast<unsigned long long>(v) << ']';
    os << std::dec;
    return os;
}

// --- Tests using assert (no cout for grading) ---
int main() {
    { // 1-byte tests
        Bitset<unsigned char> b8(0x19);
        assert(b8.getValue() == static_cast<unsigned char>(0x19));
        assert(b8.count() == 3); // 0x19 = 00011001 has 3 bits set
        Bitset<unsigned char> b8copy = b8;
        b8.flip();
        assert(b8 != b8copy);
        b8 = Bitset<unsigned char>(0xFF);
        b8.clear(4);
        assert(b8.getValue() == static_cast<unsigned char>(0xEF));
    }

    { // 8-byte tests
        Bitset<unsigned long long> b64(0x0000'0000'0000'0001ULL);
        assert(b64.getValue() == 1ULL);
        ++b64;
        assert(b64 == Bitset<unsigned long long>(2ULL));
        b64 = Bitset<unsigned long long>(0xFFFF0000FFFF0000ULL);
        assert(b64.any());
        Bitset<unsigned long long> shifted = b64 >>= 16;
        assert(b64 == shifted);
    }

    return 0;
}