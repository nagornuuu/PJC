#include <iostream>
#include <cstring>
class Person {
    char* name;
    friend class Couple;
public:
    explicit Person(const char* n);
    Person(const Person& os);
    Person& operator=(const Person& os);
    ~Person();
    friend std::ostream& operator << (std::ostream& str, const Person& os);
};

Person::Person(const char* n) {
    name = new char[std::strlen(n) + 1];
    std::strcpy(name, n);
}

Person::Person(const Person& os) {
    name = new char[std::strlen(os.name) + 1];
    std::strcpy(name, os.name);
}

Person& Person::operator=(const Person& os) {
    if (this != &os) {
        delete[] name;
        name = new char[std::strlen(os.name) + 1];
        std::strcpy(name, os.name);
    }
    return *this;
}

Person::~Person() {
    std::cout << "DEL " << name << std::endl;
    delete[] name;
}

std::ostream& operator<<(std::ostream& str, const Person& os) {
    return str << os.name;
}

class Couple {
    Person *wife, *husband;
public:
    Couple(const Person& she, const Person& he);
    Couple(const Couple& other);
    Couple& operator = (const Couple& other);
    ~Couple();
    friend std::ostream& operator << (std::ostream& str, const Couple& p);
};

Couple::Couple(const Person& she, const Person& he) {
    wife = new Person(she);
    husband = new Person(he);
}

Couple::Couple(const Couple& other) {
    wife = new Person(*other.wife);
    husband = new Person(*other.husband);
}

Couple& Couple::operator=(const Couple& other) {
    if (this != &other) {
        delete wife;
        delete husband;
        wife = new Person(*other.wife);
        husband = new Person(*other.husband);
    }
    return *this;
}

Couple::~Couple() {
    delete wife;
    delete husband;
}

std::ostream& operator<<(std::ostream& str, const Couple& p) {
    return str << "Couple: he " << *(p.husband) << ", she " << *(p.wife);
}

int main(void) {
    using std::cout; using std::endl;
    Person *pjohn = new Person("John"),
    *pjane = new Person("Jane");
    Person mary("Mary"), mark("Mark");
    Couple *pcouple1 = new Couple(mary, *pjohn);
    Couple couple2(*pjane,mark);
    delete pjohn;
    delete pjane;
    cout << *pcouple1 << endl;
    cout << couple2 << endl;
    couple2 = *pcouple1;
    delete pcouple1;
    cout << couple2 << endl;
}