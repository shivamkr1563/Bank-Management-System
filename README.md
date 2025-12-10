# 🏦 Bank Management System

A comprehensive **C++ Banking Application** with advanced features including money transfers, interest calculations, account statement generation, and secure password encryption.

## 📋 Table of Contents
- [Features](#features)
- [Technologies Used](#technologies-used)
- [System Requirements](#system-requirements)
- [Installation & Setup](#installation--setup)
- [How to Use](#how-to-use)
- [Project Structure](#project-structure)
- [Key Highlights](#key-highlights)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

### Core Banking Operations
- ✅ **Account Creation** - Register new accounts with validation
- ✅ **Secure Login** - Password-protected authentication with encryption
- ✅ **Deposit Money** - Add funds to your account
- ✅ **Withdraw Money** - Withdraw with balance validation
- ✅ **Money Transfer** - Transfer funds between accounts
- ✅ **Balance Inquiry** - Check current account balance

### Advanced Features
- 📊 **Account Statement Generation** - Export detailed transaction history to file
- 💰 **Interest Calculator** - Calculate and add interest to savings account
- 📝 **Transaction History** - View all past transactions with timestamps
- 🔐 **Password Encryption** - Caesar cipher encryption for security
- ✔️ **Input Validation** - Email, phone, Aadhar number validation
- 🔒 **Unique Account Numbers** - Prevents duplicate account creation

## 🛠️ Technologies Used

### Backend (C++)
- **Language:** C++
- **Libraries:** 
  - `<iostream>` - Input/Output operations
  - `<fstream>` - File handling
  - `<string>` - String manipulation
  - `<vector>` - Dynamic arrays
  - `<ctime>` - Date and time operations
  - `<iomanip>` - Output formatting
- **Data Storage:** Text files (accounts.txt, transactions.txt)
- **Compiler:** G++ (MinGW)

### Frontend (Web)
- **HTML5** - Structure and markup
- **CSS3** - Modern styling with Flexbox/Grid
- **JavaScript (ES6)** - Client-side logic
- **Font Awesome** - Icon library
- **localStorage** - Browser-based data persistence

## 💻 System Requirements

- **Operating System:** Windows/Linux/MacOS
- **Compiler:** G++ compiler (MinGW for Windows)
- **RAM:** Minimum 512 MB
- **Storage:** 10 MB free space

## 🚀 Installation & Setup

### Option 1: Console Application (C++)

#### 1. Clone or Download the Repository
```bash
git clone <repository-url>
cd "Bank Management System"
```

#### 2. Compile the Program
```bash
g++ BankAccount.cpp -o BankAccount
```

#### 3. Run the Application
**Windows:**
```bash
BankAccount.exe
```

**Linux/Mac:**
```bash
./BankAccount
```

### Option 2: Web Application (Frontend)

#### Method 1: Direct Browser Access
1. Navigate to `frontend` folder
2. Double-click `index.html`
3. Start using the web interface!

#### Method 2: Local Development Server
```bash
# Using Python
cd frontend
python -m http.server 8000

# Using Node.js
npx http-server frontend -p 8000
```

Then open: `http://localhost:8000`

#### Method 3: VS Code Live Server
1. Install "Live Server" extension in VS Code
2. Right-click `index.html`
3. Select "Open with Live Server"

## 📖 How to Use

### Creating a New Account
1. Select option `1` from the main menu
2. Enter account holder name
3. Choose a unique account number
4. Set a password (minimum 4 characters)
5. Provide Aadhar number (12 digits)
6. Enter valid email address
7. Enter phone number (10 digits)
8. Make initial deposit (minimum $500)

### Logging In
1. Select option `2` from the main menu
2. Enter your account number
3. Enter your password
4. Access your account dashboard

### Available Operations After Login
- **Deposit Money** - Add funds to your account
- **Withdraw Money** - Remove funds (with balance check)
- **Transfer Money** - Send money to another account
- **Check Balance** - View current balance
- **Account Details** - See complete account information
- **Transaction History** - View all past transactions
- **Generate Statement** - Export transactions to file
- **Calculate Interest** - Calculate interest on savings

## 📁 Project Structure

```
Bank Management System/
│
├── BankAccount.cpp          # C++ Console Application
├── README.md                # Project documentation
├── accounts.txt             # Account data storage (auto-generated)
├── transactions.txt         # Transaction logs (auto-generated)
├── statement_XXXXX.txt      # Generated account statements
│
└── frontend/                # Web Frontend
    ├── index.html           # Login & landing page
    ├── register.html        # Account registration page
    ├── dashboard.html       # Main dashboard
    ├── style.css           # All styling
    ├── script.js           # JavaScript logic
    └── README.md           # Frontend documentation
```

## 🎯 Key Highlights

### Security Features
- ✅ Password encryption using Caesar cipher
- ✅ Login authentication system
- ✅ Account number uniqueness validation
- ✅ Secure file-based data storage

### Validation Mechanisms
- ✅ Email format validation (contains @ and .)
- ✅ Phone number validation (exactly 10 digits)
- ✅ Aadhar validation (exactly 12 digits)
- ✅ Password length check (minimum 4 characters)
- ✅ Minimum deposit requirement ($500)
- ✅ Insufficient balance checks

### Professional Features
- ✅ Timestamped transactions
- ✅ Detailed transaction logs
- ✅ Account statement export
- ✅ Interest calculation and application
- ✅ Money transfer between accounts
- ✅ Formatted output with proper alignment

## 🔮 Future Enhancements

### Backend
- [ ] Add loan management system
- [ ] Implement fixed deposit accounts
- [ ] Add admin panel for bank management
- [ ] Integrate database (MySQL/SQLite)
- [ ] Implement stronger encryption (AES, SHA-256)
- [ ] REST API for frontend-backend communication

### Frontend
- [ ] Backend API integration
- [ ] Real-time notifications
- [ ] Dark mode theme
- [ ] Multi-language support
- [ ] PDF statement generation
- [ ] Bill payments feature
- [ ] Credit card management
- [ ] Mobile responsive improvements
- [ ] Progressive Web App (PWA)
- [ ] SMS/Email notifications

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 👨‍💻 Author

**Shivam Kumar**
- Email: shivam124@gmail.com
- GitHub: [Your GitHub Profile]

## 📞 Support

For any queries or issues, please open an issue on GitHub or contact via email.

---

⭐ **If you like this project, please give it a star!** ⭐

---

## 📸 Screenshots

### Main Menu
```
========================================
   WELCOME TO SCBOI+bankCode
========================================
1. Create New Account
2. Login to Account
3. About Bank
4. Exit
========================================
```

### Account Dashboard
```
========================================
         ACCOUNT MENU
========================================
1. Deposit Money
2. Withdraw Money
3. Transfer Money
4. Check Balance
5. Account Details
6. Transaction History
7. Generate Statement
8. Calculate Interest
9. Logout
========================================
```

---

**Made with ❤️ using C++**
