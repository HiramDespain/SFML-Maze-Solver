#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "IContainer.hpp"
#include <deque>

template<typename T>
class Queue : public IContainer<T>{
private:
    //using a deque to store the data
    std::deque<T> _data;
public:
    /**
     * @brief returns the front element of the queue and removes it
     * 
     * @return * T 
     */
    T pop() override;

    /**
     * @brief adds and element to the back of the queue
     * 
     * @param value 
     */
    void push(const T& value) override;

    /**
     * @brief returns the front element of the queue
     * 
     * @return T 
     */
    T top() const override;
    bool isEmpty() const override;
    int size() const override;
    T at(int &i) const override;
};

template<typename T>
T Queue<T>::at(int &i) const {
    return _data.at(i);
}

template<typename T>
int Queue<T>::size() const {
    return _data.size();
}


template<typename T>
bool Queue<T>::isEmpty() const {
    return  _data.empty();
}

template<typename T>
T Queue<T>::pop() {
    T topData = top();
    _data.pop_front();
    return topData;
}

template<typename T>
void Queue<T>::push(const T& value) {
    _data.push_back(value);
}

template<typename T>
T Queue<T>::top() const{
    return _data.front();
}

#endif