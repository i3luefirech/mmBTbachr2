//
// Created by root on 11/13/18.
//

#ifndef CODE_MMTHREADSAFEQUEUE_H
#define CODE_MMTHREADSAFEQUEUE_H

class mmThreadsafeQueue : public std::queue<int> {
private:
    pthread_mutex_t mtx;

public:
    mmThreadsafeQueue();

    bool empty();

    void push(const int &val);

    void pop(const int &val);

    int front(void);

    bool emptyFrontPop(int*);
};

#endif //CODE_MMTHREADSAFEQUEUE_H
