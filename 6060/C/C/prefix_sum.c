
/*
 int origArr[4] = {1, 2, 3, 4};
 
 The prefix sum for a sequence of numbers x0, x1, x2, ... is a second sequence of numbers y0, y1, y2, ..., where
 y0 = x0
 y1 = x0 + x1
 y2 = x0 + x1+ x2
 ...
 
 As an example, for the array above, the prefix sum is: 
 int prefix_sum[4] = {1, 3, 6, 10}
 
 Write the prefix sum code (sequential). Also mention its time complexity in Big O notation
 
 gcc -o prefix prefix_sum.c
 ./prefix
*/

#include <stdio.h>
#define SIZE 4

int main()
{
  int origArr[SIZE] = {1, 2, 3, 4};
  int prefix_sum[SIZE];  // Use this array for storing the prefix sum output. 
  
  int i;
  int sum = 0;
  
  for(i = 0; i<SIZE; i++)
  {
     sum = sum + origArr[i];  
  }
  printf("Sum is %d \n", sum);
  
  //Write your prefix sum code 
  
  // Your code start
  int s=0;
  for (i = 0; i < SIZE; i++)

  {
	  prefix_sum[i] = s + origArr[i];
	  s = prefix_sum[i];
	  printf(" %d ", s);
  }
  printf("\n");
  // Your code end
  
  // to verify the correctness
  for (i = 0; i < SIZE; i++)
  {
	  printf("%d ", prefix_sum[i]);
	  printf("\n");
  }
  return 0;
}