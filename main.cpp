#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

#include "bank.h"
#include "bankaccount.h"
#include "subaccount.h"

int main() {
  // handling user input
  char userInput;
  string userString;

  // bank private members
  string newBankName;
  string newBankAddress;
  string newBankHours;

  // bank
  Bank UserBank = Bank();

  // -------------- Start Of Code ---------------//

  // name, address, working hours of bank && make bank
  cout << "Enter the name of the bank: ";
  getline(cin, newBankName);
  cout << "Enter the address of the bank: ";
  getline(cin, newBankAddress);
  cout << "Enter the working hours: ";
  getline(cin, newBankHours);

  UserBank.SetName(newBankName);
  UserBank.SetAddress(newBankAddress);
  UserBank.SetWorkingHours(newBankHours);

  cout << endl;

  // end of setup
  UserBank.PrintBankMenu();
  UserBank.UserMenu();
}