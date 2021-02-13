#include <iostream>
#include "../StackList/StackList.h"
#include "../QueueList/QueueList.h"

int main()
{
  TStackList<int> s;
  TQueueList<int> q;

  s.Put(10);
  s.Put(11);
  q.Put(10);
  q.Put(11);

  std::cout << s.Get() << "\n";
  std::cout << q.Get() << "\n";

  return 0;
}