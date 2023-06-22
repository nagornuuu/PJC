#include <iostream>
#include <iomanip> // formatting
void showPeriod(int period) {
    //0xF = 15, 0x1F = 31, 0x7F = 127,
    int fromy = (period >> 25) + 2000;          //bits 25 positions to the right
    int fromm = (period >> 21) & 0xF;           //bits 21 positions to the right, (&) is applied to the result of the right shift operation
    int fromd = (period >> 16) & 0x1F;          //bits 16 positions to the right, (&) is applied to the result of the right shift operation
    int toy = ((period >> 9) & 0x7F) + 2000;    //bits 9 positions to the right, (&) is applied to the result of the right shift operation
    int tom = (period >> 5) & 0xF;              //bits 5 positions to the right, (&) is applied to the result of the right shift operation
    int tod = period & 0x1F;

    //std::setw is a manipulator that sets the width of the next element that is printed to a stream object with the << operator
    //std::setfill behaves as if member fill were called with c as argument on the stream on which it is inserted as a manipulator

    std::cout << std::setfill('0') << std::setw(4) << fromy << "/"
              << std::setw(2) << fromm << "/"
              << std::setw(2) << fromd << "-"
              << std::setw(4) << toy << "/"
              << std::setw(2) << tom << "/"
              << std::setw(2) << tod << std::endl;
}
int pack(int fromy, int fromm, int fromd, int toy, int tom, int tod) {
    //range [0, 127]
    int y1 = fromy - 2000;
    int y2 = toy - 2000;

    //dates in a 32-bit integer
    int packed = ((y1 << 25) | (fromm << 21) | (fromd << 16) | (y2 << 9) | (tom << 5) | tod);
    return packed;
}

int main() {
    // y m d y m d
    int period = pack(2000, 2, 3, 2127, 11, 29);
    showPeriod(period);
}
