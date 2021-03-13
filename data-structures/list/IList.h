#ifndef _I_LIST
#define _I_LIST

namespace ds {
  class IList<T>::ICollection<T> {
  public:
    virtual void push(T element) = 0;
    virtual T pop() = 0;
    virtual T seekFirst() = 0;
    virtual T seekLast() = 0;
    virtual T dequeue() = 0;

    virtual void insert(T element, int index) = 0;
    virtual void remove(int index) = 0;
    virtual T get(int index) = 0;
    
    virtual void sort() = 0;
    
    virtual IList<T> copy() = 0;
    virtual ~IList(){} 
  }
}

#endif
