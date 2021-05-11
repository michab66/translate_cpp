// Juergen Schmidt 2021

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "ConvertNumberToWord.h"

using namespace std;

namespace {

    /**
     *  
     */
    auto get_digit_packs(long number, int pack_size = 3, int base = 10) -> auto
    {
        if ( number == 0 )
            return vector<int>{};

        auto divisor =
            static_cast<int>( std::pow(base, pack_size) );

        auto current_pack =
            number % divisor;
        auto result =
            get_digit_packs(number / divisor);
        result.push_back(current_pack);

        return result;
    }

    auto number_triple_to_word(int number) -> string
    {
        if (number > 999)
            throw std::invalid_argument( std::to_string(number) );

        auto pairs = get_digit_packs(number, 2);

        if (pairs.size() > 1) {
            string result;

            if (pairs[0] == 1)
                result.append("ein");
            else
                result.append(number_triple_to_word(pairs[0]));

            result.append("hundert");
            
            // If second pair is zero we are done. Otherwise
            // translate this as well.

            if ( pairs[1] != 0 )
                result.append(number_triple_to_word(pairs[1]));

            return result;
        }

        // Base translation for single digits and special cases.
        switch (number)
        {
        case 0:
            return "null";
        case 1:
            return "eins";
        case 2:
            return "zwei";
        case 3:
            return "drei";
        case 4:
            return "vier";
        case 5:
            return "fünf";
        case 6:
            return "sechs";
        case 7:
            return "sieben";
        case 8:
            return "acht";
        case 9:
            return "neun";
        case 10:
            return "zehn";
        case 11:
            return "elf";
        case 12:
            return "zwölf";
        case 20:
            return "zwanzig";
        case 30:
            return "dreissig";
        case 40:
            return "vierzig";
        case 50:
            return "fünfzig";
        case 60:
            return "sechzig";
        case 70:
            return "siebzig";
        case 80:
            return "achzig";
        case 90:
            return "neunzig";
        }

        // Remaining are the two digit numbers.
        auto singles = get_digit_packs(pairs[0], 1);

        string result;
        
        // Oh this special case.
        if (singles[1] == 1 && singles[0] != 0 )
            result.append("ein");
        else
            result.append( number_triple_to_word(singles[1]) );

        if (singles[0] > 0)
        {
            result.append("und");
            result.append(number_triple_to_word(singles[0]*10));
        }

        return result;
    }

    // https://www.korrekturen.de/zahlwort/numeralia.shtml
    string triple_names(int triple, int triple_size)
    {
        switch (triple) {
        case 0:
            return "tausend";
        case 1:
            return triple_size == 1 ? "million" : "millionen";
        case 2:
            return triple_size == 1 ? "milliarde" : "milliarden";
        case 3:
            return triple_size == 1 ? "billion" : "billionen";
        case 4:
            return triple_size == 1 ? "billiarde" : "billiarden";
        case 5:
            return triple_size == 1 ? "trillion" : "trillionen";
        case 6:
            return triple_size == 1 ? "trilliarde" : "trilliarden";
        case 7:
            return triple_size == 1 ? "quadrillion" : "quadrillionen";
        case 8:
            return triple_size == 1 ? "quadrilliarde" : "quadrilliarden";
        default:
            return triple_size == 1 ? "phantastillion" : "phantastillionen";
        }
    }

    std::string translate(long number)
    {
        auto triple_groups = get_digit_packs(number);

        auto group_number = triple_groups.size() -2;

        string result;

        for (auto c : triple_groups)
        {
            result.append(number_triple_to_word(c));
            result.append(" ");
            if (group_number > 0) {
                result.append(triple_names(group_number, c));
                group_number--;
            }
        }

        return result;
    }
}


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

#if 0
    output = convertNumberToWord.convertInToOut(input);
    cout << input << " = " << output << endl;
#endif

    try {
        auto the_number = std::strtol(input.c_str(), nullptr, 10);

        auto digit_packs = get_digit_packs(
            the_number );

        for (auto c : digit_packs)
            cout << c << "\n";

        cout << translate(the_number) << "\n";
    }
    catch (std::exception& e) {
        cout << "Cold not convert to number: " << input << "\n";
    }
  }

  return 0;
};

