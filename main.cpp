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

const string CURRENCY = "franc";
const string CURRENCY_CENTS = "centime";
const double MIN_AMOUNT = 0;
const double  MAX_AMOUNT = 999999.99;

/**
 * Convert a double number in a Vaudois price.
 * @param amount a double between 0 and 999999.99
 *
 * @return the converted amount in a string
 */
string montantEnVaudois(double amount);

/**
 * @brief check if user's input is between min and max values
 * @param input user's input to check
 * @param min minimum accepted value
 * @param max maximum accepted value
 * @return boolean result of condition
 */
bool checkInput(double input, double min, double max);

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
 * @brief Convert integer parts of an entered number into a string
 * adding franc(s) and dealing with plural
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

int main() {

  double d;

  while (cin >> d) {
    cout << montantEnVaudois(d) << endl;
  }
  return 0;
}

string montantEnVaudois(double amount) {
  
  if (!checkInput(amount, MIN_AMOUNT, MAX_AMOUNT)) {
    return "ERREUR - Entree non-valide!";
  }
  // split the francs and the cents
  int francs = (int) amount;
  int cents = int((amount - francs + 0.005) * 100);

  // if the user entered 0 as the amount, return 0
  if (francs == 0 and cents == 0) {
    return getUnitText(francs) + " franc";
  }

  int part = francs;
  bool accord = true;
  string francsText;
  while (part) {
    // get the first three numbers
    int group = part % 1000;

    francsText = convertFrancs(group, accord) + " " + francsText;

    // remove the part that was just converted to text
    part /= 1000;
    // check if there are anymore numbers to convert
    if (part) {
      // if so, then add the thousands text
      francsText = "mille " + francsText;
    }

    //
    accord = false;
  }

  // add the currency to the end
  francsText += CURRENCY;
  // check plural
  francsText += francs > 1 ? "s" : "";

  // check if there are cents to convert.
  string centsText;
  if (cents) {
    centsText = convertCents(cents);
  }

  // build the return text.
  //  if there are francs and cents the return text with both otherwise, return only the one that isn't empty
  return francs and cents ? francsText + " et " + centsText : francs ? francsText : cents ? centsText : "";
}

string getUnitText(int number) {
  switch (number) {
    case 0:
      return "zero";
    case 1:
      return "un";
    case 2:
      return "deux";
    case 3:
      return "trois";
    case 4:
      return "quatre";
    case 5:
      return "cinq";
    case 6:
      return "six";
    case 7:
      return "sept";
    case 8:
      return "huit";
    case 9:
      return "neuf";
    default:
      return "UNITE ERREUR";
  }
}

string getTeensText(int number) {
  switch (number) {
    case 11:
      return "onze";
    case 12:
      return "douze";
    case 13:
      return "treize";
    case 14:
      return "quatorze";
    case 15:
      return "quinze";
    case 16:
      return "seize";
    default:
      return "TEEN ERREUR";
  }
}

string getDozenText(int number) {
  switch (number) {
    case 1:
      return "dix";
    case 2:
      return "vingt";
    case 3:
      return "trente";
    case 4:
      return "quarante";
    case 5:
      return "cinquante";
    case 6:
      return "soixante";
    case 7:
      return "septante";
    case 8:
      return "huitante";
    case 9:
      return "nonante";
    default:
      return "DIXAINE ERREUR";
  }
}

string getHundredText(int number) {

  string text = "cent";

  // avoid "un cent"
  if (number != 1) {
    text = getUnitText(number) + " " + text;
  }

  return text;
}

string convertFrancs(int number, bool checkGrammar) {
  string text;

  if (number >= 100) {
    text += getHundredText(number / 100);

    text += number / 100 != 1 and checkGrammar ? number % 100 != 0 ? " " : "s" : " ";
    number = number % 100;

  }
  if (number >= 17 or number == 10) {
    text += getDozenText(number / 10);
    number = number % 10;

    if (number) {
      text += number == 1 ? " et " : "-";
    }
  } else if (number > 10) {
    text += getTeensText(number);
    number = 0;
  }
  if (number > 0) {
    text += getUnitText(number);
  }

  return text;
}

string convertCents(int number) {
  string text = convertFrancs(number, true) + " " + CURRENCY_CENTS;
  text += number > 1 ? "s" : "";
  return text;
}

bool checkInput(double input, double min, double max) {
  return input >= min && input <= max;
}