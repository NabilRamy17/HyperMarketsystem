#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <stdio.h>
using namespace std;

void admin_mainMenu();
void user_mainMenu();

const string USERS_FILE = "users.txt";
const string PRODUCTS_FILE = "products.txt";

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin";

class Product {
public:
    string name;
    double price;
    int quantity;
    string category;

    Product() {

    }

    Product(string name, double price, int quantity,string category) {
        this->name = name;
        this->price = price;
        this->quantity = quantity;
        this->category = category;
    }

};

Product list_Product[100];
int products_number = 0; // 3dd el products fi el array

Product cart[100];
int quantity[100];
int products_number_in_cart = 0;


void Loading(int speed, string keyword) { // speed in mile sec

    for (int i = 0; i <= 15; i++)
    {
        cout << keyword << "...[";

        for (int j = 0; j < 15; j++)
        {
            if (i > j) {
                cout << "#";
            }
            else {
                cout << "_";
            }
        }
        cout << "] " << (100 / 15) * i << "% ";

        if (i % 4 == 0)
            cout << "|";
        else if (i % 4 == 1)
            cout << "/";
        else if (i % 4 == 2)
            cout << "-";
        else if (i % 4 == 3)
            cout << "\\";


        cout << endl << endl << endl;

        Sleep(speed);
        system("CLS");
    }



}

void signup() {
    string username, password;

    cout << " - Enter username : ";
    cin >> username;
    cout << " - Enter password : ";
    cin >> password;

    while (true) {
        ifstream ifile(USERS_FILE);
        bool found = false;
        while (!ifile.eof() && ifile.is_open() && !found) {
            string temp_u, temp_p;
            ifile >> temp_u >> temp_p;
            if (temp_u == username)
                found = true;
        }
        ifile.close();

        if (found) {
            cout << "Error..Username is already taken..enter again :";
            cin >> username;
        }
        else {
            break;
        }
    }

    ofstream ofile(USERS_FILE, ios::app);
    ofile << endl << username << " " << password;
    ofile.close();
    
    cout << "User added successfully" << endl;
}

void login() {
    string username, password;

    for (int i = 3; i >= 0; i--) {
        cout << " - Enter username : ";
        cin >> username;
        cout << " - Enter password : ";
        cin >> password;

        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
            admin_mainMenu();
            exit(0);
        }

        ifstream ifile(USERS_FILE);
        bool found = false;
        string temp_u, temp_p;

        while (!ifile.eof() && ifile.is_open() && !found) {
            ifile >> temp_u >> temp_p ;
            if (temp_u == username && temp_p == password)
                found = true;
        }
        ifile.close();

        if (found) {
            cout << "Welcome user" << endl;
            user_mainMenu();
            break;
        }
        else {
            cout << "Wrong username or password .. you have " << i  << " trials" << endl;
        }
    }
    
    cout << "You have to sign up first" << endl ;
}

void viewProducts()
 {
    if (products_number == 0) {
        cout << "No Products to view" << endl;
    }
    else {
        cout << left << setw(15) << "Name" << setw(20) << "Price" << setw(25) << "Quantity" << setw(15) << "category" << endl;
        cout << "===============================================================================" << endl;
        for (int i = 0; i < products_number; i++) {
            cout << left << setw(15) << list_Product[i].name << setw(20) << list_Product[i].price << setw(25) << list_Product[i].quantity << setw(15) << list_Product[i].category << endl;
        }
    }
}

void addproduct() {
    string name, category;
    double price;
    int quantity;

    cout << " - Enter product name : ";
    cin >> name;    
    cout << " - Enter product category : ";
    cin >> category;    
    cout << " - Enter product price : ";
    cin >> price;    
    cout << " - Enter product quantity : ";
    cin >> quantity;

    while (true) {
        bool found = false;
        for (int i = 0; i < products_number; i++) {
            if (list_Product[i].name == name) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Error.." << name  << " is already added before .. enter a new one :";
            cin >> name;
        }
        else 
            break;
    }


    Loading(100, "adding");

    Product product = Product(name, price, quantity, category); // create product object
    list_Product[products_number++] = product;
    cout << product.name << " added successfully" << endl;
}

void deleteproduct() {
    viewProducts();

    cout << endl << "Enter the name of the product you want to delete: ";
    string target;
    cin >> target;

    // Find the index of the products with the target number
    int targetIndex = -1;
    for (int i = 0; i < products_number; ++i) {
        if (list_Product[i].name == target) {
            targetIndex = i;
            break;
        }
    }

    // If the movie with the target number is found
    if (targetIndex != -1) {
        // Shift elements to remove the target movie
        for (int i = targetIndex; i < products_number - 1; ++i) {
            list_Product[i] = list_Product[i + 1];
        }
        products_number--;
        cout << target << " deleted successfully." << endl;
    }
    else {
        cout << target << " not found." << endl;
    }
}

void updateproduct() {
    viewProducts();

    int taregetIndex = -1;

    while (taregetIndex == -1) {
        cout << endl << "Enter the name of the product you want to update: ";
        string target;
        cin >> target;

        for (int i = 0; i < products_number; i++)
        {
            if (list_Product[i].name == target) {
                taregetIndex = i;
                break;
            }
        }

        if (taregetIndex == -1)
            cout << "Error.." << target << " not found" << endl;
    }


    string name, category;
    double price;
    int quantity;

    cout << " - Enter product new name : ";
    cin >> name;
    cout << " - Enter product new category : ";
    cin >> category;
    cout << " - Enter product new price : ";
    cin >> price;
    cout << " - Enter product new quantity : ";
    cin >> quantity;

    list_Product[taregetIndex].name = name;
    list_Product[taregetIndex].category = category;
    list_Product[taregetIndex].price = price;
    list_Product[taregetIndex].quantity = quantity;

    cout << list_Product[taregetIndex].name << " has been updated successfully" << endl;

}

void save() {
    ofstream file(PRODUCTS_FILE);

    for (int i = 0; i < products_number; i++)
    {
        file << endl << list_Product[i].name << " " << list_Product[i].price << " " << list_Product[i].quantity << " " << list_Product[i].category;
    }

    file.close();
}

void getDataFromFile() {
    ifstream file(PRODUCTS_FILE);

    while(!file.eof() && file.is_open())
    {
        string name, category;
        double price;
        int quantity;

        file >> name >> price >> quantity >> category;
        list_Product[products_number++] = Product(name, price, quantity, category);// create product object
    }

    file.close();
}

void admin_mainMenu() {
    cout << "+-----------------------------------------+" << endl;
    cout << "|                                         |" << endl;
    cout << "|             Admin Main Menu             |" << endl;
    cout << "|             ---------------             |" << endl;
    cout << "|                                         |" << endl;
    cout << "|            1. View products             |" << endl;
    cout << "|            2. add product               |" << endl;
    cout << "|            3. delete product            |" << endl;
    cout << "|            4. update product            |" << endl;
    cout << "|            5. Exit                      |" << endl;
    cout << "|                                         |" << endl;
    cout << "+-----------------------------------------+" << endl;
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        viewProducts();
        break;
    case 2:
         addproduct();
        break;
    case 3:
         deleteproduct();
        break;
    case 4:
         updateproduct();
        break;
    default:
        save();
        exit(0);
        break;
    }

    admin_mainMenu();
}

void viewCart() {
    if (products_number_in_cart == 0) {
        cout << "No Products to view in the cart" << endl;
    }
    else {
        cout << left << setw(15) << "Name"  << setw(25) << "Quantity" << endl;
        cout << "===============================================================================" << endl;
        for (int i = 0; i < products_number_in_cart; i++) {
            cout << left << setw(15) << cart[i].name << setw(25) << quantity[i]  << endl;
        }
    }
}

void addToCart() {
    viewProducts();
    cout << " Enter product name : ";
    string target;
    cin >> target;
    cout << " Enter product quantity :";
    int q;
    cin >> q;

    for (int i = 0; i < products_number; ++i) {
        if (list_Product[i].name == target) {
            cart[products_number_in_cart] = list_Product[i];
            quantity[products_number_in_cart++] = q;
            cout << "Done "<<endl;
            return;
        }
    }
    cout << "Not found" << endl;
}

void Checkout() {
    double total = 0.0;
    cout << "Receipt:" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Name\t\tPrice\tQty\tTotal" << endl;
    cout << "---------------------------------------------------" << endl;

    for (int i = 0; i < products_number_in_cart; ++i) {
        double productTotal = cart[i].price * quantity[i];
        total += productTotal;

        cout << cart[i].name << "\t\t" << cart[i].price << "\t" << quantity[i] << "\t" << productTotal << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Total: $" << total << endl;
}

void user_mainMenu() {
    cout << "+-----------------------------------------+" << endl;
    cout << "|                                         |" << endl;
    cout << "|             User Main Menu              |" << endl;
    cout << "|             --------------              |" << endl;
    cout << "|                                         |" << endl;
    cout << "|            1. View products             |" << endl;
    cout << "|            2. View Cart                 |" << endl;
    cout << "|            3. Add to cart               |" << endl;
    cout << "|            4. Check out                 |" << endl;
    cout << "|            5. Exit                      |" << endl;
    cout << "|                                         |" << endl;
    cout << "+-----------------------------------------+" << endl;
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        viewProducts();
        break;
    case 2:
        viewCart();
        break;
    case 3:
        addToCart();
        break;
    case 4:
        Checkout();
        break;
    default:
        exit(0);
        break;
    }

    user_mainMenu();
}


void start() {
    cout << "+-----------------------------------------+" << endl;
    cout << "|                                         |" << endl;
    cout << "|      Hypermarket Management System      |" << endl;
    cout << "|      -----------------------------      |" << endl;
    cout << "|                                         |" << endl;
    cout << "|            1. Login                     |" << endl;
    cout << "|            2. Sign up                   |" << endl;
    cout << "|            3. Quit                      |" << endl;
    cout << "|                                         |" << endl;
    cout << "+-----------------------------------------+" << endl;
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        login();
        break;
    case 2:
        signup();
        break;
    default:
        exit(0);
    }
}

int main()
{
    getDataFromFile();
    start();

}

