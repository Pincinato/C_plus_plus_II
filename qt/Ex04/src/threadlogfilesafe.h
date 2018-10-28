#ifndef THREADLOGFILESAFE_H
#define THREADLOGFILESAFE_H
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

class ThreadLogFileSafe
{
public:
    ThreadLogFileSafe(){
        in.open("threadLogSafe.txt",std::ifstream::in | std::ifstream::out);
    }
    ~ThreadLogFileSafe(){
        if (in){in.close();}
    }
    void print(std::thread::id thread_id,int value){

        std::call_once(header,[this](){in<<" HEADER "<<std::endl<<"------------"<<std::endl;});
        std::lock_guard<std::mutex> guard(mutexLogToFile);
        std::cout<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
        in<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
    }
private:
    std::fstream in;
    std::once_flag header;
    std::mutex mutexLogToFile;
};
#endif // THREADLOGFILESAFE_H
