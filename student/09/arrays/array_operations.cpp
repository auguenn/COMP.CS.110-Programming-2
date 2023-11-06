#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
  int greatest = *itemptr;
  while (size > 0)
    {
      if (greatest < *itemptr)
        {
          greatest = *itemptr;
        }
      size--;
      itemptr++;
    }
  return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
  int greatest = *itemptr;
  while (itemptr < endptr)
    {
      if (greatest < *itemptr)
        {
          greatest = *itemptr;
        }
      itemptr++;
    }
  return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
  while (itemptr < endptr)
    {
      *targetptr = *itemptr;
      itemptr++;
      targetptr++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
  rightptr--;
  int value;
  while (leftptr < rightptr)
    {
      value = *leftptr;
      *leftptr = *rightptr;
      *rightptr = value;
      rightptr--;
      leftptr++;
    }
}
