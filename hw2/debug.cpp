#include <iostream>
using namespace std;
int main() {
    const unsigned short ZERO = 0;
    cout << "ZERO = " << hex << ZERO << endl;
    cout << "~ZERO = " << hex << (~ZERO) << endl;
    cout << "0xFFFF = " << hex << 0xFFFF << endl;
    cout << "(~ZERO == 0xFFFF) = " << ((~ZERO) == 0xFFFF ? "true" : "false") << endl;
    return 0;
}
