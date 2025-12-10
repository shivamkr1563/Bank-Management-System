// Local Storage Keys
const STORAGE_KEY = 'bankAccounts';
const TRANSACTION_KEY = 'bankTransactions';
const CURRENT_USER_KEY = 'currentUser';

// Utility Functions
function showMessage(elementId, message, type = 'success') {
    const messageEl = document.getElementById(elementId);
    if (messageEl) {
        messageEl.textContent = message;
        messageEl.className = `message ${type}`;
        messageEl.style.display = 'block';
        setTimeout(() => {
            messageEl.style.display = 'none';
        }, 5000);
    }
}

function validateEmail(email) {
    const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return re.test(email);
}

function validatePhone(phone) {
    return phone.length === 10 && /^\d+$/.test(phone);
}

function validateAadhar(aadhar) {
    return aadhar.length === 12 && /^\d+$/.test(aadhar);
}

function encryptPassword(password) {
    return btoa(password); // Simple base64 encoding
}

function decryptPassword(encrypted) {
    return atob(encrypted);
}

function getCurrentDateTime() {
    return new Date().toLocaleString();
}

function formatCurrency(amount) {
    return `$${parseFloat(amount).toFixed(2)}`;
}

// Storage Functions
function getAccounts() {
    const accounts = localStorage.getItem(STORAGE_KEY);
    return accounts ? JSON.parse(accounts) : [];
}

function saveAccounts(accounts) {
    localStorage.setItem(STORAGE_KEY, JSON.stringify(accounts));
}

function getTransactions() {
    const transactions = localStorage.getItem(TRANSACTION_KEY);
    return transactions ? JSON.parse(transactions) : [];
}

function saveTransaction(transaction) {
    const transactions = getTransactions();
    transactions.push(transaction);
    localStorage.setItem(TRANSACTION_KEY, JSON.stringify(transactions));
}

function getCurrentUser() {
    const user = localStorage.getItem(CURRENT_USER_KEY);
    return user ? JSON.parse(user) : null;
}

function setCurrentUser(user) {
    localStorage.setItem(CURRENT_USER_KEY, JSON.stringify(user));
}

function clearCurrentUser() {
    localStorage.removeItem(CURRENT_USER_KEY);
}

// Navigation Functions
function showRegisterForm() {
    window.location.href = 'register.html';
}

function logout() {
    if (confirm('Are you sure you want to logout?')) {
        clearCurrentUser();
        window.location.href = 'index.html';
    }
}

// Index Page - Login Form
if (document.getElementById('loginForm')) {
    document.getElementById('loginForm').addEventListener('submit', function(e) {
        e.preventDefault();
        
        const accountNumber = document.getElementById('loginAccNum').value.trim();
        const password = document.getElementById('loginPassword').value;
        
        if (!accountNumber || !password) {
            alert('Please fill in all fields');
            return;
        }
        
        const accounts = getAccounts();
        const encryptedPass = encryptPassword(password);
        const account = accounts.find(acc => 
            acc.accountNumber === accountNumber && acc.password === encryptedPass
        );
        
        if (account) {
            setCurrentUser(account);
            window.location.href = 'dashboard.html';
        } else {
            alert('Invalid account number or password!');
        }
    });
}

// Register Page - Registration Form
if (document.getElementById('registerForm')) {
    document.getElementById('registerForm').addEventListener('submit', function(e) {
        e.preventDefault();
        
        const accountHolderName = document.getElementById('accountHolderName').value.trim();
        const accountNumber = document.getElementById('accountNumber').value.trim();
        const accountPassword = document.getElementById('accountPassword').value;
        const aadharNumber = document.getElementById('aadharNumber').value.trim();
        const phoneNumber = document.getElementById('phoneNumber').value.trim();
        const email = document.getElementById('email').value.trim();
        const initialDeposit = parseFloat(document.getElementById('initialDeposit').value);
        
        // Validation
        if (!accountHolderName || !accountNumber || !accountPassword || 
            !aadharNumber || !phoneNumber || !email || !initialDeposit) {
            showMessage('registerMessage', 'Please fill in all fields!', 'error');
            return;
        }
        
        if (accountPassword.length < 4) {
            showMessage('registerMessage', 'Password must be at least 4 characters!', 'error');
            return;
        }
        
        if (!validateAadhar(aadharNumber)) {
            showMessage('registerMessage', 'Invalid Aadhar number! Must be 12 digits.', 'error');
            return;
        }
        
        if (!validateEmail(email)) {
            showMessage('registerMessage', 'Invalid email format!', 'error');
            return;
        }
        
        if (!validatePhone(phoneNumber)) {
            showMessage('registerMessage', 'Invalid phone number! Must be 10 digits.', 'error');
            return;
        }
        
        if (initialDeposit < 500) {
            showMessage('registerMessage', 'Minimum initial deposit is $500!', 'error');
            return;
        }
        
        // Check unique account number
        const accounts = getAccounts();
        if (accounts.some(acc => acc.accountNumber === accountNumber)) {
            showMessage('registerMessage', 'Account number already exists!', 'error');
            return;
        }
        
        // Create new account
        const newAccount = {
            accountHolderName,
            accountNumber,
            password: encryptPassword(accountPassword),
            aadharNumber,
            phoneNumber,
            email,
            balance: initialDeposit,
            createdAt: getCurrentDateTime()
        };
        
        accounts.push(newAccount);
        saveAccounts(accounts);
        
        // Log initial deposit transaction
        saveTransaction({
            accountNumber,
            type: 'DEPOSIT',
            amount: initialDeposit,
            balance: initialDeposit,
            timestamp: getCurrentDateTime(),
            description: 'Initial Deposit'
        });
        
        showMessage('registerMessage', 
            `Account created successfully! Account Number: ${accountNumber}`, 'success');
        
        setTimeout(() => {
            window.location.href = 'index.html';
        }, 2000);
    });
}

// Dashboard Functions
function showSection(sectionId) {
    // Hide all sections
    document.querySelectorAll('.dashboard-section').forEach(section => {
        section.classList.remove('active');
    });
    
    // Show selected section
    document.getElementById(sectionId).classList.add('active');
    
    // Update nav active state
    document.querySelectorAll('.nav-menu a').forEach(link => {
        link.classList.remove('active');
    });
    event.target.classList.add('active');
    
    // Update balance displays
    const user = getCurrentUser();
    if (user) {
        if (document.getElementById('depositBalance')) {
            document.getElementById('depositBalance').value = formatCurrency(user.balance);
        }
        if (document.getElementById('withdrawBalance')) {
            document.getElementById('withdrawBalance').value = formatCurrency(user.balance);
        }
        if (document.getElementById('transferBalance')) {
            document.getElementById('transferBalance').value = formatCurrency(user.balance);
        }
        if (document.getElementById('interestBalance')) {
            document.getElementById('interestBalance').value = formatCurrency(user.balance);
        }
    }
}

function loadDashboard() {
    const user = getCurrentUser();
    
    if (!user) {
        window.location.href = 'index.html';
        return;
    }
    
    // Update user info
    document.getElementById('userName').textContent = `Welcome, ${user.accountHolderName}`;
    document.getElementById('currentBalance').textContent = formatCurrency(user.balance);
    document.getElementById('accountNum').textContent = user.accountNumber;
    
    // Load transactions
    const transactions = getTransactions().filter(t => t.accountNumber === user.accountNumber);
    document.getElementById('totalTransactions').textContent = transactions.length;
    
    // Load recent transactions
    loadRecentTransactions();
    
    // Load profile
    loadProfile();
}

function loadRecentTransactions() {
    const user = getCurrentUser();
    const transactions = getTransactions()
        .filter(t => t.accountNumber === user.accountNumber)
        .slice(-5)
        .reverse();
    
    const listEl = document.getElementById('recentTransList');
    
    if (transactions.length === 0) {
        listEl.innerHTML = '<p class="no-data">No recent transactions</p>';
        return;
    }
    
    listEl.innerHTML = transactions.map(t => `
        <div class="trans-item ${t.type.toLowerCase()}">
            <div>
                <strong>${t.type}</strong>
                <p>${t.timestamp}</p>
                ${t.description ? `<p><small>${t.description}</small></p>` : ''}
            </div>
            <div>
                <strong>${formatCurrency(t.amount)}</strong>
                <p>Balance: ${formatCurrency(t.balance)}</p>
            </div>
        </div>
    `).join('');
}

function loadTransactionHistory() {
    const user = getCurrentUser();
    const transactions = getTransactions()
        .filter(t => t.accountNumber === user.accountNumber)
        .reverse();
    
    const historyEl = document.getElementById('transactionHistory');
    
    if (transactions.length === 0) {
        historyEl.innerHTML = '<p class="no-data">No transactions found</p>';
        return;
    }
    
    historyEl.innerHTML = `
        <table>
            <thead>
                <tr>
                    <th>Date & Time</th>
                    <th>Type</th>
                    <th>Amount</th>
                    <th>Balance</th>
                    <th>Description</th>
                </tr>
            </thead>
            <tbody>
                ${transactions.map(t => `
                    <tr>
                        <td>${t.timestamp}</td>
                        <td>${t.type}</td>
                        <td>${formatCurrency(t.amount)}</td>
                        <td>${formatCurrency(t.balance)}</td>
                        <td>${t.description || '-'}</td>
                    </tr>
                `).join('')}
            </tbody>
        </table>
    `;
}

function loadProfile() {
    const user = getCurrentUser();
    
    document.getElementById('profileName').textContent = user.accountHolderName;
    document.getElementById('profileAccNum').textContent = user.accountNumber;
    document.getElementById('profileEmail').textContent = user.email;
    document.getElementById('profilePhone').textContent = user.phoneNumber;
    document.getElementById('profileAadhar').textContent = user.aadharNumber;
    document.getElementById('profileBalance').textContent = formatCurrency(user.balance);
}

function updateAccountBalance(newBalance) {
    const user = getCurrentUser();
    user.balance = newBalance;
    
    // Update in storage
    const accounts = getAccounts();
    const index = accounts.findIndex(acc => acc.accountNumber === user.accountNumber);
    if (index !== -1) {
        accounts[index].balance = newBalance;
        saveAccounts(accounts);
    }
    
    // Update current user
    setCurrentUser(user);
    
    // Refresh display
    document.getElementById('currentBalance').textContent = formatCurrency(newBalance);
    loadRecentTransactions();
    loadProfile();
}

// Deposit Form
if (document.getElementById('depositForm')) {
    document.getElementById('depositForm').addEventListener('submit', function(e) {
        e.preventDefault();
        
        const user = getCurrentUser();
        const amount = parseFloat(document.getElementById('depositAmount').value);
        
        if (amount <= 0) {
            showMessage('depositMessage', 'Invalid amount!', 'error');
            return;
        }
        
        const newBalance = user.balance + amount;
        updateAccountBalance(newBalance);
        
        saveTransaction({
            accountNumber: user.accountNumber,
            type: 'DEPOSIT',
            amount: amount,
            balance: newBalance,
            timestamp: getCurrentDateTime(),
            description: 'Cash Deposit'
        });
        
        showMessage('depositMessage', 
            `Successfully deposited ${formatCurrency(amount)}! New balance: ${formatCurrency(newBalance)}`, 
            'success');
        
        document.getElementById('depositAmount').value = '';
        document.getElementById('depositBalance').value = formatCurrency(newBalance);
    });
}

// Withdraw Form
if (document.getElementById('withdrawForm')) {
    document.getElementById('withdrawForm').addEventListener('submit', function(e) {
        e.preventDefault();
        
        const user = getCurrentUser();
        const amount = parseFloat(document.getElementById('withdrawAmount').value);
        
        if (amount <= 0) {
            showMessage('withdrawMessage', 'Invalid amount!', 'error');
            return;
        }
        
        if (amount > user.balance) {
            showMessage('withdrawMessage', 
                `Insufficient balance! Available: ${formatCurrency(user.balance)}`, 
                'error');
            return;
        }
        
        const newBalance = user.balance - amount;
        updateAccountBalance(newBalance);
        
        saveTransaction({
            accountNumber: user.accountNumber,
            type: 'WITHDRAW',
            amount: amount,
            balance: newBalance,
            timestamp: getCurrentDateTime(),
            description: 'Cash Withdrawal'
        });
        
        showMessage('withdrawMessage', 
            `Successfully withdrawn ${formatCurrency(amount)}! New balance: ${formatCurrency(newBalance)}`, 
            'success');
        
        document.getElementById('withdrawAmount').value = '';
        document.getElementById('withdrawBalance').value = formatCurrency(newBalance);
    });
}

// Transfer Form
if (document.getElementById('transferForm')) {
    document.getElementById('transferForm').addEventListener('submit', function(e) {
        e.preventDefault();
        
        const user = getCurrentUser();
        const recipientAccNum = document.getElementById('recipientAccount').value.trim();
        const amount = parseFloat(document.getElementById('transferAmount').value);
        
        if (recipientAccNum === user.accountNumber) {
            showMessage('transferMessage', 'Cannot transfer to same account!', 'error');
            return;
        }
        
        if (amount <= 0) {
            showMessage('transferMessage', 'Invalid amount!', 'error');
            return;
        }
        
        if (amount > user.balance) {
            showMessage('transferMessage', 
                `Insufficient balance! Available: ${formatCurrency(user.balance)}`, 
                'error');
            return;
        }
        
        // Find recipient
        const accounts = getAccounts();
        const recipientIndex = accounts.findIndex(acc => acc.accountNumber === recipientAccNum);
        
        if (recipientIndex === -1) {
            showMessage('transferMessage', 'Recipient account not found!', 'error');
            return;
        }
        
        const recipient = accounts[recipientIndex];
        
        // Update balances
        const newSenderBalance = user.balance - amount;
        const newRecipientBalance = recipient.balance + amount;
        
        // Update sender
        updateAccountBalance(newSenderBalance);
        
        // Update recipient
        accounts[recipientIndex].balance = newRecipientBalance;
        saveAccounts(accounts);
        
        // Log transactions
        saveTransaction({
            accountNumber: user.accountNumber,
            type: 'TRANSFER',
            amount: amount,
            balance: newSenderBalance,
            timestamp: getCurrentDateTime(),
            description: `Transfer to ${recipientAccNum}`
        });
        
        saveTransaction({
            accountNumber: recipientAccNum,
            type: 'TRANSFER',
            amount: amount,
            balance: newRecipientBalance,
            timestamp: getCurrentDateTime(),
            description: `Transfer from ${user.accountNumber}`
        });
        
        showMessage('transferMessage', 
            `Successfully transferred ${formatCurrency(amount)} to ${recipient.accountHolderName}!`, 
            'success');
        
        document.getElementById('recipientAccount').value = '';
        document.getElementById('transferAmount').value = '';
        document.getElementById('transferBalance').value = formatCurrency(newSenderBalance);
    });
}

// Interest Calculator
function calculateInterest() {
    const user = getCurrentUser();
    const months = parseInt(document.getElementById('interestMonths').value);
    
    if (!months || months <= 0) {
        alert('Please enter valid number of months');
        return;
    }
    
    const rate = 4.5; // 4.5% annual
    const interest = (user.balance * rate * months) / (12 * 100);
    const totalAmount = user.balance + interest;
    
    const resultEl = document.getElementById('interestResult');
    resultEl.innerHTML = `
        <h4>Interest Calculation Result</h4>
        <p><span>Principal Amount:</span> <strong>${formatCurrency(user.balance)}</strong></p>
        <p><span>Interest Rate:</span> <strong>${rate}% per annum</strong></p>
        <p><span>Time Period:</span> <strong>${months} months</strong></p>
        <p><span>Interest Earned:</span> <strong style="color: var(--success-color)">${formatCurrency(interest)}</strong></p>
        <p><span>Total Amount:</span> <strong>${formatCurrency(totalAmount)}</strong></p>
        <button onclick="addInterest(${interest})" class="btn btn-primary" style="margin-top: 15px;">
            <i class="fas fa-plus"></i> Add Interest to Account
        </button>
    `;
    resultEl.classList.add('show');
}

function addInterest(interest) {
    const user = getCurrentUser();
    const newBalance = user.balance + interest;
    
    updateAccountBalance(newBalance);
    
    saveTransaction({
        accountNumber: user.accountNumber,
        type: 'INTEREST',
        amount: interest,
        balance: newBalance,
        timestamp: getCurrentDateTime(),
        description: 'Interest Credit'
    });
    
    showMessage('interestMessage', 
        `Interest of ${formatCurrency(interest)} added successfully!`, 
        'success');
    
    document.getElementById('interestMonths').value = '';
    document.getElementById('interestResult').classList.remove('show');
    document.getElementById('interestBalance').value = formatCurrency(newBalance);
}

// Generate Statement
function generateStatement() {
    const user = getCurrentUser();
    const transactions = getTransactions()
        .filter(t => t.accountNumber === user.accountNumber);
    
    let statement = `
========================================
      SCBOI BANK - ACCOUNT STATEMENT
========================================
Generated: ${getCurrentDateTime()}
Account Holder: ${user.accountHolderName}
Account Number: ${user.accountNumber}
Current Balance: ${formatCurrency(user.balance)}
========================================

TRANSACTION HISTORY:
========================================
`;
    
    transactions.forEach(t => {
        statement += `
Date: ${t.timestamp}
Type: ${t.type}
Amount: ${formatCurrency(t.amount)}
Balance: ${formatCurrency(t.balance)}
${t.description ? 'Description: ' + t.description : ''}
----------------------------------------
`;
    });
    
    statement += `
========================================
        END OF STATEMENT
========================================
`;
    
    // Create download
    const blob = new Blob([statement], { type: 'text/plain' });
    const url = window.URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = `statement_${user.accountNumber}_${Date.now()}.txt`;
    a.click();
    
    showMessage('statementMessage', 'Statement generated and downloaded!', 'success');
}

// Initialize dashboard on load
if (window.location.pathname.includes('dashboard.html')) {
    window.onload = function() {
        loadDashboard();
        
        // Load transaction history when that section is active
        const historySection = document.getElementById('history');
        const observer = new MutationObserver(function(mutations) {
            mutations.forEach(function(mutation) {
                if (mutation.target.classList.contains('active') && 
                    mutation.target.id === 'history') {
                    loadTransactionHistory();
                }
            });
        });
        
        observer.observe(historySection, { attributes: true });
    };
}
