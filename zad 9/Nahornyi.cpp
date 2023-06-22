#include <iostream>

class Segment {
    double A, B;
public:
    Segment(double A, double B) : A(A), B(B) { }

    friend Segment operator+(double d, const Segment& seg) {
        return {seg.A + d, seg.B + d};
    }

    Segment operator+(double d) const {
        return {A + d, B + d};
    }

    friend Segment operator+(const Segment& seg1, const Segment& seg2) {
        return {std::min(seg1.A, seg2.A), std::max(seg1.B, seg2.B)};
    }

    Segment operator-(double d) const {
        return {A - d, B - d};
    }

    Segment operator*(double d) const {
        return {d * A, d * B};
    }

    friend Segment operator*(double d, const Segment& seg) {
        return {d * seg.A, d * seg.B};
    }

    Segment operator/(double d) const {
        return {A / d, B / d};
    }

    bool operator()(double d) const {
        return d >= A && d <= B;
    }

    friend std::ostream& operator<<(std::ostream& str, Segment& segment);
};

std::ostream& operator<<(std::ostream& str, Segment& segment) {
    return str << "[" << segment.A << "," << segment.B << "]";
}

int main() {
    using std::cout; using std::endl;
    Segment seg{2, 3}, s = 1 + 2 * ((seg - 2) / 2 + seg) / 3;
    cout << s << endl << std::boolalpha;
    for (double x = 0.5; x < 4; x += 1)
        cout << "x=" << x << ": " << s(x) << endl;
}