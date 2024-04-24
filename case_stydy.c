#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS_TO_ADD 10

typedef struct {
    char *name;
    float price;
    int quantity;
} Product;

Product inventory[MAX_ITEMS];
int numItems = 0;

int compareNames(const char *name1, const char *name2) {
    return strcmp(name1, name2) == 0;
}

void addProduct() {
    if (numItems >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }

    if (numItems + 1 > MAX_ITEMS) {
        printf("Cannot add more than %d products at once.\n", MAX_PRODUCTS_TO_ADD);
        return;
    }

    printf("Enter product details for product %d:\n", numItems + 1);

    inventory[numItems].name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    printf("Name: ");
    scanf("%s", inventory[numItems].name);

    printf("Price (in Rs): ");
    scanf("%f", &(inventory[numItems].price));

    printf("Quantity: ");
    scanf("%d", &(inventory[numItems].quantity));

    numItems++;
    printf("Product added successfully.\n");
}

void generateBill() {
    char itemName[MAX_NAME_LENGTH];
    int quantityNeeded;
    float total = 0.0;
    float tax = 0.0; 
    int found = 0;

    printf("Enter the number of different products to buy: ");
    scanf("%d", &quantityNeeded);

    printf("\n-------------------BILL-------------------\n");
    printf("%-20s %-10s %-10s\n", "Item", "Price", "Quantity");
    printf("------------------------------------------\n");

    for (int i = 0; i < quantityNeeded; i++) {
        printf("Enter the product you need: ");
        scanf("%s", itemName);

        found = 0;
        for (int j = 0; j < numItems; j++) {
            if (compareNames(itemName, inventory[j].name)) {
                found = 1;
                int quantityToBuy;
                printf("Enter quantity of %s: ", inventory[j].name);
                scanf("%d", &quantityToBuy);
                if (inventory[j].quantity >= quantityToBuy) {
                    printf("%-20s %-10.2f %-10d\n", inventory[j].name, inventory[j].price, quantityToBuy);
                    total += inventory[j].price * quantityToBuy;
                    inventory[j].quantity -= quantityToBuy;
                } else {
                    printf("Insufficient quantity available for %s.\n", inventory[j].name);
                    break;
                }
            }
        }

        if (!found) {
            printf("Product %s not available.\n", itemName);
        }
    }

    
    tax = total * 0.09;
    total += tax; 

    printf("------------------------------------------\n");
    printf("Subtotal: Rs%.2f\n", total - tax); 
    printf("Tax (9%%): Rs%.2f\n", tax); 
    printf("Total: Rs%.2f\n", total);
}

int main() {
    int choice;
    do {
        printf("\nWelcome to Smart Bazaar!\n");
        printf("1. Customer\n");
        printf("2. Shop Owner\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateBill();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (1); 

    return 0;
}