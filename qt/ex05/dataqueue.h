#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include <iostream>
#include <deque>
#include <condition_variable>

template <typename T>
class DataQueue
{
public:
    DataQueue(uint16_t size=1000):max_size(size){}

    void add(T elementToAdd){
        if(!isFull()){
            std::lock_guard<std::mutex> Locker(dequeLocker);
            myDeque.push_front(elementToAdd);
            std::lock_guard<std::mutex> full_locker(fullLocker);
            if ( myDeque.size() >= max_size){full=true;}
        }
        else{
            std::unique_lock<std::mutex>Locker_get{dequeLocker};
            consumer_notification.wait(Locker_get,[this]{return !isFull();});
            myDeque.push_front(elementToAdd);
            std::lock_guard<std::mutex> full_locker(fullLocker);
            if ( myDeque.size() >= max_size){full=true;}
        }
        consumer_notification.notify_one();
    }

    T get(){
        T returnValue;
        if(isEmpty()){
            std::unique_lock<std::mutex>Locker_get{dequeLocker};
            produce_notification.wait(Locker_get,[this]{return !(isEmpty());});
            returnValue = myDeque.back();
            myDeque.pop_back();
            std::lock_guard<std::mutex> full_locker(fullLocker);
            if ( myDeque.size() < max_size){full=false;}
        }
        else {
            std::lock_guard<std::mutex>Locker(dequeLocker);
            returnValue = myDeque.back();
            myDeque.pop_back();
            std::lock_guard<std::mutex> full_locker(fullLocker);
            if ( myDeque.size() < max_size){full=false;}
        }
        consumer_notification.notify_one();
        return returnValue;
    }

    bool isFull(){
        std::lock_guard<std::mutex>Locker(fullLocker);
        return full;
    }

    bool isEmpty(){
        std::lock_guard<std::mutex>Locker(dequeLocker);
        return myDeque.empty();
    }

private:
    uint16_t max_size;
    bool full = false;
    std::deque<T> myDeque;
    std::mutex dequeLocker;
    std::mutex fullLocker;
    std::condition_variable produce_notification;
    std::condition_variable consumer_notification;
};
#endif // DATAQUEUE_H
