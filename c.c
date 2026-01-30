#include <stdio.h>

struct bank {
    int accno;
    int pin;
    float balance;
    int active;     // 1 = active, 0 = deleted
};

struct bank b[10];
int n = 0;

/* Find account index */
int findAccount(int acc) {
    int i;
    for (i = 0; i < n; i++) {
        if (b[i].accno == acc && b[i].active == 1)
            return i;
    }
    return -1;
}

/* Create Account */
void create() {
    printf("Enter Account Number: ");
    scanf("%d", &b[n].accno);

    printf("Set PIN: ");
    scanf("%d", &b[n].pin);

    printf("Enter Initial Balance: ");
    scanf("%f", &b[n].balance);

    b[n].active = 1;
    n++;

    printf("Account Created Successfully\n");
}

/* Deposit */
void deposit() {
    int acc, i;
    float amt;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%f", &amt);

    b[i].balance += amt;
    printf("Deposit Successful\n");
}

/* Withdraw */
void withdraw() {
    int acc, i;
    float amt;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%f", &amt);

    if (amt > b[i].balance)
        printf("Insufficient Balance\n");
    else {
        b[i].balance -= amt;
        printf("Withdraw Successful\n");
    }
}

/* Check Balance */
void checkBalance() {
    int acc, i;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    printf("Balance: %.2f\n", b[i].balance);
}

/* Change PIN */
void changePIN() {
    int acc, i, newpin;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    printf("Enter New PIN: ");
    scanf("%d", &newpin);

    b[i].pin = newpin;
    printf("PIN Changed\n");
}

/* Transfer Money */
void transfer() {
    int from, to, i, j;
    float amt;

    printf("From Account: ");
    scanf("%d", &from);
    printf("To Account: ");
    scanf("%d", &to);

    i = findAccount(from);
    j = findAccount(to);

    if (i == -1 || j == -1) {
        printf("Invalid Account\n");
        return;
    }

    printf("Enter Amount: ");
    scanf("%f", &amt);

    if (amt > b[i].balance) {
        printf("Insufficient Balance\n");
        return;
    }

    b[i].balance -= amt;
    b[j].balance += amt;

    printf("Transfer Successful\n");
}

/* Mini Statement */
void miniStatement() {
    int acc, i;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    printf("Account No: %d\n", b[i].accno);
    printf("Balance: %.2f\n", b[i].balance);
}

/* Unlock Account (simple) */
void unlock() {
    int acc, i;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    printf("Account Unlocked\n");
}

/* Delete Account */
void deleteAccount() {
    int acc, i;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    i = findAccount(acc);
    if (i == -1) {
        printf("Account Not Found\n");
        return;
    }

    b[i].active = 0;
    printf("Account Deleted\n");
}

/* MAIN */
int main() {
    int choice;

    do {
        printf("\n------ BANK MENU ------");
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Check Balance");
        printf("\n5. Change PIN");
        printf("\n6. Transfer Money");
        printf("\n7. Mini Statement");
        printf("\n8. Unlock Account");
        printf("\n9. Delete Account");
        printf("\n10. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: changePIN(); break;
            case 6: transfer(); break;

            case 7: miniStatement(); break;
            case 8: unlock(); break;
            case 9: deleteAccount(); break;
            case 10: printf("Thank You!\n"); break;
            default: printf("Invalid Choice\n");
        }
    } while (choice != 10);

    return 0;
// }#Banking-Management-system
// This program is a banking management system developed using the C programming language
