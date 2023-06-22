#include <iostream>
enum Banks {PKO, BGZ, BRE, BPH};
struct Account {
    Banks bank;
    int balance;
};
struct Person {
    char name[20];
    Account account;
};
struct Couple {
    Person he;
    Person she;
};

const Couple* bestClient(const Couple* cpls, int size, Banks bank) {
    const Couple *result = nullptr;
    int maxBalance = INT_MIN;

    for (int i = 0; i < size; i++) {
        const Couple& cpl = cpls[i];
        bool bankMatch = (cpl.he.account.bank == bank || cpl.she.account.bank == bank);
        bool balance = (cpl.he.account.balance + cpl.she.account.balance > maxBalance);
        if (bankMatch && balance) {
            result = &cpl;
            maxBalance = cpl.he.account.balance + cpl.she.account.balance;
        }
    }

    return result;
}
int main() {
    using std::cout; using std::endl;
    Couple cpls[] = {
            {{"Johnny", {PKO, 1200}}, {"Mary", {BGZ, 1400}}},
            {{"Peter",  {BGZ, 1400}}, {"Suzy", {BRE, -1500}}},
            {{"Kevin",  {PKO, 1600}}, {"Katy", {BPH, 1500}}},
            {{"Kenny",  {BPH, 200}},  {"Lucy", {BRE, -201}}}
    };
    const Couple* p = bestClient(cpls, 4, BRE);
    if (p)
        cout << p->he.name << " and " << p->she.name
             << ": " << p->he.account.balance +
                        p->she.account.balance << endl;
    else
        cout << "No such couple...\n";
}

