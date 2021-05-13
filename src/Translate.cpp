/*
 * Implement a command line program that accepts a single number and prints 
 * this number textually in German or English language to standard out.
 *
 * Examples:
 * >translate 1
 * Eins
 * >translate 313
 * Dreihundertdreizehn
 * >translate 2000000
 * Zwei millionen
 * >translate 1234011
 * Eine million zweihundertvierunddreißig tausend elf
 */

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

using std::string;
using std::vector;

/**
 * Split the passed number in packets of digits of a certain size.
 * E.g. 123456, pack size 3: (123)(456).
 * E.g. 123456, pack size 2: (12)(34)(56).
 */
auto get_digit_packs(unsigned long number, int pack_size, int base = 10) -> auto
{
    if (number == 0)
        return vector<int>{};

    auto divisor =
        static_cast<int>(std::pow(base, pack_size));

    auto current_pack =
        number % divisor;
    auto result =
        get_digit_packs(number / divisor, pack_size);
    result.push_back(current_pack);

    return result;
}

/**
 * Convert a decimal number with a single digit to a string.
 */
auto number_digit_to_word(unsigned int number) -> string
{
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
    default:
        throw std::domain_error(std::to_string(number) + ">9");
    }
}

/**
 * Convert a decimal number with a maximum of two digits to
 * a string.
 */
auto number_pair_to_word(unsigned int number) -> string
{
    if (number > 99)
        throw std::domain_error(std::to_string(number) + ">99");
    else if (number < 10)
        return number_digit_to_word(number);

    // Translation for special cases.
    switch (number)
    {
    case 10:
        return "zehn";
    case 11:
        return "elf";
    case 12:
        return "zwölf";
    case 13:
        return "dreizehn";
    case 14:
        return "vierzehn";
    case 15:
        return "fünfzehn";
    case 16:
        return "sechzehn";
    case 17:
        return "siebzehn";
    case 18:
        return "achtzehn";
    case 19:
        return "neunzehn";
    case 20:
        return "zwanzig";
    case 30:
        return "dreißig";
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

    // Remaining are systematic two-digit numbers.
    auto singles = get_digit_packs(number, 1);

    string result;
        
    // Oh, this special case.
    if (singles[1] == 1 && singles[0] != 0)
        result.append("ein");
    else
        result.append( number_digit_to_word(singles[1]) );

    if (singles[0] > 0)
    {
        result.append("und");
        result.append(number_pair_to_word(singles[0]*10));
    }

    return result;
}

/**
 * Convert a decimal number with a maximum of three digits to
 * a string.
 */
auto number_triple_to_word(unsigned int number) -> string
{
    if (number > 999)
        throw std::domain_error(std::to_string(number) + ">999" );

    auto pairs = get_digit_packs(number, 2);

    if (pairs.size() == 0) {
        // Number was zero.
        return number_pair_to_word( number );
    }    
    else if (pairs.size() > 1) {
        string result;

        if (pairs[0] == 1)
            result.append("ein");
        else
            result.append(number_pair_to_word(pairs[0]));

        result.append("hundert");
            
        // If the second pair is zero we are done. Otherwise
        // translate this as well.

        if ( pairs[1] != 0 )
            result.append(number_pair_to_word(pairs[1]));

        return result;
    }

    return number_pair_to_word( pairs[0] );
}

// https://www.korrekturen.de/zahlwort/numeralia.shtml
auto triple_names(int triple, int triple_size) -> string
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

/**
 * Convert the passed number to its German textual representation.
 */
std::string translate(long number)
{
    if ( number == 0 )
        return number_pair_to_word( number );

    string result;

    if ( number < 0 )
    {
        result = "minus ";
        number = -number;
    }

    // Split the number into its triple-digit-groups.
    auto triple_groups = 
        get_digit_packs(number, 3);

    int group_number = 
        triple_groups.size();

    // Loop over the triple-digit-groups, translate each and
    // place the group-name (million, milliarde, etc.) in between.
    for (auto c : triple_groups)
    {
        group_number--;

        // If triple pack is empty, we skip this altogether. (1000011)
        if ( c == 0 )
            continue;
        // The 1 case for tausend. (1000)
        else if ( c == 1 && group_number == 1 )
            result.append("ein");
        // The remaining 1 cases.
        else if ( c == 1 && group_number > 1 )
            result.append("eine");
        // The regular case.
        else
            result.append(number_triple_to_word(c));

        result.append(" ");

        // Place the triple name between all packs but not after the last.
        if (group_number > 0) {
            result.append(triple_names(group_number-1, c));
            result.append(" ");
        }
    }

    return result;
}

auto processInput(string input) -> int
{
    try {
        size_t unprocessed;
        auto the_number = std::stol(
            input,
            &unprocessed);

        if (unprocessed < input.size())
            throw std::invalid_argument(input);

        std::cout << translate(the_number) << "\n";

        return 0;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << input << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Not convertible: " << input << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }

    return 1;
}

}

/**
 * Entry point.  Accept a single required argument from the command line or
 * enter a read-eval-print loop.
 */
int main(int argc, char**argv)
{
    if (argc == 2)
        return processInput(argv[1]);

    std::cout << "Enter an integer number or enter to quit.\n";

    while (true)
    {
        std::cout << "> ";

        std::string input;

        std::getline(std::cin, input);

        if (input.empty())
            return 0;

        processInput(input);
    }

    return 0;
};
