#ifndef STACK_HPP
#define STACK_HPP

#include "IContainer.hpp"
#include <deque>

template<typename T>
class Stack : public IContainer<T>{
private:
    //using a deque to store the data
    std::deque<T> _data;
public:
    /**
     * @brief returns the back element of the stack and removes it
     * 
     * @return * T 
    */
    T pop() override;

    /**
     * @brief pushes to the back of the stack
     * 
     * @param value 
     */
    void push(const T& value) override;

    /**
     * @brief returns the back element
     * 
     * @return T 
     */
    T top() const override;
    bool isEmpty() const override;
    int size() const override;
    T at(int &i) const override;
};

template<typename T>
T Stack<T>::at(int &i) const {
    return _data.at(i);
}

template<typename T>
int Stack<T>::size() const {
    return _data.size();
}

template<typename T>
bool Stack<T>::isEmpty()const {
    return  _data.empty();
}

template<typename T>
T Stack<T>::pop() {
    T topData = top();
    _data.pop_back();
    return topData;
}

template<typename T>
void Stack<T>::push(const T& value) {
    _data.push_back(value);
}

template<typename T>
T Stack<T>::top() const{
    return _data.back();
}

#endif