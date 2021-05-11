#pragma once
#include <iostream>
#include <string>

using namespace std;



class ConvertNumberToWord
{

public:
  ConvertNumberToWord();
  string convertInToOut(string input);

private:


  string threeNumbersToWord(char char1, char char2, char char3, int thousand);
  string oneNumberToWordOnner(char charIn, int position);
  string oneNumberToWordTenner(char charIn);
  string clnstr(string Input);

};

