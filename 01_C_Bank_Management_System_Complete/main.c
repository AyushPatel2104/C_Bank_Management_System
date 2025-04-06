#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    int acc_no;
    char name[50];
    float balance;
};

// Function Prototypes
void create_account(struct account **accounts, int *count);
void view_all_accounts(struct account *accounts, int count);
void deposit_money(struct account *accounts, int count);
void withdraw_money(struct account *accounts, int count);
void search_account(struct account *accounts, int count);
void save_to_file(struct account *accounts, int count);
void load_from_file(struct account **accounts, int *count);
void free_memory(struct account *accounts);

int main() {
    struct account *accounts = NULL;
    int count = 0;
    int choice;

    load_from_file(&accounts, &count);

    do {
        printf("\n\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n2. View All Accounts\n3. Deposit Money\n");
        printf("4. Withdraw Money\n5. Search Account\n6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice) {
            case 1:
                create_account(&accounts, &count);
                break;
            case 2:
                view_all_accounts(accounts, count);
                break;
            case 3:
                deposit_money(accounts, count);
                break;
            case 4:
                withdraw_money(accounts, count);
                break;
            case 5:
                search_account(accounts, count);
                break;
            case 6:
                save_to_file(accounts, count);
                free_memory(accounts);
                printf("Data saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void create_account(struct account **accounts, int *count) {
    (*accounts) = realloc(*accounts, (*count + 1) * sizeof(struct account));
    if (*accounts == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    printf("Enter Account Number: ");
    scanf("%d", &((*accounts)[*count].acc_no));
    printf("Enter Name: ");
    scanf(" %[^
]s", (*accounts)[*count].name);
    printf("Enter Initial Balance: ");
    scanf("%f", &((*accounts)[*count].balance));
    (*count)++;
    printf("Account created successfully!\n");
}

void view_all_accounts(struct account *accounts, int count) {
    if (count == 0) {
        printf("No accounts to display.\n");
        return;
    }
    printf("\nList of Accounts:\n");
    for (int i = 0; i < count; i++) {
        printf("Acc No: %d | Name: %s | Balance: %.2f\n",
               accounts[i].acc_no, accounts[i].name, accounts[i].balance);
    }
}

void deposit_money(struct account *accounts, int count) {
    int acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    for (int i = 0; i < count; i++) {
        if (accounts[i].acc_no == acc_no) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Invalid amount!\n");
                return;
            }
            accounts[i].balance += amount;
            printf("Amount deposited successfully!\n");
            return;
        }
    }
    printf("Account not found.\n");
}

void withdraw_money(struct account *accounts, int count) {
    int acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    for (int i = 0; i < count; i++) {
        if (accounts[i].acc_no == acc_no) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= 0 || amount > accounts[i].balance) {
                printf("Invalid or insufficient balance!\n");
                return;
            }
            accounts[i].balance -= amount;
            printf("Amount withdrawn successfully!\n");
            return;
        }
    }
    printf("Account not found.\n");
}

void search_account(struct account *accounts, int count) {
    int acc_no;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    for (int i = 0; i < count; i++) {
        if (accounts[i].acc_no == acc_no) {
            printf("Acc No: %d | Name: %s | Balance: %.2f\n",
                   accounts[i].acc_no, accounts[i].name, accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void save_to_file(struct account *accounts, int count) {
    FILE *fp = fopen("accounts.dat", "wb");
    if (fp == NULL) {
        printf("Error saving data!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(accounts, sizeof(struct account), count, fp);
    fclose(fp);
}

void load_from_file(struct account **accounts, int *count) {
    FILE *fp = fopen("accounts.dat", "rb");
    if (fp == NULL) return;
    fread(count, sizeof(int), 1, fp);
    *accounts = malloc(*count * sizeof(struct account));
    if (*accounts == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    fread(*accounts, sizeof(struct account), *count, fp);
    fclose(fp);
}

void free_memory(struct account *accounts) {
    free(accounts);
}