//
// Created by root on 11/13/18.
//

#include <queue>
#include <pthread.h>
#include "mmThreadsafeQueue.h"

mmThreadsafeQueue::mmThreadsafeQueue() {
    pthread_mutex_init (&this->mtx, NULL);
}

void mmThreadsafeQueue::push (const int& val){
    pthread_mutex_lock (&this->mtx);
    queue::push(val);
    pthread_mutex_unlock (&this->mtx);
}

void mmThreadsafeQueue::pop (const int& val){
    pthread_mutex_lock (&this->mtx);
    queue::pop();
    pthread_mutex_unlock (&this->mtx);
}

int mmThreadsafeQueue::front (void){
    pthread_mutex_lock (&this->mtx);
    int ret = queue::front();
    pthread_mutex_unlock (&this->mtx);
    return ret;
}

bool mmThreadsafeQueue::emptyFrontPop(int * res){
    pthread_mutex_lock (&this->mtx);
    bool ret = 0;
    if(queue::empty()){
        *res = 0;
    } else {
        *res = queue::front();
        queue::pop();
    }
    pthread_mutex_unlock (&this->mtx);
    return ret;
}


