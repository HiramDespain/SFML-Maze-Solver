#ifndef ICONTAINER_H
#define ICONTAINER_H

template<typename T>
class IContainer{
public:
    /**
     * @brief remove and return the top element of the container
     * 
     * @return T 
     */
    virtual T pop() = 0;

    /**
     * @brief add a new element to the container
     * 
     */
    virtual void push (const T&) = 0;

    /**
     * @brief return the top element of the container
     * 
     * @return T 
     */
    virtual T top() const = 0;

    /**
     * @brief check if the container is empty
     * 
     * @return true 
     * @return false 
     */
    virtual bool isEmpty() const = 0;

    /**
     * @brief return the size of the container
     * 
     * @return int 
     */
    virtual int size() const = 0;

    /**
     * @brief return the element at the given index
     * 
     * @param i 
     * @return T 
     */
    virtual T at(int &i) const = 0;
};


#endif