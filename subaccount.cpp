#include "subaccount.h"
#include <iostream>
#include <iomanip>
using namespace std;

//print menu for this default subaccount and then prompt user
void SubAccount::PrintMenu() const {
  cout << endl << endl;
  cout << "|";
  cout << setfill('-') << setw(50) << "|" << endl;
  cout << "| Eligible services for sub-account " << accNum << endl;
  cout << "| D -- Deposit" << endl;
  cout << "| W -- Withdraw" << endl;
  cout << "| X -- Exit" << endl;
  cout << "|";
    cout << setfill('-') << setw(50) << "|" << endl;
  cout << "Please enter your selection: ";
}

//prints the sub account (default case)
void SubAccount::PrintSubAccount() const {
  cout << "    | Sub-Account number: " << accNum << endl
            << "    | Balance: " << balance << endl;
}

//Default Subaccount Menu user loop
void SubAccount::SubAccountMenu() {
  char userInput;
  int userAmount;
  PrintMenu();
  cin >> userInput;

  while (toupper(userInput) != 'X') {
    switch (toupper(userInput)) {
    case 'D':
      cout << "    Enter amount to deposit: ";
      cin >> userAmount;
      Deposit(userAmount);
      break;

    case 'W':
      cout << "    Enter amount to withdraw: ";
      cin >> userAmount;
      Withdraw(userAmount);
      break;

    default:
      cout << "Error not valid character" << endl;
      break;
    }

    PrintMenu();
    cin >> userInput;
  }
  cout << endl << "    | End of service for Sub-Account " << accNum << endl;
}

// Static Saving Account Keys getters (starts at 999)
int SavingAccount::savingAccountKeys = 999;

//prints menu (override for checking account)
void CheckingAccount::PrintMenu() const {
  cout << endl << endl;
  cout << "|";
  cout << setfill('-') << setw(50) << "|" << endl;
  cout << "| Eligible services for sub-account " << accNum << endl;
  cout << "| D -- Deposit" << endl;
  cout << "| W -- Withdraw" << endl;
  cout << "| C -- Max Capacity" << endl;
  cout << "| L -- Lock Sub-Account" << endl;
  cout << "| U -- Unlock Sub-Account" << endl;
  cout << "| X -- Exit" << endl;
  cout << "|";
    cout << setfill('-') << setw(50) << "|" << endl;
  cout << "Please enter your selection: ";
}

// Static Checking account keys getters (starts at 5999)
int CheckingAccount::checkingAccountKeys = 5999;

// Deposit (checking account override for deposit)
void CheckingAccount::Deposit(int amount) {
  if (lock == true) {
    cout << "    | Account is currently locked!" << endl;
    cout << "    | Deposit was unsuccessful" << endl;
    return;
  } else {
    if (amount + balance > maxCap) {
      cout << "    | Deposit exceeds maximum capacity" << endl;
      cout << "    | Deposit was unsuccessful" << endl;
      return;
    } else {
      balance += amount;
      cout << "    | Deposit was successful" << endl;
      cout << "    | The current balance is " << balance << endl;
    }
  }
}

// Withdraw (checking account override for withdraw)
void CheckingAccount::Withdraw(int amount) {
  if (lock == true) {
    cout << "    | Account is currently locked!" << endl;
    cout << "    | Withdraw was unsuccessful" << endl;
    return;
  } else {
    if (balance - amount < 0) {
      cout << "    | Withdraw exceeds current funds" << endl;
      cout << "    | Withdraw was unsuccessful";
      return;
    } else {
      balance -= amount;
      cout << "    | Withdraw was successful" << endl;
      cout << "    | The current balance is " << balance << endl;
    }
  }
}

// SubAccountMenu looping (checking account override for subaccountmenu())
void CheckingAccount::SubAccountMenu() {
  char userInput;
  int userAmount;
  PrintMenu();
  cin >> userInput;

  while (toupper(userInput) != 'X') {
    switch (toupper(userInput)) {
      case 'D':
        cout << "    Enter amount to deposit: ";
        cin >> userAmount;
        Deposit(userAmount);
        break;

      case 'W':
        cout << "    Enter amount to withdraw: ";
        cin >> userAmount;
        Withdraw(userAmount);
        break;

      case 'C': 
        cout << "    Please enter desired maximum: ";
        cin >> userAmount;
        if (userAmount < balance) {
          cout << "    | Desired max is less than current balance please withdraw so that the balance is below desired maximum" << endl;
        } else {
          SetMaxCap(userAmount);
          cout << "    | New Max-Cap is " << maxCap << endl;
        }
        break;

      case 'L':
        if (lock == false) {
          lock = true;
          cout << "    | Account is now locked" << endl;
        } else {
          cout << "    | Account is already locked" << endl;
        }
        break;

      case 'U':
        if (lock == true) {
          lock = false;
          cout << "    | Account is now unlocked" << endl;
        } else {
          cout << "    | Account is already unlocked" << endl;
        }
        break;

      default:
        cout << "    | Error not valid character" << endl;
        break;
    }

    PrintMenu();
    cin >> userInput;
    //print menu here
  }
  cout << endl << "    | End of service for Sub-Account " << accNum << endl;
}

//print our sub account info (checking info override)
void CheckingAccount::PrintSubAccount() const {
  cout << "    | Sub-Account number: " << accNum << endl
            << "    | Balance: " << balance << endl;
  cout << "    | The maximum capacity is: " << maxCap << endl;

  if (lock == true) {
    cout << "    | The sub-account is locked." << endl;
  } else {
    cout << "    | The sub-account is not locked." << endl;
  }
}
