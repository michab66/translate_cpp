#include "ConvertNumberToWord.h"


ConvertNumberToWord::ConvertNumberToWord()
{


}


string ConvertNumberToWord::convertInToOut(string input)
{
  string output;
  string input2("            ");

  int length = input.length();

  reverse(input.begin(), input.end());
  
  for (int i = 0; i < length; i++)
  {

    input2[i] = input[i];
  }

  string underThousand = "";
  string overThousand = "";
  string overMillion = "";

  underThousand = threeNumbersToWord(input2[2], input2[1], input2[0], 0);
  overThousand = threeNumbersToWord(input2[5], input2[4], input2[3], 1);
  overMillion = threeNumbersToWord(input2[8], input2[7], input2[6], 1);
  

  if (overThousand != "")
  {

    output = overThousand.append(" tausend ").append(underThousand);

  }
  else
  {
    output = underThousand;

  }

  if (overMillion != "")
  {
    if ((input2[8] == '0' || input2[8] == ' ') && (input2[7] == '0' || input2[7] == ' ') && (input2[6] == '1'))
    {
      output = overMillion.append(" million ").append(output);
    }
    else
    {
      output = overMillion.append(" millionen ").append(output);
    }

  }

  bool isZero = true;
  
  for (int i = 0; i < 8; i++)
  {
    if (input2[i] != ' ' && input2[i] != '0')
    {
      isZero = false;
      break;

    }


  }

  if (isZero)
  {

    output = "Null";

  }


  output = clnstr(output);
  output[0] = toupper(output[0]);

  return output;

}








string ConvertNumberToWord::threeNumbersToWord(char char1, char char2, char char3, int thousand)
{

  string output = "";
  string tennerWord = "";
  string hundredWord = "";


  if (char2 == '1' && char3 == '1')
  {

    tennerWord = "elf";

  }
  else if (char2 == '1' && char3 == '2')
  {

    tennerWord = "zw�lf";

  }
  else if (char2 == '1' && char3 == '7')
  {

    tennerWord = "siebzehn";

  }
  else if (char2 == '1' && char3 > '2')
  {

    tennerWord = oneNumberToWordOnner(char3, 1).append(oneNumberToWordTenner(char2));

  }
  else if (char2 > '1' && char3 > '2')
  {

    tennerWord = oneNumberToWordOnner(char3, 1).append("und").append(oneNumberToWordTenner(char2));

  }
  else
  {
    if (char2 == '0' || char2 == ' ')
    {
      tennerWord = oneNumberToWordOnner(char3, thousand);
    }
    else
    {

      if (char3 == '0')
      {
        tennerWord = oneNumberToWordTenner(char2);
      }
      else
      {
      
        tennerWord = oneNumberToWordOnner(char3, 1).append("und").append(oneNumberToWordTenner(char2));

      }
    }

  }

  if (char1 != '0' && char1 != ' ')
  {
    hundredWord = oneNumberToWordOnner(char1, 1).append("hundert");
  }

  
  output = hundredWord.append(tennerWord);
  

  return output;


}



string ConvertNumberToWord::oneNumberToWordOnner(char charIn, int position)
{
 
  string oneer = "";

  if (charIn == '1')
  {

    if (position == 0)
    {
      oneer = "eins";
    }
    else
    {
      oneer = "ein";
    }

  }
  else if (charIn == '2')
  {

    oneer = "zwei";

  }
  else if (charIn == '3')
  {

    oneer = "drei";

  }
  else if (charIn == '4')
  {

    oneer = "vier";

  }
  else if (charIn == '5')
  {

    oneer = "fuenf";

  }
  else if (charIn == '6')
  {

    oneer = "sechs";

  }
  else if (charIn == '7')
  {

    oneer = "sieben";

  }
  else if (charIn == '8')
  {

    oneer = "acht";

  }
  else if (charIn == '9')
  {

    oneer = "neun";

  }

  return oneer;
}



string ConvertNumberToWord::oneNumberToWordTenner(char charIn)
{

  string tenner = "";

  if (charIn == '1')
  {

    tenner = "zehn";

  }
  else if (charIn == '2')
  {

    tenner = "zwanzig";

  }
  else if (charIn == '3')
  {

    tenner = "dreißig";

  }
  else if (charIn == '4')
  {

    tenner = "vierzig";

  }
  else if (charIn == '5')
  {

    tenner = "fünfzig";

  }
  else if (charIn == '6')
  {

    tenner = "sechzig";

  }
  else if (charIn == '7')
  {

    tenner = "siebzig";

  }
  else if (charIn == '8')
  {

    tenner = "achtzig";

  }
  else if (charIn == '9')
  {

    tenner = "neunzig";

  }

  return tenner;

}


string ConvertNumberToWord::clnstr(string Input)
{
  int laenge = strlen(Input.c_str()) - 1;
  for (int i = 0; i <= laenge; ++i)
  {
    switch (Input[i])
    {
    // Encoding fails on Mac.
    // case '�': Input[i] = 0x84;
    //   break;
    // case '�': Input[i] = 0x94;
    //   break;
    // case '�': Input[i] = 0x81;
    //   break;
    // case '�': Input[i] = 0x8E;
    //   break;
    // case '�': Input[i] = 0x99;
    //   break;
    // case '�': Input[i] = 0x9A;
    //   break;
    // case '�': Input[i] = 0xE1;
    //   break;
    default: break;
    }
  }
  return (Input);
};