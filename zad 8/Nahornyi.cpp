#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

struct Point {
    double x;
    double y;
};

struct Rect {
    Point left;
    Point right;
};

std::vector<double> process(const Rect* rects, size_t sz, std::function<double(Rect)> f) {
    std::vector<double> results;
    results.reserve(sz);

    for (int i = 0; i < sz; i++) {
        results.push_back(f(rects[i]));
    }

    return results;
}

double calculateArea(Rect rect) {
    double width = rect.right.x - rect.left.x;
    double height = rect.left.y - rect.right.y;
    double sum = width * height;
    return sum;
}

double calculateDiagonalLength(Rect rect) {
    double width = rect.right.x - rect.left.x;
    double height = rect.left.y - rect.right.y;
    double sum = width * width + height * height;
    return std::sqrt(sum);
}

int main() {
    Rect rects[] = {
            {{0, 4}, {4, 1}},
            {{-6, 3}, {6, -2}},
            {{-7, 4}, {8, -4}}
    };

    std::vector<double> areas = process(rects, 3, calculateArea);
    std::vector<double> diagonalLengths = process(rects, 3, calculateDiagonalLength);


    for (double area : areas) {
        std::cout << area << " ";
    }
    std::cout << "(pola)" << std::endl;

    for (double length : diagonalLengths) {
        std::cout << length << " ";
    }
    std::cout << "(dlugosci przekatnych)" << std::endl;

}