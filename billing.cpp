#include <iostream>
#include <fstream>

using namespace std;

class shopping {
private:
    int p_code;
    float price;
    float disc;
    string p_name;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu() {
    m:
    int choice;
    string email;
    string pswrd;

    cout << "\t\t\t\t____________________\n";
    cout << "\t\t\t\t                     \n";
    cout << "\t\t\t\t Supermarket Main Menu\n";
    cout << "\t\t\t\t                     \n";
    cout << "\t\t\t\t____________________\n";

    cout << "\t\t\t\t | 1) Administrator |\n";
    cout << "\t\t\t\t | 2) Buyer         |\n";
    cout << "\t\t\t\t | 3) Exit          |\n";
    cout << "\t\t\t\t Please Select: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t\t Enter Password: ";
            cin >> pswrd;

            if (email == "sudhanshujoshi95@gmail.com" && pswrd == "Pawanjoshi@14") {
                administrator();
            } else {
                cout << "Invalid email/password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout << "Please select from the given options\n";
    }

    goto m;
}

void shopping::administrator() {
    m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t|____1) Add the product____|";
    cout << "\n\t\t\t|____2) Edit the product____|";
    cout << "\n\t\t\t|____3) Delete the product____|";
    cout << "\n\t\t\t|____4) Back to main menu____|";

    cout << "\n\t\t\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            add();
            break;

        case 2:
            edit();
            break;

        case 3:
            rem();
            break;

        case 4:
            menu();
            break;

        default:
            cout << "Invalid choice!\n";
    }

    goto m;
}

void shopping::buyer() {
    m:
    int choice;
    cout << "\t\t Buyer \n";
    cout << "\t\t\t 1) Buy Product \n";
    cout << "\t\t\t 2) Go back \n";
    cout << "\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            receipt();
            break;

        case 2:
            menu();
            break;

        default:
            cout << "Invalid choice!\n";
    }

    goto m;
}

void shopping::add() {
    m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code of the product: ";
    cin >> p_code;
    cout << "\n\n\t Name of the product: ";
    cin >> p_name;
    cout << "\n\n\t Price of the product: ";
    cin >> price;
    cout << "\n\n\t Discount on the product: ";
    cin >> disc;

    data.open("database.txt", ios::in);  // Open file in read mode

    if (!data) {
        data.open("database.txt", ios::app | ios::out); // Open file in append and write mode
        data << " " << p_code << " " << p_name << " " << price << " " << disc << endl;
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
            goto m;
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << p_code << " " << p_name << " " << price << " " << disc << endl;
            data.close();
        }
    }

    cout << "\n\n\t\t Record inserted successfully!";
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the Record ";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data) {
        cout << "\n\n File doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> p_code >> p_name >> price >> disc;

        while (!data.eof()) {
            if (pkey == p_code) {
                cout << "\n\t\t Product new code: ";
                cin >> c;
                cout << "\n\t\t Name of the product: ";
                cin >> n;
                cout << "\n\t\t Price of the product: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;

                data1 << " " << c << " " << n << " " << p << " " << d << endl;
                cout << "\n\n\t\t Record edited successfully!";
                token++;
            } else {
                data1 << " " << p_code << " " << p_name << " " << price << " " << disc << endl;
            }

            data >> p_code >> p_name >> price >> disc;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found, sorry!";
        }
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete the product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data) {
        cout << "File doesn't exist";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> p_code >> p_name >> price >> disc;

        while (!data.eof()) {
            if (p_code == pkey) {
                cout << "\n\n\t Product deleted successfully!";
                token++;
            } else {
                data1 << " " << p_code << " " << p_name << " " << price << " " << disc << endl;
            }
            data >> p_code >> p_name >> price >> disc;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found";
        }
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);

    cout << "\n\n|___________________________________\n";
    cout << "Product-No. \t\t Name \t\t Price\n";
    cout << "|___________________________________\n";
    data >> p_code >> p_name >> price >> disc;

    while (!data.eof()) {
        cout << p_code << "\t\t" << p_name << "\t\t" << price << endl;
        data >> p_code >> p_name >> price >> disc;
    }
    data.close();
}

void shopping::receipt() {
    fstream data;

    int codes_arr[100];
    int qt_arr[100];
    char choice;
    int c = 0;
    float amount = 0;
    float disc = 0;
    float total = 0;

    cout << "\n\n\t\t\t RECEIPT ";
    data.open("database.txt", ios::in);

    if (!data) {
        cout << "\n\n Empty Database";
    } else {
        data.close();

        list();

        cout << "\n_____________________________________\n";
        cout << "\n                                     \n";
        cout << "\n        Please place the order       \n";
        cout << "\n                                     \n";
        cout << "\n_____________________________________\n";

        do {
            m:
            cout << "\n\n Enter Product code: ";
            cin >> codes_arr[c];
            cout << "\n\n Enter the product quantity: ";
            cin >> qt_arr[c];

            for (int i = 0; i < c; i++) {
                if (codes_arr[c] == codes_arr[i]) {
                    cout << "\n\n Duplicate product code. Please try again.";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Do you want to buy another product? If yes then press 'Y' else 'N': ";
            cin >> choice;
        } while (choice == 'Y' || choice == 'y');

        cout << "\n\n\t\t\t__________________RECEIPT____________________\n";
        cout << "\nProduct No \t Product Name \t Product Quantity \t Price \t Amount \t Amount with discount\n";

        for (int i = 0; i < c; i++) {
            fstream data;
            data.open("database.txt", ios::in);
            data >> p_code >> p_name >> price >> disc;

            while (!data.eof()) {
                if (p_code == codes_arr[i]) {
                    amount = price * qt_arr[i];
                    disc = amount - (amount * disc / 100);
                    total = total + disc;
                    cout << "\n" << p_code << "\t\t" << p_name << "\t\t" << qt_arr[i] << "\t\t\t" << price << "\t" << amount << "\t\t" << disc;
                }
                data >> p_code >> p_name >> price >> disc;
            }
            data.close();
        }
        cout << "\n\n____________________________________";
        cout << "\n Total Amount: " << total;
    }
}

int main() {
    shopping s;
    s.menu();
}
