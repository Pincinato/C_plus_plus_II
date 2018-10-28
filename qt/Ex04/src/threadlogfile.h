#ifndef THREADLOGFILE_H
#define THREADLOGFILE_H
#include <iostream>
#include <fstream>
#include <thread>

class ThreadLogFile
{
public:
    ThreadLogFile(){
        in.open("threadLog.txt",std::ifstream::in | std::ifstream::out);
    }
    ~ThreadLogFile(){
        if (in){in.close();}
    }
    void print(std::thread::id thread_id,int value){

        std::cout<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
        in<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
    }
private:
    std::fstream in;
};

#endif // THREADLOGFILE_H
