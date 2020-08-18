/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

/* Constructor for the Deque class */
template <class T>
Deque<T>::Deque(){
    /**
     * @todo Your code here! 
     */
     k1 = 0;
     k2 = -1;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    /**
     * @todo Your code here! 
     */
    if (k2 + 1 == (int)data.size()) {
        data.push_back(newItem);
    } else {
        data[k2 + 1] = newItem;
    }
    k2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The leftmost item of the Deque.
 */
template <class T>
T Deque<T>::popL() {
    /**
     * @todo Your code here! 
     */
    T ret_val = data[k1];
    k1++;

    //resizing
    int size = k2 - k1 + 1;
    if (size < k1) {
        for (int i = 0; i < size; i++) {
            data[i] = data[k1 + i];
        }
        data.resize(size);
        k1 = 0;
        k2 = size - 1;
    }
    return ret_val;
}

/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The rightmost item of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    /**
     * @todo Your code here! 
     */
    T ret_val = data[k2];
    k2--;


    //resizing
    int size = k2 - k1 + 1;
    if (size < k1) {
        for (int i = 0; i < size; i++) {
            data[i] = data[k1 + i];
        }
        data.resize(size);
        k1 = 0;
        k2 = size - 1;
    }
    return ret_val;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the left of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */
    return data[k1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
    */
    return data[k2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const {
    /**
     * @todo Your code here! 
     */
    return (k2 - k1 < 0);
}
