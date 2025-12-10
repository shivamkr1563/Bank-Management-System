#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<algorithm>

using namespace std;

class bankAccount {
    private:
        string bankName = "Shivam Bank Of India";
        int bankcode = 101;
        string accountHolderName;
        string accountNumber;
        string accountPassword;
        string addharNumber;
        string email;
        string phoneNumber;
        double balance;
    public:
        void savetoFile();
        void mainMenu();
        void createAccount();
        void loginBankAccount();
        void depositMoney();
        void withdrawMoney();
        void checkBalance();
        void accountDetails();
        void allTransactionHistory();
        void transferMoney();
        void generateAccountStatement();
        void calculateInterest();
        bool validateEmail(string email);
        bool validatePhone(string phone);
        bool validateAadhar(string aadhar);
        bool isAccountNumberUnique(string accNum);
        string encryptPassword(string password);
        string getCurrentDateTime();
};

// Validate email format
bool bankAccount::validateEmail(string email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    return (atPos != string::npos && dotPos != string::npos && 
            atPos > 0 && dotPos > atPos + 1 && dotPos < email.length() - 1);
}

// Validate phone number (10 digits)
bool bankAccount::validatePhone(string phone) {
    if (phone.length() != 10) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Validate Aadhar number (12 digits)
bool bankAccount::validateAadhar(string aadhar) {
    if (aadhar.length() != 12) return false;
    for (char c : aadhar) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Check if account number is unique
bool bankAccount::isAccountNumberUnique(string accNum) {
    ifstream inFile("accounts.txt");
    if (!inFile.is_open()) return true;
    
    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            string existingAccNum = line.substr(0, pos);
            if (existingAccNum == accNum) {
                inFile.close();
                return false;
            }
        }
    }
    inFile.close();
    return true;
}

// Simple password encryption (Caesar cipher)
string bankAccount::encryptPassword(string password) {
    string encrypted = "";
    for (char c : password) {
        encrypted += char(c + 3);
    }
    return encrypted;
}

// Get current date and time
string bankAccount::getCurrentDateTime() {
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

// Save account details to file
void bankAccount::savetoFile() {
    ofstream outFile("accounts.txt", ios::app);
    if (outFile.is_open()) {
        outFile << accountNumber << "|" << accountHolderName << "|" 
                << accountPassword << "|" << addharNumber << "|" 
                << email << "|" << phoneNumber << "|" << balance << endl;
        outFile.close();
    } else {
        cout << "Error: Unable to save account details!" << endl;
    }
}

// Main Menu
void bankAccount::mainMenu() {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "   WELCOME TO " << bankName << endl;
        cout << "========================================" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Login to Account" << endl;
        cout << "3. About Bank" << endl;
        cout << "4. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                createAccount();
                break;
            case 2:
                loginBankAccount();
                break;
            case 3:
                cout << "\n========================================" << endl;
                cout << "           ABOUT BANK" << endl;
                cout << "========================================" << endl;
                cout << "Bank Name: " << bankName << endl;
                cout << "Bank Code: " << bankcode << endl;
                cout << "Services: Account Management, Deposits," << endl;
                cout << "         Withdrawals, Money Transfers," << endl;
                cout << "         Interest Calculations" << endl;
                cout << "Version: 2.0 (Enhanced)" << endl;
                cout << "========================================" << endl;
                break;
            case 4:
                cout << "\nThank you for using " << bankName << "!" << endl;
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    } while(choice != 4);
}

// Create new account
void bankAccount::createAccount() {
    cout << "\n========================================" << endl;
    cout << "       CREATE NEW ACCOUNT" << endl;
    cout << "========================================" << endl;
    
    cin.ignore();
    cout << "Enter Account Holder Name: ";
    getline(cin, accountHolderName);
    
    cout << "Enter Account Number: ";
    getline(cin, accountNumber);
    
    // Validate unique account number
    if (!isAccountNumberUnique(accountNumber)) {
        cout << "\nError: Account number already exists!" << endl;
        return;
    }
    
    cout << "Enter Password (min 4 characters): ";
    getline(cin, accountPassword);
    
    if (accountPassword.length() < 4) {
        cout << "\nError: Password must be at least 4 characters!" << endl;
        return;
    }
    
    cout << "Enter Aadhar Number (12 digits): ";
    getline(cin, addharNumber);
    
    if (!validateAadhar(addharNumber)) {
        cout << "\nError: Invalid Aadhar number! Must be 12 digits." << endl;
        return;
    }
    
    cout << "Enter Email: ";
    getline(cin, email);
    
    if (!validateEmail(email)) {
        cout << "\nError: Invalid email format!" << endl;
        return;
    }
    
    cout << "Enter Phone Number (10 digits): ";
    getline(cin, phoneNumber);
    
    if (!validatePhone(phoneNumber)) {
        cout << "\nError: Invalid phone number! Must be 10 digits." << endl;
        return;
    }
    
    cout << "Enter Initial Deposit Amount (minimum $500): ";
    cin >> balance;
    
    if (balance < 500) {
        cout << "\nError: Minimum initial deposit is $500!" << endl;
        balance = 0;
        return;
    }
    
    // Encrypt password before saving
    accountPassword = encryptPassword(accountPassword);
    
    savetoFile();
    
    cout << "\n========================================" << endl;
    cout << "  Account Created Successfully!" << endl;
    cout << "========================================" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder: " << accountHolderName << endl;
    cout << "Initial Balance: $" << balance << endl;
    cout << "========================================" << endl;
}

// Login to bank account
void bankAccount::loginBankAccount() {
    string inputAccNum, inputPassword;
    bool found = false;
    
    cin.ignore();
    cout << "\n========================================" << endl;
    cout << "           LOGIN" << endl;
    cout << "========================================" << endl;
    cout << "Enter Account Number: ";
    getline(cin, inputAccNum);
    
    cout << "Enter Password: ";
    getline(cin, inputPassword);
    
    // Encrypt input password for comparison
    inputPassword = encryptPassword(inputPassword);
    
    ifstream inFile("accounts.txt");
    if (inFile.is_open()) {
        string line;
        
        while (getline(inFile, line)) {
            vector<string> tokens;
            string token;
            size_t start = 0;
            size_t pos = 0;
            
            // Split by pipe delimiter
            while ((pos = line.find('|', start)) != string::npos) {
                token = line.substr(start, pos - start);
                tokens.push_back(token);
                start = pos + 1;
            }
            tokens.push_back(line.substr(start));
            
            // Need exactly 7 fields
            if (tokens.size() == 7) {
                string accNum = tokens[0];
                string name = tokens[1];
                string password = tokens[2];
                string aadhar = tokens[3];
                string mail = tokens[4];
                string phone = tokens[5];
                double bal = stod(tokens[6]);
                
                if (accNum == inputAccNum && password == inputPassword) {
                    accountNumber = accNum;
                    accountHolderName = name;
                    accountPassword = password;
                    addharNumber = aadhar;
                    email = mail;
                    phoneNumber = phone;
                    balance = bal;
                    found = true;
                    break;
                }
            }
        }
        inFile.close();
        
        if (found) {
            cout << "\n========================================" << endl;
            cout << "  Login Successful!" << endl;
            cout << "  Welcome, " << accountHolderName << "!" << endl;
            cout << "========================================" << endl;
            
            int choice;
            do {
                cout << "\n========================================" << endl;
                cout << "         ACCOUNT MENU" << endl;
                cout << "========================================" << endl;
                cout << "1. Deposit Money" << endl;
                cout << "2. Withdraw Money" << endl;
                cout << "3. Transfer Money" << endl;
                cout << "4. Check Balance" << endl;
                cout << "5. Account Details" << endl;
                cout << "6. Transaction History" << endl;
                cout << "7. Generate Statement" << endl;
                cout << "8. Calculate Interest" << endl;
                cout << "9. Logout" << endl;
                cout << "========================================" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                
                switch(choice) {
                    case 1:
                        depositMoney();
                        break;
                    case 2:
                        withdrawMoney();
                        break;
                    case 3:
                        transferMoney();
                        break;
                    case 4:
                        checkBalance();
                        break;
                    case 5:
                        accountDetails();
                        break;
                    case 6:
                        allTransactionHistory();
                        break;
                    case 7:
                        generateAccountStatement();
                        break;
                    case 8:
                        calculateInterest();
                        break;
                    case 9:
                        cout << "\nLogging out..." << endl;
                        break;
                    default:
                        cout << "\nInvalid choice! Please try again." << endl;
                }
            } while(choice != 9);
        } else {
            cout << "\nError: Invalid Account Number or Password!" << endl;
        }
    } else {
        cout << "\nError: Unable to access account database!" << endl;
    }
}

// Deposit money
void bankAccount::depositMoney() {
    double amount;
    cout << "\n========================================" << endl;
    cout << "         DEPOSIT MONEY" << endl;
    cout << "========================================" << endl;
    cout << "Current Balance: $" << balance << endl;
    cout << "Enter amount to deposit: $";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "\nError: Invalid amount! Please enter a positive value." << endl;
        return;
    }
    
    balance += amount;
    
    // Update file
    vector<string> lines;
    ifstream inFile("accounts.txt");
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    
    ofstream outFile("accounts.txt");
    for (const string& l : lines) {
        if (l.find(accountNumber) != string::npos && l.find(accountPassword) != string::npos) {
            outFile << accountNumber << "|" << accountHolderName << "|" 
                    << accountPassword << "|" << addharNumber << "|" 
                    << email << "|" << phoneNumber << "|" << balance << endl;
        } else {
            outFile << l << endl;
        }
    }
    outFile.close();
    
    // Log transaction with timestamp
    ofstream transFile("transactions.txt", ios::app);
    if (transFile.is_open()) {
        transFile << getCurrentDateTime() << "|" << accountNumber << "|DEPOSIT|" 
                  << amount << "|" << balance << endl;
        transFile.close();
    }
    
    cout << "\n========================================" << endl;
    cout << "  Deposit Successful!" << endl;
    cout << "========================================" << endl;
    cout << "Deposited Amount: $" << amount << endl;
    cout << "New Balance: $" << balance << endl;
    cout << "========================================" << endl;
}

// Withdraw money
void bankAccount::withdrawMoney() {
    double amount;
    cout << "\n========================================" << endl;
    cout << "         WITHDRAW MONEY" << endl;
    cout << "========================================" << endl;
    cout << "Current Balance: $" << balance << endl;
    cout << "Enter amount to withdraw: $";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "\nError: Invalid amount! Please enter a positive value." << endl;
        return;
    }
    
    if (amount > balance) {
        cout << "\nError: Insufficient balance!" << endl;
        cout << "Available Balance: $" << balance << endl;
        return;
    }
    
    balance -= amount;
    
    // Update file
    vector<string> lines;
    ifstream inFile("accounts.txt");
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    
    ofstream outFile("accounts.txt");
    for (const string& l : lines) {
        if (l.find(accountNumber) != string::npos && l.find(accountPassword) != string::npos) {
            outFile << accountNumber << "|" << accountHolderName << "|" 
                    << accountPassword << "|" << addharNumber << "|" 
                    << email << "|" << phoneNumber << "|" << balance << endl;
        } else {
            outFile << l << endl;
        }
    }
    outFile.close();
    
    // Log transaction with timestamp
    ofstream transFile("transactions.txt", ios::app);
    if (transFile.is_open()) {
        transFile << getCurrentDateTime() << "|" << accountNumber << "|WITHDRAW|" 
                  << amount << "|" << balance << endl;
        transFile.close();
    }
    
    cout << "\n========================================" << endl;
    cout << "  Withdrawal Successful!" << endl;
    cout << "========================================" << endl;
    cout << "Withdrawn Amount: $" << amount << endl;
    cout << "New Balance: $" << balance << endl;
    cout << "========================================" << endl;
}

// Check balance
void bankAccount::checkBalance() {
    cout << "\n========================================" << endl;
    cout << "         BALANCE INQUIRY" << endl;
    cout << "========================================" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder: " << accountHolderName << endl;
    cout << "Current Balance: $" << balance << endl;
    cout << "========================================" << endl;
}

// Display account details
void bankAccount::accountDetails() {
    cout << "\n========================================" << endl;
    cout << "        ACCOUNT DETAILS" << endl;
    cout << "========================================" << endl;
    cout << "Bank Name: " << bankName << endl;
    cout << "Bank Code: " << bankcode << endl;
    cout << "Account Holder: " << accountHolderName << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Aadhar Number: " << addharNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Current Balance: $" << balance << endl;
    cout << "========================================" << endl;
}

// Display all transaction history
void bankAccount::allTransactionHistory() {
    cout << "\n========================================" << endl;
    cout << "      TRANSACTION HISTORY" << endl;
    cout << "========================================" << endl;
    
    ifstream transFile("transactions.txt");
    if (transFile.is_open()) {
        string line;
        bool found = false;
        
        while (getline(transFile, line)) {
            if (line.find(accountNumber) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }
        transFile.close();
        
        if (!found) {
            cout << "No transactions found for this account." << endl;
        }
    } else {
        cout << "No transaction history available." << endl;
    }
    cout << "========================================" << endl;
}

// Transfer money to another account
void bankAccount::transferMoney() {
    string recipientAccNum;
    double amount;
    
    cout << "\n========================================" << endl;
    cout << "         MONEY TRANSFER" << endl;
    cout << "========================================" << endl;
    cout << "Current Balance: $" << balance << endl;
    
    cin.ignore();
    cout << "Enter Recipient Account Number: ";
    getline(cin, recipientAccNum);
    
    if (recipientAccNum == accountNumber) {
        cout << "\nError: Cannot transfer to same account!" << endl;
        return;
    }
    
    // Check if recipient account exists
    ifstream inFile("accounts.txt");
    bool recipientExists = false;
    string recipientName;
    
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            vector<string> tokens;
            string token;
            size_t start = 0;
            size_t pos = 0;
            
            while ((pos = line.find('|', start)) != string::npos) {
                token = line.substr(start, pos - start);
                tokens.push_back(token);
                start = pos + 1;
            }
            tokens.push_back(line.substr(start));
            
            if (tokens.size() == 7 && tokens[0] == recipientAccNum) {
                recipientExists = true;
                recipientName = tokens[1];
                break;
            }
        }
        inFile.close();
    }
    
    if (!recipientExists) {
        cout << "\nError: Recipient account not found!" << endl;
        return;
    }
    
    cout << "Recipient Name: " << recipientName << endl;
    cout << "Enter amount to transfer: $";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "\nError: Invalid amount!" << endl;
        return;
    }
    
    if (amount > balance) {
        cout << "\nError: Insufficient balance!" << endl;
        return;
    }
    
    // Deduct from sender
    balance -= amount;
    
    // Update both accounts
    vector<string> lines;
    ifstream readFile("accounts.txt");
    string line;
    while (getline(readFile, line)) {
        lines.push_back(line);
    }
    readFile.close();
    
    ofstream outFile("accounts.txt");
    for (const string& l : lines) {
        vector<string> tokens;
        string token;
        size_t start = 0;
        size_t pos = 0;
        
        while ((pos = l.find('|', start)) != string::npos) {
            token = l.substr(start, pos - start);
            tokens.push_back(token);
            start = pos + 1;
        }
        tokens.push_back(l.substr(start));
        
        if (tokens.size() == 7) {
            if (tokens[0] == accountNumber) {
                outFile << accountNumber << "|" << accountHolderName << "|" 
                        << accountPassword << "|" << addharNumber << "|" 
                        << email << "|" << phoneNumber << "|" << balance << endl;
            } else if (tokens[0] == recipientAccNum) {
                double recipientBalance = stod(tokens[6]) + amount;
                outFile << tokens[0] << "|" << tokens[1] << "|" << tokens[2] << "|" 
                        << tokens[3] << "|" << tokens[4] << "|" << tokens[5] << "|" 
                        << recipientBalance << endl;
            } else {
                outFile << l << endl;
            }
        } else {
            outFile << l << endl;
        }
    }
    outFile.close();
    
    // Log transaction
    ofstream transFile("transactions.txt", ios::app);
    if (transFile.is_open()) {
        transFile << getCurrentDateTime() << "|" << accountNumber << "|TRANSFER TO " 
                  << recipientAccNum << "|" << amount << "|" << balance << endl;
        transFile << getCurrentDateTime() << "|" << recipientAccNum << "|TRANSFER FROM " 
                  << accountNumber << "|" << amount << "|" << (stod(line) + amount) << endl;
        transFile.close();
    }
    
    cout << "\n========================================" << endl;
    cout << "  Transfer Successful!" << endl;
    cout << "========================================" << endl;
    cout << "Transferred Amount: $" << amount << endl;
    cout << "Recipient: " << recipientName << endl;
    cout << "Your New Balance: $" << balance << endl;
    cout << "========================================" << endl;
}

// Generate detailed account statement
void bankAccount::generateAccountStatement() {
    cout << "\n========================================" << endl;
    cout << "      ACCOUNT STATEMENT" << endl;
    cout << "========================================" << endl;
    
    string filename = "statement_" + accountNumber + ".txt";
    ofstream statementFile(filename);
    
    if (statementFile.is_open()) {
        statementFile << "========================================" << endl;
        statementFile << "      " << bankName << endl;
        statementFile << "        ACCOUNT STATEMENT" << endl;
        statementFile << "========================================" << endl;
        statementFile << "Generated: " << getCurrentDateTime() << endl;
        statementFile << "Account Holder: " << accountHolderName << endl;
        statementFile << "Account Number: " << accountNumber << endl;
        statementFile << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
        statementFile << "========================================" << endl;
        statementFile << "\nTRANSACTION HISTORY:" << endl;
        statementFile << "========================================" << endl;
        
        ifstream transFile("transactions.txt");
        if (transFile.is_open()) {
            string line;
            bool found = false;
            
            while (getline(transFile, line)) {
                if (line.find(accountNumber) != string::npos) {
                    // Parse and format transaction
                    vector<string> tokens;
                    string token;
                    size_t start = 0;
                    size_t pos = 0;
                    
                    while ((pos = line.find('|', start)) != string::npos) {
                        token = line.substr(start, pos - start);
                        tokens.push_back(token);
                        start = pos + 1;
                    }
                    tokens.push_back(line.substr(start));
                    
                    if (tokens.size() >= 5) {
                        statementFile << "Date: " << tokens[0] << endl;
                        statementFile << "Type: " << tokens[2] << endl;
                        statementFile << "Amount: $" << tokens[3] << endl;
                        statementFile << "Balance: $" << tokens[4] << endl;
                        statementFile << "----------------------------------------" << endl;
                        found = true;
                    }
                }
            }
            transFile.close();
            
            if (!found) {
                statementFile << "No transactions found." << endl;
            }
        }
        
        statementFile << "========================================" << endl;
        statementFile << "      END OF STATEMENT" << endl;
        statementFile << "========================================" << endl;
        statementFile.close();
        
        cout << "Statement generated successfully!" << endl;
        cout << "File saved as: " << filename << endl;
    } else {
        cout << "Error generating statement!" << endl;
    }
    cout << "========================================" << endl;
}

// Calculate interest on savings
void bankAccount::calculateInterest() {
    cout << "\n========================================" << endl;
    cout << "      INTEREST CALCULATOR" << endl;
    cout << "========================================" << endl;
    cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    
    int months;
    double rate = 4.5; // 4.5% annual interest rate
    
    cout << "Enter number of months: ";
    cin >> months;
    
    if (months <= 0) {
        cout << "\nError: Invalid number of months!" << endl;
        return;
    }
    
    double interest = (balance * rate * months) / (12 * 100);
    double totalAmount = balance + interest;
    
    cout << "\n========================================" << endl;
    cout << "      INTEREST CALCULATION" << endl;
    cout << "========================================" << endl;
    cout << "Principal Amount: $" << fixed << setprecision(2) << balance << endl;
    cout << "Interest Rate: " << rate << "% per annum" << endl;
    cout << "Time Period: " << months << " months" << endl;
    cout << "Interest Earned: $" << fixed << setprecision(2) << interest << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    cout << "========================================" << endl;
    
    char addInterest;
    cout << "\nAdd interest to account? (y/n): ";
    cin >> addInterest;
    
    if (addInterest == 'y' || addInterest == 'Y') {
        balance += interest;
        
        // Update account file
        vector<string> lines;
        ifstream inFile("accounts.txt");
        string line;
        while (getline(inFile, line)) {
            lines.push_back(line);
        }
        inFile.close();
        
        ofstream outFile("accounts.txt");
        for (const string& l : lines) {
            if (l.find(accountNumber) != string::npos && l.find(accountPassword) != string::npos) {
                outFile << accountNumber << "|" << accountHolderName << "|" 
                        << accountPassword << "|" << addharNumber << "|" 
                        << email << "|" << phoneNumber << "|" << balance << endl;
            } else {
                outFile << l << endl;
            }
        }
        outFile.close();
        
        // Log transaction
        ofstream transFile("transactions.txt", ios::app);
        if (transFile.is_open()) {
            transFile << getCurrentDateTime() << "|" << accountNumber << "|INTEREST|" 
                      << interest << "|" << balance << endl;
            transFile.close();
        }
        
        cout << "\nInterest added successfully!" << endl;
        cout << "New Balance: $" << fixed << setprecision(2) << balance << endl;
    }
}

// Main function
int main() {
    bankAccount bank;
    bank.mainMenu();
    return 0;
}

// g++ BankAccount.cpp -o BankAccount
// BankAccount.exe