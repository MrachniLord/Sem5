#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Base {
protected:
    int* ptr;
public:
    Base() {
        ptr = new int(10);
    }
    virtual ~Base() {
        delete ptr;
    }
    virtual void print() {
        cout << "Base: " << *ptr << endl;
    }
};

class Derived : public Base {
private:
    string str;
public:
    Derived() {
        str = "Hello";
    }
    virtual ~Derived() {}
    virtual void print() {
        cout << "Derived: " << str << endl;
    }
};

class DB {
private:
    vector<Base*>* storage;
public:
    DB() {
        storage = new vector<Base*>;
    }
    ~DB() {
        for (auto i : *storage) {
            delete i;
        }
        delete storage;
    }
    void add(Base* obj) {
        storage->push_back(obj);
    }
    void copy(DB& other) {
        for (auto i : *storage) {
            if (dynamic_cast<Derived*>(i)) {
                Derived* d = new Derived(*dynamic_cast<Derived*>(i));
                other.add(d);
            }
            else {
                Base* b = new Base(*i);
                other.add(b);
            }
        }
    }
};

int main() {
    DB db1, db2;

    Base* b = new Base();
    Derived* d = new Derived();

    db1.add(b);
    db1.add(d);

    db1.copy(db2);

    delete b;
    delete d;

    return 0;
}
