#define BITSET_UNIT_TEST
#include "Bitset.cpp"
#include <cassert>
#include <sstream>
#include <string>
#include <iostream>

int main() {
    // Type aliases
    using U8 = unsigned char;
    using U16 = unsigned short;
    using U64 = unsigned long long;

    // --- Basic constructor / getValue
    Bitset<U16> a(U16(0xC3B0));
    assert(a.getValue() == U16(0xC3B0));

    // --- none / any / all
    Bitset<U16> z(U16(0x0000));
    assert(z.none());
    assert(!z.any());
    Bitset<U16> all(U16(~U16(0)));
    assert(all.all());

    // --- flip
    Bitset<U16> b(U16(0xC3B0));
    b.flip();
    assert(b == Bitset<U16>(U16(~U16(0xC3B0))));

    // --- set / clear
    Bitset<U16> s(U16(0));
    s.set();
    assert(s.all());
    s.clear();
    assert(s.none());

    // --- set(index) and get(index)
    Bitset<U16> t(U16(0));
    t.set(2);
    assert(t.get(2));
    assert(t == Bitset<U16>(U16(1u << 2)));

    // --- clear(index)
    Bitset<U16> c(U16(0xFFFF));
    c.clear(5);
    assert(!c.get(5));

    // --- isPow2
    Bitset<U16> p(U16(0x0100));
    assert(p.isPow2());
    Bitset<U16> notp(U16(0xC3B0));
    assert(!notp.isPow2());

    // --- clearLast1
    Bitset<U16> cl(U16(0b101100)); // 0x2C
    cl.clearLast1(); // clears lowest 1 -> 0b101000
    assert(cl == Bitset<U16>(U16(0b101000)));

    // --- count
    Bitset<U16> cnt(U16(0b101011));
    assert(cnt.count() == 4);

    // --- swap, swapHi, swapLo behavior (sanity checks)
    Bitset<U16> sw(U16(0x1234));
    sw.swap();
    // swapping lower and upper bytes of 0x1234 -> 0x3412
    assert(sw == Bitset<U16>(U16(0x3412)));

    Bitset<U16> shi(U16(0xABCD));
    shi.swapHi();
    // high byte of 0xABCD is 0xAB -> nibbles A and B -> swapped -> 0xBA -> new value 0xBACD
    assert(shi == Bitset<U16>(U16(0xBACD)));

    Bitset<U16> slo(U16(0xABCD));
    slo.swapLo();
    // low byte 0xCD -> swap nibbles C and D -> 0xDC -> new value 0xABDC
    assert(slo == Bitset<U16>(U16(0xABDC)));

    // --- bitwise operators: & | ^ ~ (external/member)
    Bitset<U16> x1(U16(0xF0F0));
    Bitset<U16> x2(U16(0x0FF0));
    assert((x1 & x2) == Bitset<U16>(U16(0x00F0)));
    assert((x1 | x2) == Bitset<U16>(U16(0xFFF0)));
    assert((x1 ^ x2) == Bitset<U16>(U16(0xF000)));
    assert((~x1) == Bitset<U16>(U16(~U16(0xF0F0))));

    // --- compound ^= and >>=
    Bitset<U16> ca(U16(0xAAAA));
    Bitset<U16> cb(U16(0x5555));
    Bitset<U16> cret = (ca ^= cb);
    assert(ca == Bitset<U16>(U16(0xFFFF)));
    assert(cret == Bitset<U16>(U16(0xFFFF)));

    Bitset<U16> sh(U16(0x00FF));
    Bitset<U16> shret = (sh >>= 4);
    assert(sh == Bitset<U16>(U16(0x000F)));
    assert(shret == Bitset<U16>(U16(0x000F)));

    // --- prefix ++
    Bitset<U16> inc(U16(24));
    ++inc;
    assert(inc == Bitset<U16>(U16(25)));
    ++(++inc);
    assert(inc == Bitset<U16>(U16(27)));

    // --- comparisons < >= != ==
    Bitset<U16> small(U16(1));
    Bitset<U16> big(U16(2));
    assert(small < big);
    assert(big >= small);
    assert(small != big);

    // --- shifts: << (member) and >> (external)
    Bitset<U16> ls(U16(0x0001));
    Bitset<U16> lsr = ls << 4;
    assert(lsr == Bitset<U16>(U16(0x0010)));
    Bitset<U16> rs(U16(0x1000));
    Bitset<U16> rsr = rs >> 8;
    assert(rsr == Bitset<U16>(U16(0x0010)));

    // --- ostream operator (just ensure it compiles and returns stream)
    {
        std::ostringstream oss;
        oss << Bitset<U16>(U16(0x1A));
        std::string out = oss.str();
        assert(out.find("decimal:") != std::string::npos);
    }

    // --- tests for 1-byte and 8-byte widths
    Bitset<U8> b1(U8(0x5A));
    assert(b1.getValue() == U8(0x5A));
    assert(b1.count() == 4);

    Bitset<U64> b8(U64(0x0123456789ABCDEFULL));
    assert(b8.getValue() == U64(0x0123456789ABCDEFULL));
    // check a few bits
    assert(b8.get(0) == true); // LSB is 1
    assert(b8.get(63) == false);

    // quick stress: flip twice restores
    Bitset<U64> stress(U64(0xDEADBEEFDEADBEEFULL));
    auto copy = stress;
    stress.flip();
    stress.flip();
    assert(stress == copy);

    return 0;
}
