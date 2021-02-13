#pragma once
#include <iostream>

using namespace std;

template<class T>
class TListElem
{
protected:
  T data;
  TListElem<T>* next;
  TListElem<T>* prev;
public:
  TListElem(T _data);
  ~TListElem();

  T GetData();
  TListElem<T>* GetNext();
  TListElem<T>* GetPrev();

  void SetData(T _data);
  void SetNext(TListElem<T>* _next);
  void SetPrev(TListElem<T>* _prev);

  template <class T1>
  friend ostream& operator << (ostream& ostr, const TListElem<T1>& A);
  template <class T1>
  friend istream& operator >> (istream& istr, const TListElem<T1>& A);
};

template <class T>
class TList
{
protected:
  TListElem<T>* root;
  TListElem<T>* end;
  int count;

public:
  TList();
  TList(const TList<T>& _v);
  ~TList();

  TList<T>& operator =(const TList<T>& _v);

  void InsFirst(T d);
  void InsLast(T d);
  void Ins(TListElem<T>* e, T d);

  TListElem<T>* GetFirst();
  TListElem<T>* GetLast();

  void DelFirst();
  void DelLast();
  void Del(TListElem<T>* e);

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TList<T1>& A);
  template <class T1>
  friend istream& operator >> (istream& istr, TList<T1>& A);

  bool IsFull() const;
  bool IsEmpty() const;
  int GetCount();
};

template<class T1>
ostream& operator<<(ostream& ostr, const TListElem<T1>& A)
{
  ostr << A.data;
}

template<class T1>
istream& operator>>(istream& istr, const TListElem<T1>& A)
{
  istr >> A.data;
}

template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1>& A)
{
  TListElem<T1>* i = A.root;

  while (i != NULL)
  {
    ostr << *i << endl;
    i = i->GetNext();
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1>& A) {
  int count;
  istr >> count;
  for (int i = 0; i < count; i++)
  {
    T1 d;
    istr >> d;
    A.InsLast(d);
  }
  return istr;
}

template<class T>
TList<T>::TList()
{
  root = NULL;
  end = NULL;
  count = 0;
}

template <class T>
TList<T>::TList(const TList<T>& _v)
{
  count = _v.count;

  TListElem<T>* i = _v.root;
  TListElem<T>* j = this->root;
  TListElem<T>* p = NULL;

  while (i != NULL)
  {
    j = new TListElem<T>(*i);
    j->SetNext(0);
    if (p != NULL)
    {
      p->SetNext(j);
      j->SetPrev(p);
    }

    p = j;

    if (root == NULL)
      root = j;

    i = i->next;
  }
}

template <class T>
TList<T>::~TList()
{
  if (this->root != NULL)
  {
    TListElem<T>* i = this->root;
    TListElem<T>* p = NULL;

    while (i != NULL)
    {
      p = i;
      i = i->GetNext();
      delete p;
    }

    this->root = NULL;
    this->end = NULL;
    count = 0;
  }
}

template <class T>
TList<T>& TList<T>::operator =(const TList<T>& _v)
{
  if (this == &_v)
    return *this;

  if (this->root != NULL)
  {
    TListElem<T>* i = this->root;
    TListElem<T>* p = NULL;

    while (i != NULL)
    {
      p = i;
      i = i->GetNext();
      delete p;
    }

    this->root = NULL;
    this->end = NULL;
    count = 0;
  }

  count = _v.count;

  TListElem<T>* i = _v.root;
  TListElem<T>* j = this->root;
  TListElem<T>* p = NULL;

  while (i != NULL)
  {
    j = new TListElem<T>(*i);
    j->SetNext(0);
    if (p != NULL)
    {
      p->SetNext(j);
      j->SetPrev(p);
    }

    p = j;

    if (root == NULL) 
      root = j;

    i = i->GetNext();
  }

  return *this;

}

template<class T>
void TList<T>::InsFirst(T d)
{
  if (this->IsFull())
    throw "stack overflow";

  TListElem<T>* temp = new TListElem<T>(d);
  temp->SetNext(root);
  root = temp; 
  if (end == NULL)
    end = temp;
  count++;
}

template<class T>
void TList<T>::InsLast(T d)
{
  if (this->IsFull())
    throw "stack overflow";

  if (end == 0)
    end = new TListElem<T>(d);
  else
  {
    TListElem<T>* temp = new TListElem<T>(d); 
    temp->SetNext(end);
    end = temp;
  }
  if (root == NULL)
    root = end;
  count++;
}

template<class T>
void TList<T>::Ins(TListElem<T>* e, T d)
{
  
  TListElem<T>* temp = new TListElem<T>(d);
  temp->SetNext(e->GetNext()); 
  temp->SetPrev(e); 
  e->GetNext()->SetPrev(temp); 
  e->SetNext(temp);
  count++;
}

template<class T>
TListElem<T>* TList<T>::GetFirst()
{
  return root;
}

template<class T>
TListElem<T>* TList<T>::GetLast()
{
  return end;
}

template<class T>
void TList<T>::DelFirst()
{

  TListElem<T>* i = root;
  root = root->GetNext();
  count--;
  delete i;
}

template<class T>
void TList<T>::DelLast()
{
  TListElem<T>* i = end;
  end = end->GetPrev();
  count--;
  delete i;
}

template<class T>
void TList<T>::Del(TListElem<T>* e)
{
  e->GetPrev()->SetNext(e->GetNext()); 
  e->GetNext()->SetPrev(e->GetPrev());
  count--;
  delete e;
}


template<class T>
bool TList<T>::IsFull() const
{
  try
  {
    TListElem<T>* temp = new TListElem<T>(1);
    delete temp;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

template<class T>
bool TList<T>::IsEmpty() const
{
  return (count == 0);
}

template<class T>
int TList<T>::GetCount()
{
  return count;
}

template<class T>
TListElem<T>::TListElem(T _data)
{
  data = _data;
  next = NULL;
  prev = NULL;
}

template<class T>
TListElem<T>::~TListElem()
{
  next = NULL;
  prev = NULL;
}

template<class T>
T TListElem<T>::GetData()
{
  return data;
}

template<class T>
TListElem<T>* TListElem<T>::GetNext()
{
  return next;
}

template<class T>
TListElem<T>* TListElem<T>::GetPrev()
{
  return prev;
}

template<class T>
void TListElem<T>::SetData(T _data)
{
  data = _data;
}

template<class T>
void TListElem<T>::SetNext(TListElem<T>* _next)
{
  next = _next;
}

template<class T>
void TListElem<T>::SetPrev(TListElem<T>* _prev)
{
  prev = _prev;
}