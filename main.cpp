/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 06
 Fichier     : main.cpp
 Auteur(s)   : Emmanuel Janssens, Sylvain Laydernier, Doran Kayoumi
 Date        : 28.11.2018

 But         : Transform numerical data into his corresponding string 
               (3214 become "trois mille deux cent quatorze")

 Remarque(s) :

 Compilateur : g++<6.3.0>
 -----------------------------------------------------------------------------------
 */
#include <iostream>

using namespace std;

/**
 * Convert a double number in a Vaudois price.
 * @param amount a double between 0 and 999999.99
 *
 * @return the converted amount in a string
 */
string montantEnVaudois(double amount);

/**
 * @brief return corresponding text to the 0-9 integer
 * @param unit to convert to text (int 0-9)
 * 
 * @return intger's text in a string
 */
string getUnitText(int number);

/**
 * @brief return corresponding text to the selected teen (11-16)
 * @param teen to convert to text (11-16)
 * 
 * @return teen's text in a string
*/
string getTeensText(int number);

/**
 * @brief return corresponding text to the entered dozen
 * @param dozen to convert to text
 * 
 * @return dozen's text in a string
 */
string getDozenText(int number);

/**
 * @brief return corresponding text to the selected hundred with suffix "cent" 
 * if hundred is one, don't add any suffix
 * @param hundred to convert to text
 * 
 * @return hundred's text in a string
 */
string getHundredText(int number);

/*
 * @brief manage thousands from a double to return it as 
 * his complete corresponding string(2202 = deux mille deux cent deux)
 * @param double to extract thousands from
 * 
 * @return thousands' text
 */
string manageThousands(double number);

/*
 * @brief Convert integer parts of an entered number into a string
 * adding franc(s) and dealing with plurial
 * @param[int] number number to get as text
 * @param[bool] checkGrammar boolean to decide if we need to check
 * grammar or not
 * 
 * @return entire string of a number with "franc" or "francs" suffix
 */
string convertFrancs(int number, bool checkGrammar);

/*
 * @brief convert a given number to a cents part as a string
 * including "centimes" as suffix
 * @param int to convert as text
 * 
 * @return parameter's corresponding text
 */
string convertCents(int number);

int main()
{

    double d = 500500;

    cout << montantEnVaudois(d) << endl;
    //  while( cin >> d ) {
    //    cout << montantEnVaudois(d) << endl;
    //  }
    return 0;
}

string montantEnVaudois(double amount)
{

    // split the francs and the cents
    int francs = (int)amount;
    int cents = int((amount - francs + 0.005) * 100);

    // if the user entered 0 as the amount, return 0
    if (francs == 0 and cents == 0) {
        return getUnitText(francs) + " franc";
    }

    string francsText;
    if (francs <= 999)
    {
        francsText = convertFrancs(francs, true);
    }
    else
    {
        francsText = manageThousands(francs);
    }
    francsText += " franc";
    francsText += francs > 1 ? "s" : "";

    string centsText;
    if (cents)
    {
        centsText = convertCents(cents) + " centime";
        centsText += cents > 1 ? "s" : "";
    }

    // build the return text.
    //  if there are francs and cents the return text with both otherwise, return only the one that isn't empty
    return francs and cents ? francsText + " et " + centsText : francs? francsText : cents? centsText : "";
}

string getUnitText(int number)
{
    switch (number)
    {
        case 0: return "zero";
        case 1: return "un";
        case 2: return "deux";
        case 3: return "trois";
        case 4: return "quatre";
        case 5: return "cinq";
        case 6: return "six";
        case 7: return "sept";
        case 8: return "huit";
        case 9: return "neuf";
        default: return "UNITE ERREUR";
    }
}

string getTeensText(int number)
{
    switch (number)
    {
        case 11: return "onze";
        case 12: return "douze";
        case 13: return "treize";
        case 14: return "quatorze";
        case 15: return "quinze";
        case 16: return "seize";
        default: return "TEEN ERREUR";
    }
}

string getDozenText(int number)
{
    switch (number)
    {
        case 1: return "dix";
        case 2: return "vingt";
        case 3: return "trente";
        case 4: return "quarante";
        case 5: return "cinquante";
        case 6: return "soixante";
        case 7: return "septante";
        case 8: return "huitante";
        case 9: return "nonante";
        default: return "DIXAINE ERREUR";
    }
}

string getHundredText(int number)
{

    string text = "cent";

    if (number != 1)
    {
        text = getUnitText(number) + " " + text;
    }

    return text;
}

string convertFrancs(int number, bool checkGrammar)
{
    string text;

    int part = number;

    if (part >= 100)
    {
        text += getHundredText(part / 100);

        text += part / 100 != 1 and checkGrammar ? part % 100 != 0 ? " " : "s" : " ";
        part = part % 100;

    }
    if (part >= 17 or part == 10) {
        text += getDozenText(part / 10);
        part = part % 10;

        if (part)
        {
            text += part == 1 ? " et " : "-";
        }
    } else if (part > 10)
    {
        text += getTeensText(part);
        part = 0;
    }
    if (part > 0)
    {
        text += getUnitText(part);
    }

    return text;
}

string manageThousands(double number)
{

    int part1 = int(number / 1000);
    int part2 = (int)number % 1000;

    string text = "mille";

    // if part1 != 1, we need to add "mille" in the string to return
    if (part1 != 1)
    {
        text = convertFrancs(part1, false) + " " + text;
    }

    text += " " + convertFrancs(part2, true);
    return text;
}

string convertCents(int number)
{
    return convertFrancs(number, true);
}
