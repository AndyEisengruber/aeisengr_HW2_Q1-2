/*************************************************************************
** Author : Andrew Eisengruber
** Program : hw2, q2
** Date Created : February 23rd, 2024
** Date Last Modified : February 23rd, 2024
** Usage : No command line arguments
**
** Problem:
Your program should have the following items:
(a) Define a Check struct which has the following components with appropriate data types and an overloaded op-
erator which takes Check and a float variable to compare whether the CheckAmount is greater than the second
variable. Also, there should be an overload << for this struct to be able to print all details in a single line when
user uses cout<<check where check is a Check type.
• CheckNum
• CheckMemo
• CheckAmount
*************************************************************************/

#include <iostream>
#include <string>
using namespace std;

struct Check {

    int CheckNum;
    string CheckMemo;
    double CheckAmount;

    // overloaded > operator
    bool operator>(const float& amount) const {
        return CheckAmount > amount;
    }

    //overloaded << operator
    friend ostream& operator << (ostream& os, const Check& check) {
        os << "CheckNum: " << check.CheckNum << ", CheckMemo: " << check.CheckMemo << "< CheckAmount: " << check.CheckAmount;
        return os;
    }

};

class CheckBook {
private:
    float balance;
    Check* chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;

public:
    // our getters
    float getBalance() const { return balance; }
    float getLastDeposit() const { return lastDeposit; }
    int getNumOfChecks() const { return numOfChecks; }
    int getCheckBookSize() const { return checkBookSize; }
    //our setters
    void setBalance(float b) { balance = b; }
    void setLastDeposit(float ld) { lastDeposit = ld; }
    void setNumbOfChecks(int cbs) { checkBookSize = cbs; }

    //default constructor
    CheckBook() : balance(0), numOfChecks(0), checkBookSize(4) {
        chkPtr = new Check[checkBookSize];
    }

    //Secondary constructor
    CheckBook(float initial_balance) : balance(initial_balance), numOfChecks(0), checkBookSize(2) {
        chkPtr = new Check[checkBookSize];
    }
    //our destructor
    CheckBook(const CheckBook& cb) {
        //copy all data members
        balance = cb.balance;
        lastDeposit = cb.lastDeposit;
        numOfChecks = cb.numOfChecks;
        checkBookSize = cb.checkBookSize;

        //here we allocate memory for the chkPtr and copy the checks
        chkPtr = new Check[checkBookSize];
        for (int i = 0; i < numOfChecks; i++) {
            chkPtr[i] = cb.chkPtr[i];
        }
    }
    //overloaded assignment operator
    CheckBook& operator=(const CheckBook& cb) {
        if (this != &cb) {
            //free up the existing memory
            delete[] chkPtr;

            //copy all data members like before
            balance = cb.balance;
            lastDeposit = cb.lastDeposit;
            numOfChecks = cb.numOfChecks;
            checkBookSize = cb.checkBookSize;

            //then allocate memory for chkPtr and copy the checks
            chkPtr = new Check[checkBookSize];
            for (int i = 0; i < numOfChecks; i++) {
                chkPtr[i] = cb.chkPtr[i];
            } 
        }
        return *this;
    }

    //our deposit funciton
    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
    }
    //our writeCheck function
    bool writeCheck(const Check& c) {
        if (c > balance) {
            return false;
        }
        //Update our balance and the number of checks
        balance -= c.CheckAmount;
        numOfChecks++;

        //Double the size of teh Check array if it is necessary
        if (numOfChecks > checkBookSize / 2) {
            Check* newChkPtr = new Check[checkBookSize * 2];

            for (int i = 0; i < numOfChecks; i++) {
                newChkPtr[i] = chkPtr[i];
            }
            delete[] chkPtr;
            chkPtr = newChkPtr;
            checkBookSize *= 2;
        }
        //Now we update the check array
        chkPtr[numOfChecks - 1] = c;

        return true;
    }

    //our display function
    void displayChecks() const {
        for (int i = numOfChecks - 1; i >= 0; i--) {
            cout << chkPtr[i] << endl;
        }
    }

    //checkTest function 
    void checkTest(CheckBook& cb, float balance) {
        while (balance > 0) {
            Check c;
            c.CheckAmount = 10; //write small checks
            if (cb.writeCheck(c)) {
                balance -= c.CheckAmount;
            }
            else {
                break;
            }
        }
        cb.displayChecks();
    }


};




int main()
{
    CheckBook cb(10000); //Initializing the checkbook with a high balance
    checkTest(cb, cb.getBalance());
    return 0;



}


