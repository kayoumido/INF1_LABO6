/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 06
 Fichier     : main.cpp
 Auteur(s)   : Emmanuel Janssens, Sylvain Laydernier, Doran Kayoumi
 Date        : 28.11.2018

 But         : Transforme une somme numérique en une version textuelle
               e.g. 3214 => trois mille deux cent quatorze
               
 Remarque(s) : Nous avons décidé d'arrondir les données saisies par l'utilisateur
               au lieu de retourner un message d'erreur.
               e.g. 52.99893 => 53.00, 52.523304 => 52.52
 Compilateur : g++<6.3.0>
 -----------------------------------------------------------------------------------
 */
#include <iostream>

using namespace std;

const string CURRENCY = "franc";
const string CURRENCY_CENTS = "centime";
const double MIN_AMOUNT = 0;
const double MAX_AMOUNT = 999999.99;

/**
 * @brief Translates real numbers into prices expressed in vaudois
 * @details E.g.
 *   12.30  -> "douze francs et trente centimes"
 *   200.01 -> "deux cents francs et un centime"
 *   180    -> "cent huitante francs"
 *   1.80   -> "un franc et huitante centimes"
 *   0.20   -> "vingt centimes"
 *   0      -> "zéro franc"
 *
 * @param[double] amount between 0 and 999999.99
 * @return[string] string of the amount in vaudois
 */
string montantEnVaudois(double amount);

/**
 * @brief check if user's input is between min and max values
 *
 * @param[double] input user's input to check
 * @param[double] min minimum accepted value
 * @param[double] max maximum accepted value
 * @return[bool] true if hte value in the range otherwise false
 */
bool checkInput(double input, double min, double max);

/**
 * @brief return corresponding text to the 0-9 integer
 *
 * @param[int] unit to convert to text (0-9)
 * @return[int] text in a string
 */
string getUnitText(int number);

/**
 * @brief get corresponding text to the selected teen (11-16)
 *
 * @param teen to convert to text (11-16)
 * @return teen's text in a string
*/
string getTeensText(int number);

/**
 * @brief get corresponding text to the given dozen number
 *
 * @param dozen to convert to text
 * @return dozen's text in a string
 */
string getDozenText(int number);

/**
 * @brief get corresponding text to the given hundred number.
 * which equals to the number with the suffix "cent".
 *
 * @param hundred to convert to text
 * @return hundred's text in a string
 */
string getHundredText(int number);

/**
 * @brief get the text to display for a group of 3 numbers
 * @details e.g. 
 *     The number 123456 can be split into two groups of 3 :
 *        1. "123" which represents the thousands or "mille" in vaudois
 *        2. "456" which doesn't have any related text to display
 *
 * @param[int] groupNumber
 * @return[string] the text of the group
 */
string getGroupText(int groupNumber);

/**
 * @brief convert a number into it's textual equivalent
 *
 * @param[int] number to convert
 * @param[bool] accord boolean to decide if we need to accord the text
 * @param[string] groupNumberName the specific text to add for a given
 *                group. (see getGroupText function)
 * @return[string] text of the converted number
 */
string convertFrancs(int number, bool accord, const string &groupNumberName);

/*
 * @brief convert a given number to a cents part as a string
 * including "centimes" as suffix
 *
 * @param[int] cents to convert as text
 * @return[string] text of the converted number
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

  amount += 0.005;
  // split the francs and the cents
  int francs = (int)amount;
  int cents = int((amount - francs) * 100);

  // if the user entered 0 as the amount, return the text for 0
  if (francs == 0 and cents == 0) {
    return getUnitText(francs) + " " + CURRENCY;
  }

  int part = francs;
  int groupNumber = 0;
  bool accord = true;
  string francsText;
  while (part) {

    // get the current group
    int group = part % 1000;

    francsText = convertFrancs(group, accord, getGroupText(groupNumber)) + francsText;

    // remove the part that was just converted to text
    part /= 1000;

    // the groups past the first don't need their
    // unit, dozens and hundreds to be accorded
    // since there's a suffix after them and according
    // to the french grammar rules regarding number,
    // they don't need to be accorded.
    accord = false;

    // pass to the next group
    ++groupNumber;
  }

  // add the currency to the end
  francsText += " " + CURRENCY;
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

string getGroupText(int groupNumber) {
  switch (groupNumber) {
    case 1:
      return "mille";
    default:
      return "";
  }
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

string convertFrancs(int number, bool accord, const string &groupNumberName) {
  string text;

  if (number >= 100) {
    text += getHundredText(number / 100);

    // the text is accorded only if it's desired.
    // if it is, then we check that the number isn't 100
    // and that there isn't anything afterwards.
    //  e.g. 230 -> doesn't take an "s"
    //       200 -> takes an "s"
    text += accord and number / 100 != 1 ? number % 100 != 0 ? " " : "s" : " ";
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

  // add group name only if the given name isn't empty
  if (!groupNumberName.empty()) {
    // avoid things like "un mille"
    if (number == 1) {
      text = groupNumberName;
    } else {
      text += " " + groupNumberName;
    }
    text += " ";
  }

  return text;
}

string convertCents(int number) {
  string text = convertFrancs(number, true, "") + " " + CURRENCY_CENTS;
  text += number > 1 ? "s" : "";
  return text;
}

bool checkInput(double input, double min, double max) {
  return input >= min && input <= max;
}
