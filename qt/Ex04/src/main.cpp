#include <iostream>
#include <vector>
#include "threadlogfile.h"
#include "threadlogfilesafe.h"
using namespace std;


void logToFile(ThreadLogFile &log ,int value);
void logToFileSafe(ThreadLogFileSafe &log ,int value);
void ex4_3(void);
void ex4_4(void);

int main()
{
    ex4_3();
    ex4_4();
    return 0;
}

void logToFile(ThreadLogFile &log ,int value){
    log.print(std::this_thread::get_id(),value);

}

void logToFileSafe(ThreadLogFileSafe &log ,int value){
    log.print(std::this_thread::get_id(),value);
}

void ex4_3(void){
    ThreadLogFile log;
    logToFile(log,1);
    vector <thread> myThreads;
    myThreads.clear();
    for (unsigned int i=0 ; i < 10*thread::hardware_concurrency();i++){
        myThreads.push_back(thread(logToFile,std::ref(log),i));
     }
    for (auto &it :myThreads){ it.join();}
}

void ex4_4(void){
    ThreadLogFileSafe logEx4_4;
    vector <thread> myThreads;
    myThreads.clear();
    for (unsigned int i=0 ; i < 10*thread::hardware_concurrency();i++){
        myThreads.push_back(thread(logToFileSafe,std::ref(logEx4_4),i));
     }
    for (auto &it :myThreads){ it.join();}
}
