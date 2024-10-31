#include <iostream>
#include <chrono>
#include <mutex>
using namespace std;

class Singleton {

public:

static Singleton* getInstance(const string& value);

Singleton(Singleton& other) = delete;

void operator=(const Singleton&) = delete;

string value() const {
    return value_;
}

protected:
    Singleton(const string value) : value_(value)
    {
    }
    ~Singleton() {}
    string value_;

 private:
	static Singleton* instance_;
	static mutex mutex_;

};

Singleton* Singleton::instance_{ nullptr };
mutex Singleton::mutex_;

Singleton* Singleton::getInstance(const string& value) {
    lock_guard<mutex> lock(mutex_);

    if (instance_ == nullptr) {
        instance_ = new Singleton(value);
    }

    return instance_;
}


void ThreadFoo() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("FOO");
    cout << singleton->value() << "\n";
}

void ThreadBar() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("BAR");
    cout << singleton->value() << "\n";
}

int main()
{
    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}