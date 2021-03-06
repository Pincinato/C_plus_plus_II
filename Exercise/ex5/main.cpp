// Exercise 05 - Producer-Consumer Pattern
#include <iostream>
#include <thread>
#include <sstream>
#include "dataqueue.h"

using namespace std;
using namespace std::chrono_literals;

DataQueue<int> q{5};
bool finished{false};

void pcout(stringstream& msg)
{
    mutex coutMu;
    lock_guard<mutex> coutLock{coutMu};
    cout << msg.str() << endl;
}

void produce(size_t nbrItems)
{
    for(size_t count{0}; count < nbrItems; ++count)
    {
        std::this_thread::sleep_for(60ms); // Producing time
        q.add(count);
        stringstream ss; ss << "Producing --> item " <<   count;
        pcout(ss);
    }

    finished = true;
    stringstream ss; ss << " --- Producer done ----";
    pcout(ss);
}

void consume()
{
    while (!q.isEmpty() || !finished)
    {
        std::this_thread::sleep_for(90ms); // Consuming time
        stringstream ss; ss << "item " << q.get() << " --> comsumed";
        pcout(ss);
    }
}


int main()
{
    // Producer
    thread pThread{produce, 25};

    // Consumer
    thread cThread{consume};

    pThread.join();
    finished = true;
    cThread.join();

    cout << "Finished!"<< endl;
    return 0;
}
