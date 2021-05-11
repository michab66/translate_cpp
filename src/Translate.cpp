// Juergen Schmidt 2021

#include <iostream>
#include <string>
#include <vector>
#include "ConvertNumberToWord.h"

using namespace std;


int main()
{
  cout << "e for exit." << endl;

  ConvertNumberToWord convertNumberToWord;
  string input = "";

  while (input.compare("e") != 0)
  {

    cout << ">translate ";

    input = "           ";
    cin >> input;
    string output;

    output = convertNumberToWord.convertInToOut(input);
    cout << input << " = " << output << endl;

  }

  return 0;
};

