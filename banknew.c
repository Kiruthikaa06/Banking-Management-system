#include <stdio.h>
#include <stdlib.h>

/* ---------- STRUCTURES ---------- */
struct bank {
    int accno;
    int pin;
    float balance;
    int active;     // 1 = active, 0 = deleted
};

struct credit {
    int accno;
    float amount;
    char type[15];   // Deposit / Withdraw / Transfer
};

/* ---------- GLOBAL DATA ---------- */
struct bank b[10];
int n = 0;

/* ---------- FUNCTION DECLARATIONS ---------- */
void loadClients();
void saveClients();
void saveAccountsText();
void saveCredit(int accno, float amt, char type[]);

int findAccount(int acc);

/* ---------- FILE FUNCTIONS ---------- */

/* Load client.dat data into array */
void loadClients() {
    FILE *fp = fopen("client.dat", "rb");
    if (fp == NULL) return;

    n = fread(b, sizeof(struct bank), 10, fp);
    fclose(fp);
}

/* Save array data into client.dat */
void saveClients() {
    FILE *fp = fopen("client.dat", "wb");
    fwrite(b, sizeof(struct bank), n, fp);
    fclose(fp);

    saveAccountsText();   // also update text file
}

/* Save readable account details into accounts.txt */
void saveAccountsText() {
    FILE *fp = fopen("accounts.txt", "w");
    int i;

    fprintf(fp, "ACCOUNT SUMMARY\n");
    fprintf(fp, "-------------------------\n");

    for (i = 0; i < n; i++) {
        if (b[i].active == 1) {
            fprintf(fp, "Acc No: %d | Balance: %.2f\n",
                    b[i].accno, b[i].balance);
        }
    }
    fclose(fp);
}

/* Save transaction into credit.dat */
void saveCredit(int accno, float amt, char type[]) {
    FILE *fp = fopen("credit.dat", "ab");
    struct credit c;

    c.accno = accno;
    c.amount = amt;
    sprintf(c.type, "%s", type);

    fwrite(&c, sizeof(struct credit), 1, fp);
    fclose(fp);
}

/* ---------- LOGIC FUNCTIONS ---------- */

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

    saveClients();
    printf("Account Created Successfully\n");
}

/* Deposit Money */
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
    saveCredit(acc, amt, "Deposit");
    saveClients();

    printf("Deposit Successful\n");
}

/* Withdraw Money */
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

    if (amt > b[i].balance) {
        printf("Insufficient Balance\n");
        return;
    }

    b[i].balance -= amt;
    saveCredit(acc, amt, "Withdraw");
    saveClients();

    printf("Withdraw Successful\n");
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

    printf("Available Balance: %.2f\n", b[i].balance);
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
    saveClients();

    printf("PIN Changed Successfully\n");
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

    saveCredit(from, amt, "Transfer");
    saveClients();

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
    saveClients();

    printf("Account Deleted Successfully\n");
}

/* ---------- MAIN ---------- */
int main() {
    int choice;

    loadClients();   // load data at start

    do {
        printf("\n------ BANK MENU ------");
        printf("\n1. Create Account");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Check Balance");
        printf("\n5. Change PIN");
        printf("\n6. Transfer Money");
        printf("\n7. Mini Statement");
        printf("\n8. Delete Account");
        printf("\n9. Exit");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: changePIN(); break;
            case 6: transfer(); break;
            case 7: miniStatement(); break;
            case 8: deleteAccount(); break;
            case 9: printf("Thank You!\n"); break;
            default: printf("Invalid Choice\n");
        }
    } while (choice != 9);

    return 0;
}
