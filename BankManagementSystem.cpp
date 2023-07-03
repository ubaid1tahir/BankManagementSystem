using namespace std;

// add external libraries
#include<iostream>
#include<string>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<array>
#include<stdio.h>

// display 
void start() {
    system("cls");
    cout << "\t\t\t\t ***** Bank Management System *****" << endl;
}

void menu() {
    cout << "\t Menu " << endl;
    cout << "1. Opening An Account" << endl;
    cout << "2. Deposit Amount" << endl;
    cout << "3. Withdraw Amount" << endl;
    cout << "4. Transaction History" << endl;
    cout << "5. Check Balance" << endl;
    cout << "0. Exit" << endl;
}

// performance

void opening(){
    // variables 
    string title, number, type;
    long opening_balance;
    // input string
    bool isnull = false;
    do {
        cout << "Enter Account Title :";
        getline(cin, title);
        if (title == "") {
            cout << "Title must be required" << endl;
            isnull = true;
        }
        else {
            isnull = false;
        }
    } while (isnull);
    Start:
    cout << "Enter Account Number :";
    cin >> number;
    fstream accountfile;
    accountfile.open("Accounts", ios::out | ios::app);
    fstream read;
    string str;
    read.open("Accounts");
    if (read.is_open()) {
        while (read) {
            getline(read, str);
            if (str == number) {
                cout << "This account number is already existed." << endl;
                goto Start;
            }
        }
    }
    cout << "Enter Account Type :";
    cin >> type;
    bool isvalid = true;
    do {
        cout << "Enter Opening Balance - Minimum 15000:";
        cin >> opening_balance;
        if (opening_balance < 15000) {
            cout << "Opening balance must be greater or equal to 15000" << endl;
            isvalid = false;
        }
        else {
            isvalid = true;
        }
    } while (!isvalid);
    try {
        
        accountfile << number << "\n";
        accountfile.close();
        fstream file;
        file.open(number, ios::out);
        file << title << " whose account number is " << number << " makes an account of type " << type
            << " and the opening balance is " << opening_balance << "." << '\n';
        file.close();
        fstream balance;
        balance.open("balance", ios::app);
        balance << number << "|" << opening_balance << "\n";
        balance.close();
    }
    catch (exception ex) {
        cout << "Error in writing your account in file. Please try later" << endl;
    }
}


void update(long balance,string number,string mode) {
    fstream tempfile;
    long long payment = balance;
    tempfile.open("balance");
    fstream acttempfile;
    acttempfile.open("tempfile", ios::out | ios::app);
    string str, previous, strpayment;
    if (tempfile.is_open()) {
        while (tempfile) {
            getline(tempfile, str);
            if (str == previous) {
                break;
            }
            if (!str.find(number)) {
                bool isbar = false;
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == '|') {
                        isbar = true;
                        i++;
                    }
                    if (isbar) {
                       strpayment += str[i];
                    }
                }
                double totalbalance = 0.0;
                if (mode == "deposit") {
                    payment += atoll(strpayment.c_str());
                    totalbalance += payment;
                }
                else if (mode == "withdraw") {
                    if (payment > atoll(strpayment.c_str())) {
                        cout << "You have not enough balance- Transaction fails" << endl;
                        cout << "press any key to continue..." << endl;
                        char choose = _getch();
                        return;
                    }
                    else {
                        totalbalance = atoll(strpayment.c_str());
                        totalbalance -= payment;
                    }
                }
                
                acttempfile << number <<"|" << totalbalance << '\n';
            }
            else {
                acttempfile << str << '\n';
            }
            previous = str;
        }
    }
    tempfile.close();
    acttempfile.close();

    //// remove the file "balance"
    if (remove("balance") != 0)
        perror("Error.. Try Later");
    
    // rename

    char oldname[] = "tempfile";
    char newname[] = "balance";

    /*	Deletes the file if exists */
    if (rename(oldname, newname) != 0)
        perror("Error.. Try Later");


    cout << "press any key to continue..." << endl;
    char choose = _getch();
}

void deposit() {
    string payment_method, account_number, title;
    string choice;
    long deposit_money;
    cout << "Your Name :";
    string name;
    cin >> name;
    bool isnull = false;
    do {
        cout << "Select Deposit Method :" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Cheque" << endl;
        cout << "Input 1 or 2:";
        cin >> choice;
        if (choice == "1") {
            payment_method = "Cash";
            isnull = false;
        }
        else if (choice == "2") {
            payment_method = "Cheque";
            isnull = false;
        }
        else {
            isnull = true;
            "Invalid Input";

        }
    } while (isnull);
    cout << "Enter account title :";
    cin >> title;
    cout << "Enter Account Number :";
    cin >> account_number;
    cout << "Enter Deposit Balance :";
    cin >> deposit_money;
    fstream deposit;
    deposit.open(account_number, ios::app);
    deposit << name << " has sent " << deposit_money << " to " << account_number << " by using the " << payment_method << " method" << '\n';
    deposit.close();
    cout << "You successfully deposited " << deposit_money << endl;
    update(deposit_money,account_number,"deposit");
}

void withdraw() {
    long withdraw_money;
    string account_number;
    string name = "",title = "";
    cout << "Enter Name :";
    cin >> name;
    bool isnull = false;
    do {
        cout << "Enter Account Title :";
        getline(cin, title);
        if (title == "") {
            cout << "Title must be required" << endl;
            isnull = true;
        }
        else {
            isnull = false;
        }
    } while (isnull);
    cout << "Enter Account Number :";
    getline(cin, account_number);
    cout << "Enter Balance :";
    cin >> withdraw_money;
    fstream withdraw;
    withdraw.open(account_number, ios::app);
    withdraw << name << " has withdrawn " << withdraw_money << " from " << account_number << '\n';
    withdraw.close();
    cout << "You successfully withdrawn " << withdraw_money << endl;
    update(withdraw_money, account_number, "withdraw");
}




void FileHandling() {
    fstream balance;
    balance.open("balance", ios::out);
    balance << "Title" << "|" << "Balance" << "\n";
    balance.close();
}

void CheckBalance() {
    string title, account_number;
    cout << "Enter Account title :";
    cin >> title;
    cout << "Enter Account Number :";
    cin >> account_number;
    ifstream myfilebalance;
    myfilebalance.open("balance");
    string myline;
    bool isbar = false;
    string str,previous;
    if (myfilebalance.is_open()) {
        while (myfilebalance) { // equivalent to myfile.good()
            getline(myfilebalance, myline);
            if (!myline.find(account_number)) {// find method todo
                for (int i = 0; i < myline.length(); i++) {
                    if (myline[i] == '|') {
                        isbar = true;
                        break;
                    }
                    if (!isbar) {
                        str += myline[i];
                    }
                }
                if (str != previous) {
                    if (str == account_number) {
                        cout << myline << '\n';
                    }
                }
                
                previous = str;
                str = "";
                isbar = false;
            }
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }
    cout << "press any key to continue..." << endl;
    char choose = _getch();
}

void TransactionsHistory() {
    string title;
    cout << "Enter your account number :";
    cin >> title;

    ifstream myfile;
    myfile.open(title);
    string myline;
    if (myfile.is_open()) {
        while (myfile) { // equivalent to myfile.good()
            getline(myfile, myline);
            cout << myline << '\n';
            //if (!myline.find("1")) {// find method todo
            //    cout << myline << '\n';
            //}
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }
    cout << "press any key to continue..." << endl;
    char choose = _getch();
}
int main(){;
    cout << "\t\t\t\t ***** Bank management system *****" << endl;
    fstream bal;
    bal.open("balance", ios::out | ios::app);
    bal.close();
    do {
        start();
        menu();
        cout << "press a number between 1 to 5 :" << endl;
        char choose = _getch();
        switch (choose)
        {
        case '1':
            start();
            opening();
            break;
        case '2':
            start();
            deposit();
            break;
        case '3':
            start();
            withdraw();
            break;
        case '4':
            start();
            TransactionsHistory();
            break;
        case '5':
            start();
            CheckBalance();
            break;
        case '0':
            start();
            exit(0);
            break;
            
        default:
            cout << "Invalid input" << endl;
            break;
        }
    } while (true);
}

