#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>
#include <future>

using std::cout;
using std::shared_ptr;
using std::mutex;

// Lock_guard
mutex mtx;

// Keeps track of the number of references
class ReferenceCounter
{
public:
    ReferenceCounter() : _count(0) {}

    void add_ref()
    {
        _count.fetch_add(1, std::memory_order_relaxed);
    }
    int rm_ref()
    {
        return _count.fetch_sub(1, std::memory_order_acq_rel);
    }

private:
    std::atomic<int> _count;
};

// Smart pointers
template<class T> class Log_ptr
{
public:
    // Constructors
    Log_ptr()
    {
        _rc = new ReferenceCounter();
        _rc->add_ref();
    };
    Log_ptr(T* i) : _i(i)
    {
        cout << "\n" << " omistajuus siiretty " << &_i;

        _rc = new ReferenceCounter();
        _rc->add_ref();
    };
    Log_ptr(const Log_ptr<T>& lp) : _i(lp._i), _rc(lp._rc)
    {
        cout << "\n" << " omistajuus siiretty " << &_i;

        _rc->add_ref();
    };
    // Deconstructor
    ~Log_ptr()
    {
        cout << "\n" << " olio tuhottu " << &_i;

        RemoveRef();
    };
    // Operators
    T* operator ->() {
        std::lock_guard<mutex> lock(mtx);
        cout << "\n" << " operator-> " << &_i;
        return _i;
    };
    T& operator*() {
        std::lock_guard<mutex> lock(mtx);
        cout << "\n" << " operator* " << &_i;
        return *_i;
    };
    Log_ptr<T>& operator = (const Log_ptr<T>& lp)
    {
        if (this != &lp)
        {
            RemoveRef();
            _i = lp._i;
            _rc = lp._rc;
            _rc->add_ref();
        }
        return *this;
    }

private:
    T* _i;
    ReferenceCounter* _rc;

    void RemoveRef() const
    {
        if (_rc->rm_ref() <= 0)
        {
            delete _i;
            if (_rc != nullptr)
                delete _rc;
        }
    }
};

class Simple {
public:
    Simple()
    {
        cout << "\nI exist";
    }
    ~Simple()
    {
        cout << "\nI die";
    }

    void tervehdi() const
    {
        cout << "\nEllow!";
    }
};

shared_ptr<Simple> use_simple(shared_ptr<Simple>& p)
{
    shared_ptr<Simple> p1(new Simple);
    shared_ptr<Simple> p2(new Simple);
    cout << "\nIn function";
    return p1;
}

int main()
{
    // shared_ptr test
    shared_ptr<Simple> p1(new Simple);
    p1 = use_simple(p1);

    // Smart pointer
    Log_ptr<Simple> juttu(new Simple);
    // Use as pointer
    juttu->tervehdi();
    (*juttu).tervehdi();

    cout << "\nEnd of program";
    return 0;
}