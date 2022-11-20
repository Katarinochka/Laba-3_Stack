#ifndef __STACK_H__
#define __STACK_H__
#include <string>

const int MaxStackSize = 100;

template <class TType>
class TStack
{
private:
  TType* pMem;
  int size;
  int top;
  TStack(const TStack&) = delete; // ������ �� ����������� �����
  void operator=(const TStack&) = delete; // ������ �� ������������ �����

public:
  TStack(int _size = MaxStackSize) // ����������� �� ���������
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw std::string("Incorrect Stack Size");
    pMem = new TType[size];
  }
  ~TStack() // ����������
  {
    delete[] pMem;
  }
  bool empty() { return top == -1; } // �������� ������ �� ����
  bool full() { return top == size - 1; } // �������� �������� �� ����
  void push(const TType obj) // ������� �������� � ������� �����
  {
    if (full())
      throw std::string("Stack Is Full");
    pMem[++top] = obj;
  }
  TType pop() // ��������� �������� �������� �������� � ���������
  {
    if (empty())
      throw std::string("Stack Is Emty");
    return pMem[top--];
  }
  TType tos() // ��������� �������� �������� �������� ��� �������� // 
  {
    if (empty())
      throw std::string("Stack Is Emty");
    return pMem[top];
  }
};
#endif