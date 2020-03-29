//====================================
// Algorithm & Data Structure Analysis
// Student: Vandit Jyotindra Gajjar
// Student ID: a1779153
// Semester: 1
// Year: 2020
// Assignment: 1
//=====================================

//Importing libraries.

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

/* Printing out the vector - Method: outVector
   Parameter: int vector value.*/

void outVector(vector<int> v)
{
  for (int i = 0;i < v.size();i++)
  {
    cout << v[i];
  }
}

/* School method for Addition - Method: schoolAddition
   Parameter: int vector I1, I2 and base value.
   Return: Sum of two int vector I1 and I2.*/

vector<int> schoolAddition(vector<int> I1, vector<int> I2, int B)
{
  int carry = 0;
  vector<int> sum;
  reverse(I1.begin(), I1.end());
  reverse(I2.begin(), I2.end());

  // Zero-padding
  while(I1.size() > I2.size())
  {
        I2.push_back(0);
  }
  while(I2.size() > I1.size())
  {
        I1.push_back(0);
  }
  for (int i = 0; i < I1.size(); i++)
  {
      if (I1[i] + I2[i] + carry >= B)
      {
        sum.push_back(I1[i] + I2[i] - B + carry);
        carry = 1;
      }
      else
      {
        sum.push_back(I1[i] + I2[i] + carry);
        carry = 0;
      }
  }
  if (carry != 0)
  {
    sum.push_back(carry);
  }
  reverse(sum.begin(), sum.end());
  return sum;
}

/* School method for Subtraction - Method: schoolSubtraction
   Parameter: int vector I1, I2 and base value.
   Return: Subtraction of two int vector I1 and I2. */

vector<int> schoolSubtraction(vector<int> I1, vector<int> I2, int B)
{
  int carry = 0;
  vector<int> subtract;
  reverse(I1.begin(), I1.end());
  reverse(I2.begin(), I2.end());

  //Zero-padding
  while(I1.size() > I2.size())
  {
      I2.push_back(0);
  }
  while(I2.size() > I1.size())
  {
      I1.push_back(0);
  }
  for (int i = 0; i < I1.size(); i++)
  {
      if (I1[i] - I2[i] - carry < 0)
      {
        subtract.push_back(I1[i] - I2[i] + B - carry);
        carry = 1;
      }
      else
      {
        subtract.push_back(I1[i] - I2[i] - carry);
        carry = 0;
      }
  }
  reverse(subtract.begin(), subtract.end());
  return subtract;
}

/* School method for Multiplication - Method: schoolMultiplication
   Parameter: int vector I1, I2 and base value.
   Return: Multiplication of two int vector I1 and I2.*/

vector<int> schoolMultiplication(vector<int> I1, vector<int> I2, int B)
{
  int carry = 0;
  vector<int> multi, tmp;
  reverse(I1.begin(), I1.end());
  reverse(I2.begin(), I2.end());
  for (int i = 0; i < I2.size(); i++)
  {
    carry = 0;
    for (int j = 0; j < I1.size(); j++)
    {
      if (I1[j] * I2[i] + carry >= B)
      {
        tmp.push_back((I1[j] * I2[i] + carry) % B);
        carry = ((I1[j] * I2[i] + carry - ((I1[j] * I2[i] + carry) % B)) / B);
      }
      else
      {
        tmp.push_back(I1[j] * I2[i] + carry);
        carry = 0;
      }
    }
    if (carry != 0)
    {
      tmp.push_back(carry);
	}
    for (int k = 0; k < i; k++)
    {
      tmp.insert(tmp.begin(), 0);
    }
    reverse(tmp.begin(), tmp.end());
    multi = schoolAddition(tmp, multi, B);
    tmp.clear();
  }
  return multi;
}

/* Integer to Vector conversion - Method: intToVector
   Parameter: int value and base value.
   Return: Vector - intVec */

vector<int> intToVector(int value, int B)
{
  vector<int> intVec;
  for (; value > 0; value /= B)
    intVec.push_back(value % B);
  reverse(intVec.begin(), intVec.end());
  return intVec;
}

/* Karatsuba method for Multiplication - Method: karatsubaMulti
   Parameter: int vector I1, I2 and base value.
   Return: Multiplication of two int vector I1 and I2. */

vector<int> karatsubaMulti(vector<int> I1, vector<int> I2, int B)
{
  vector<int> a1,a0,b1,b0,c0,c1,c2,d;
  int n = max(I1.size(), I2.size());
  if (n = 3)
  {
    return schoolMultiplication(I1, I2, B);
  }
  n = ceil(n/2);

  if (I1.size() <= n)
  {
    a1.push_back(0);
    a0 = I1;
  }

  else
  {
    for (int i = 0; i < I1.size() - n;i++)
    {
      a1.push_back(I1[i]);
      reverse(a1.begin(), a1.end());
    }
    for (int i = I1.size(); i < n;i++)
    {
      a0.push_back(I1[i]);
      reverse(a0.begin(), a0.end());
    }
  }

  if (I2.size() <= n)
  {
    b1.push_back(0);
    b0 = I2;
  }

  else
  {
    for (int i = 0;i < I2.size() - n;i++)
    {
      b1.push_back(I2[i]);
      reverse(b1.begin(), b1.end());
    }
    for (int i = I2.size();i < n;i++)
    {
      b0.push_back(I2[i]);
      reverse(b0.begin(), b0.end());
    }
  }

  c0 = karatsubaMulti(a0, b0, B);
  c1 = karatsubaMulti(a1, b1, B);
  c2 = karatsubaMulti(schoolSubtraction(a0, a1, B), schoolSubtraction(b0, b1, B), B);

  vector<int> tmp1 = schoolMultiplication(c1, intToVector(int(pow(B, 2 * n)), B), B);
  vector<int> tmp2 = schoolAddition(tmp1, c0, B);
  vector<int> tmp3 = schoolAddition(tmp2, c1, B);
  vector<int> tmp4 = schoolSubtraction(tmp3, c2, B);
  vector<int> tmp5 = schoolMultiplication(tmp4, intToVector(int(pow(B, n)), B), B);

  vector<int> answer = schoolAddition(tmp5, c0, B);

  return answer;
}

//Main method for websubmission testcases.

int main()
{
  int B, numbers = 0;
  vector<int> I1, I2;
  string input, tmp;
  getline(cin, tmp);
  stringstream ss(tmp);
  while (ss >> input)
  {
    //I1 into vector
    if (numbers == 0)
    {
      for (int i = 0; i < input.size(); i++)
      {
        I1.push_back(input[i] - 48);
      }
    }
    //I2 into vector
    if (numbers == 1)
    {
      for (int i = 0; i < input.size(); i++)
      {
        I2.push_back(input[i] - '0');
      }
    }
    //Base
    if (numbers == 2)
    {
      istringstream buffer(input);
      buffer >> B;
    }
    numbers++;
  }
  outVector(schoolAddition(I1, I2, B));
  cout << " ";
  outVector(karatsubaMulti(I1, I2, B));

  return 0;
}

/* Useful References: Acknowledgements 
[1] https://en.wikipedia.org/wiki/Recursion
[2] https://stackoverflow.com/questions/19841186/karatsuba-c-implementation
[3] https://en.wikipedia.org/wiki/Karatsuba_algorithm
[4] https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/ */