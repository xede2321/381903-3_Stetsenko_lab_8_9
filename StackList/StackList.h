#pragma once
#include "../List/List.h"
#include <iostream>

using namespace std;

template <class T>
class TStackList
{
protected:
  TList<T> list;
 
public:
  TStackList();
  TStackList(const TStackList<T>& _v);
  ~TStackList();

  TStackList<T>& operator =(const TStackList<T>& _v);

  void Put(T d);
  T Get(); 

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStackList<T1>& A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStackList<T1>& A);

  int IsEmpty() const; 
  int IsFull() const;
  int GetCount();
};

template<class T>
TStackList<T>::TStackList()
{
}

template<class T>
TStackList<T>::TStackList(const TStackList<T>& _v)
{
  list = _v.list;
}

template<class T>
TStackList<T>::~TStackList()
{
}

template<class T>
TStackList<T>& TStackList<T>::operator=(const TStackList<T>& _v)
{
  if (this == &_v)
    return *this;

  list = _v.list;

  return *this;
}

template<class T>
void TStackList<T>::Put(T d)
{
  list.InsFirst(d);
}

template<class T>
T TStackList<T>::Get()
{
  if (list.IsEmpty())
    throw "stack is empty";

  T temp = list.GetFirst()->GetData();
  list.DelFirst();

  return temp;
}

template<class T>
int TStackList<T>::IsEmpty() const
{
  return list.IsEmpty();
}

template<class T>
int TStackList<T>::IsFull() const
{
  return list.IsFull();
}

template<class T>
int TStackList<T>::GetCount()
{
  return list.GetCount();
}

template<class T1>
ostream& operator<<(ostream& ostr, const TStackList<T1>& A)
{
  return ostr << A.list;
}

template<class T1>
istream& operator>>(istream& istr, TStackList<T1>& A)
{
  return istr >> A.list;
}