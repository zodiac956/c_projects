#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct accounts {
    char aName[50];
    int aNumber;
    float aMoney;
};

struct accounts* account = NULL;
int aCount = 0;

// Function declarations
void aCreate();
void aDeposit(struct accounts *acc);
void aWithdraw(struct accounts *acc);
void aBalance(struct accounts *acc);
void aOpen();
void sSaveToFile();
void sLoadFromFile();
void listAccounts();
void pressEnterToContinue();
void aDelete();




int main(void) {
    sLoadFromFile(); // Load accounts at program start
    int mainChoice;

    while (1) {
        printf("\n**************************\n");
        printf("Welcome to BMS\n");
        printf("1. Create Account\n2. Open Account\n3. List accounts\n4. Delete Account\n5. Exit\n");
        printf("Choice: ");
        scanf("%d", &mainChoice);
        while (getchar() != '\n'); // clear input buffer

        switch (mainChoice) {
            case 1: aCreate(); break;
            case 2: aOpen(); break;
            case 3: listAccounts();break;
            case 4: aDelete();break;
            case 5:
                sSaveToFile(); // Save before exiting
                printf("Goodbye!\n");
                free(account);
                exit(0); // ✅ added missing semicolon
            default:
                printf("Invalid option\n");
        }
    }

    return 0;
}

void aCreate() {
    aCount++;

    account = realloc(account, aCount * sizeof(struct accounts));
    if (account == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    struct accounts *newAcc = &account[aCount - 1];

    printf("\nName : ");
    fgets(newAcc->aName, sizeof(newAcc->aName), stdin);
    if (newAcc->aName[strlen(newAcc->aName) - 1] == '\n')
        newAcc->aName[strlen(newAcc->aName) - 1] = '\0';

    printf("Number : ");
    scanf("%d", &newAcc->aNumber);

    newAcc->aMoney = 0.0; // default initial balance
    while (getchar() != '\n'); // Clear buffer

    printf("Account created successfully!\n");

    sSaveToFile(); // ✅ save after creating account
}

void aDeposit(struct accounts *acc) {
    float moneyIn;
    printf("How much to deposit : ");
    scanf("%f", &moneyIn);

    acc->aMoney += moneyIn;

    printf("Deposit successful. New balance: %.2f\n", acc->aMoney);

    sSaveToFile(); // ✅ save after deposit
}

void aWithdraw(struct accounts *acc) {
    float moneyout;

    printf("\nCurrent Balance: %.2f\n", acc->aMoney);
    printf("How much to withdraw: ");
    scanf("%f", &moneyout);

    if (moneyout <= acc->aMoney) {
        acc->aMoney -= moneyout;
        printf("Withdrawal successful. New balance: %.2f\n", acc->aMoney);
        sSaveToFile(); // ✅ save after withdrawal
    } else {
        printf("Insufficient funds!\n");
    }
}

void aBalance(struct accounts *acc) {
    printf("\n--- Account Info ---\n");
    printf("Account holder: %s\n", acc->aName);
    printf("Account number: %d\n", acc->aNumber);
    printf("Balance: %.2f\n", acc->aMoney);
}

void aOpen() {
    int searchNumber;
    int foundIndex = -1;

    if(aCount<1){
        printf("\nThere is no accounts!! \n");
        pressEnterToContinue();
        return;
        }
    
    printf("Enter your account number: ");
    scanf("%d", &searchNumber);

    for (int i = 0; i < aCount; i++) {
        if (searchNumber == account[i].aNumber) { // ✅ fix: was using account->aNumber
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Account doesn't exist. Returning to menu.\n");
        return;
    }

    int option;
    while (1) {
        printf("\n--- Account Menu ---\n");
        printf("1. Withdraw\n2. Deposit\n3. Show Balance\n4. Exit Account\n");
        printf("Choose: ");
        scanf("%d", &option);
        while (getchar() != '\n'); // Clear buffer

        switch (option) {
            case 1: aWithdraw(&account[foundIndex]); break;
            case 2: aDeposit(&account[foundIndex]); break;
            case 3: aBalance(&account[foundIndex]); break;
            case 4:
                printf("Exiting account menu.\n");
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}

void sSaveToFile() {
    FILE* fp = fopen("accounts.dat", "wb");
    if (fp == NULL) {
        printf("Error saving to file.\n");
        return;
    }

    fwrite(&aCount, sizeof(int), 1, fp);
    fwrite(account, sizeof(struct accounts), aCount, fp);
    fclose(fp);

    printf("✔ Data saved successfully.\n");
}

void sLoadFromFile() {
    FILE* fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No saved data found. Starting fresh.\n");
        return; // no saved data
    }

    fread(&aCount, sizeof(int), 1, fp);
    account = malloc(aCount * sizeof(struct accounts));
    if (account == NULL) {
        printf("Memory allocation failed while loading.\n");
        fclose(fp);
        exit(1);
    }

    fread(account, sizeof(struct accounts), aCount, fp);
    fclose(fp);
    printf("✔ %d accounts loaded from file.\n", aCount);
}
void listAccounts(){
    
    if(aCount<1){
        printf("\nThere is no accounts!! \n");
        pressEnterToContinue();
        return;
        }
    
    
    for(int i =0;i<aCount;i++){
        printf("\nNAME : %s\n",account[i].aName);
       printf("\nNumber : %d",account[i].aNumber);
 }
    }

void aDelete(){
    
    int searchparameter;
    int foundindex=-1;
    printf("Enter account number to delete : ");
    scanf("%d",&searchparameter);
    
    for(int i =0;i<aCount;i++){
        if(searchparameter==account[i].aNumber){  
            foundindex=i;
        break;}
      
        }
    
    if (foundindex == -1) {
        printf("\nStudent not found!\n");
        pressEnterToContinue();
        return;
    }

    for(int i=foundindex;i<aCount-1;i++){
        account[i]=account[i+1];
        }
    aCount--;
    
    account=realloc(account,aCount*sizeof(struct accounts));
    
    printf("Account deleted successfully.\n");
    pressEnterToContinue();
return;
}
    
    
    
   
 void pressEnterToContinue() {
    printf("\nPress Enter to return to the menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}
