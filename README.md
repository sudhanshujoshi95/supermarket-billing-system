# supermarket-billing-system
Supermarket billing system using OOP concepts and File Handling.

This program implements a simple supermarket management system with a console-based interface. Here is a summary of what the program does and how it works:

**Classes and Methods**
- Class shopping:
  - Private Members:
int p_code: Product code.
float price: Product price.
float disc: Product discount.
string p_name: Product name.
Public Methods:
void menu(): Displays the main menu and handles user input for navigation.
void administrator(): Displays the administrator menu and handles product management.
void buyer(): Displays the buyer menu for purchasing products.
void add(): Adds a new product to the database.
void edit(): Edits an existing product in the database.
void rem(): Removes a product from the database.
void list(): Lists all products in the database.
void receipt(): Generates a receipt for purchased products.

**Functionality**

Menu Function:

The main menu provides options for the administrator, buyer, and exit.
The administrator option requires email and password authentication.
The buyer option allows the user to buy products or go back to the main menu.

Administrator Functions:

Add Product: Prompts the user for product details and adds the product to the database.txt file.

Edit Product: Prompts the user for the product code and allows editing of product details.

Delete Product: Prompts the user for the product code and deletes the product from the database.

List Products: Lists all products in the database.

Buyer Functions:

Buy Product: Allows the user to select products, specify quantities, and generate a receipt.


The receipt includes product details, quantities, prices, amounts, and discounted amounts.

**File Operations**
database.txt: Used to store product details. The file is read from and written to for adding, editing, listing, and deleting products.


**File Handling in the Code**

Including Required Header:
#include <fstream>
This header file is necessary for file handling in C++. It provides definitions for file stream classes like fstream, ifstream, and ofstream.
Adding Products to the File:
The add() method writes product details to the file.

void shopping::add() {
    fstream data;
    int c;
    int token = 0;
    float p, d;
    string n;

    cout << "\n\n\tAdd new product";
    cout << "\n\n\tProduct code of the product: ";
    cin >> p_code;
    cout << "\n\n\tName of the product: ";
    cin >> p_name;
    cout << "\n\n\tPrice of the product: ";
    cin >> price;
    cout << "\n\n\tDiscount on the product: ";
    cin >> disc;

    data.open("database.txt", ios::in); // Open file in read mode

    if (!data) {
        data.open("database.txt", ios::app | ios::out); // Open file in append and write mode
        data << " " << p_code << " " << p_name << " " << price << " " << disc << "\n";
        data.close();
    } else {
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == p_code) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1) {
            cout << "\n\n\tProduct code already exists. Please enter a unique code.";
            return;
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << p_code << " " << p_name << " " << price << " " << disc << "\n";
            data.close();
        }
    }

    cout << "\n\n\tRecord inserted!";
}
fstream data; declares a file stream object.
data.open("database.txt", ios::in); opens the file in read mode to check if the product code already exists.
If the file doesn't exist, it opens the file in append and write mode (ios::app | ios::out) and writes the product details.
If the file exists, it reads through the file to ensure the product code is unique. If unique, it appends the product details to the file.
Editing Products in the File:
The edit() method modifies existing product details.

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\n\tModify the record";
    cout << "\n\n\tProduct code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> p_code >> p_name >> price >> disc;
        while (!data.eof()) {
            if (pkey == p_code) {
                cout << "\n\tProduct new code: ";
                cin >> c;
                cout << "\n\tName of the product: ";
                cin >> n;
                cout << "\n\tPrice: ";
                cin >> p;
                cout << "\n\tDiscount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                token++;
            } else {
                data1 << " " << p_code << " " << p_name << " " << price << " " << disc << "\n";
            }
            data >> p_code >> p_name >> price >> disc;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\nRecord not found!";
        }
    }
}
data.open("database.txt", ios::in); opens the original file in read mode.
data1.open("database1.txt", ios::app | ios::out); opens a temporary file in append and write mode.
Reads each record from the original file. If the product code matches the key, it writes the updated details to the temporary file. Otherwise, it writes the original details.
remove("database.txt"); deletes the original file.
rename("database1.txt", "database.txt"); renames the temporary file to the original file name.
Removing Products from the File:
The rem() method deletes a product from the file.

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\tDelete product";
    cout << "\n\n\tProduct code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> p_code >> p_name >> price >> disc;
        while (!data.eof()) {
            if (p_code == pkey) {
                cout << "\n\n\tProduct deleted successfully!";
                token++;
            } else {
                data1 << " " << p_code << " " << p_name << " " << price << " " << disc << "\n";
            }
            data >> p_code >> p_name >> price >> disc;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\nRecord not found!";
        }
    }
}
Similar to the edit() method, it uses a temporary file to store records except for the one to be deleted.
remove("database.txt"); deletes the original file.
rename("database1.txt", "database.txt"); renames the temporary file to the original file name.
Listing Products from the File:
The list() method displays all products.

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|---------------------------------------------------\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|---------------------------------------------------\n";
    data >> p_code >> p_name >> price >> disc;
    while (!data.eof()) {
        cout << p_code << "\t\t" << p_name << "\t\t" << price << "\n";
        data >> p_code >> p_name >> price >> disc;
    }
    data.close();
}
data.open("database.txt", ios::in); opens the file in read mode.
Reads each product's details from the file and displays them in a tabular format.
Closes the file after reading all the records.
Generating a Receipt:
The receipt() method calculates the total price and generates a receipt for the products purchased.

void shopping::receipt() {
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\tReceipt";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nEmpty database";
    } else {
        data.close();

        list();
        cout << "\n----------------------------------";
        cout << "\n|                                 |";
        cout << "\n        Please place the order     ";
        cout << "\n|                                 |";
        cout << "\n----------------------------------\n";
        do {
            cout << "\n\nEnter product code: ";
            cin >> arrc[c];
            cout << "\n\nEnter the product quantity: ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++) {
                if (arrc[c] == arrc[i]) {
                    cout << "\n\nDuplicate product code. Please try again.";
                    goto m;
                }
            }
            c++;
            cout << "\n\nDo you want to buy another product? (y/n): ";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t----------------------RECEIPT----------------------\n";
        cout << "\nProduct No\t Product Name\t Quantity\t Price\t Amount\t Amount with discount\n";

        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> p_code >> p_name >> price >> disc;
            while (!data.eof()) {
                if (p_code == arrc[i]) {
                    amount = price * arrq[i];
                    dis = amount - (amount * disc / 100);
                    total += dis;
                    cout << "\n" << p_code << "\t\t" << p_name << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> p_code >> p_name >> price >> disc;
            }
            data.close();
        }
        cout << "\n\n--------------------------------------------------------";
        cout << "\nTotal Amount: " << total;
    }
}
data.open("database.txt", ios::in); opens the file in read mode.
Prompts the user to enter product codes and quantities.
Checks for duplicate product codes.
Reads each product's details from the file, calculates the amount and discounted amount, and displays them.
Calculates and displays the total amount.


**Summary:**

Adding Products: Opens the file in append mode and writes new product details, ensuring unique product codes.
Editing Products: Opens the original file in read mode and a temporary file in write mode. Writes updated details to the temporary file and renames it.
Removing Products: Similar to editing but skips writing the product to be deleted to the temporary file.
Listing Products: Opens the file in read mode and displays all products.
Generating Receipt: Opens the file in read mode, prompts the user for product codes and quantities, calculates the total, and generates a receipt.
The program uses file handling to manage product records efficiently, ensuring data persistence across sessions.


![image](https://github.com/user-attachments/assets/5354cfb6-ffb8-410b-93ea-989dd423167c)
![image](https://github.com/user-attachments/assets/d0c40840-0b0e-4d22-8603-87f09442923d)
![image](https://github.com/user-attachments/assets/5d70429b-bc0a-4bf4-b286-3ee04324b2ca)
![image](https://github.com/user-attachments/assets/21e13c74-6e13-4825-a829-235c4f3227a1)
