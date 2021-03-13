#ifndef _I_COLLECTION
#define _I_COLLECTION

namespace ds {
  class ICollection<T> {
  public:
    virtual bool isEmpty() = 0;
    virtual void add(T element) = 0;
    virtual int length() = 0;
    virtual bool isIn(T element) = 0;
    virtual bool remove(T element) = 0;
    virtual ICollection<T> collectionUnion(ICollection<T> collection) = 0;
    virtual ICollection<T> difference(ICollection<T> collection) = 0;
    virtual ICollection<T> intersection(ICollection<T> collection) = 0;
    virtual ~ICollection(){};
  }
}

#endif

