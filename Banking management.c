
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached!\n");
        return;
    }
    printf("Enter account holder name: ");
    getchar(); // Clear input buffer
    fgets(accounts[accountCount].name, sizeof(accounts[accountCount].name), stdin);
    accounts[accountCount].name[strcspn(accounts[accountCount].name, "\n")] = 0; // Remove newline
    accounts[accountCount].accountNumber = 1000 + accountCount;
    accounts[accountCount].balance = 0;
    printf("Account created successfully! Account Number: %d\n", accounts[accountCount].accountNumber);
    accountCount++;
}

int findAccount(int accNum) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum) return i;
    }
    return -1;
}

void balanceInquiry() {
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    int index = findAccount(accNum);
    if (index == -1) {
        printf("Account not found!\n");
    } else {
        printf("Account Holder: %s\nBalance: $%.2f\n", accounts[index].name, accounts[index].balance);
    }
}

void deposit() {
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    int index = findAccount(accNum);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid deposit amount!\n");
        return;
    }
    accounts[index].balance += amount;
    printf("Deposit successful! New Balance: $%.2f\n", accounts[index].balance);
}

void withdraw() {
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);
    int index = findAccount(accNum);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > accounts[index].balance) {
        printf("Invalid withdrawal amount!\n");
        return;
    }
    accounts[index].balance -= amount;
    printf("Withdrawal successful! New Balance: $%.2f\n", accounts[index].balance);
}

void transfer() {
    int fromAcc, toAcc, fromIndex, toIndex;
    float amount;
    printf("Enter your account number: ");
    scanf("%d", &fromAcc);
    fromIndex = findAccount(fromAcc);
    if (fromIndex == -1) {
        printf("Source account not found!\n");
        return;
    }
    printf("Enter recipient account number: ");
    scanf("%d", &toAcc);
    toIndex = findAccount(toAcc);
    if (toIndex == -1) {
        printf("Recipient account not found!\n");
        return;
    }
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > accounts[fromIndex].balance) {
        printf("Invalid transfer amount!\n");
        return;
    }
    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;
    printf("Transfer successful! New Balance: $%.2f\n", accounts[fromIndex].balance);
}

void menu() {
    int choice;
    do {
        printf("\nBanking Management System\n");
        printf("1. Create Account\n2. Balance Inquiry\n3. Deposit\n4. Withdraw\n5. Transfer\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(); break;
            case 2: balanceInquiry(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: transfer(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
