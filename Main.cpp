#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iomanip> 
#include <windows.h> 
#include <conio.h> 
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iomanip>   
#include <sstream>  
#include <windows.h> 
#include <iomanip>
#include <ctime>
#include <map>
using namespace std;
struct Product {
    int id;
    string name;
    double price;
    string description;
    string category;
};


vector<Product> products;
struct User {
    string username;
    string email;
    string password;
};

vector<User> users;

void clearScreen() {
    system("cls");
}

void firstMenu() {
    cout<<endl;
        cout << "========================================================================================================" << endl;
        cout<<  "|                                                                                                       |" <<endl;                           
        cout << "|                                   1. Login                                                            |" <<endl;                              
        cout << "|                                                                                                       |" <<endl;                          
        cout << "|                                   2. List all Products                                                |" <<endl;                             
        cout << "|                                                                                                       |" <<endl;                           
        cout << "|                                   3. Settings                                                         |" <<endl;                           
        cout << "|                                                                                                       |" <<endl;                              
        cout << "======================================================================================================= |" <<endl;
        cout<<endl;
        cout << "Please Enter Your Choice: ";
}

//=======================================================================================================================================
bool usernameExists(const string& username) {
    ifstream file("users.txt");
    string line;

    while (getline(file, line)) {
        // Assume each line is formatted as: username email password
        size_t pos = line.find(' ');
        if (pos != string::npos) {
            string existingUsername = line.substr(0, pos);
            if (existingUsername == username) {
                return true;
            }
        }
    }

    return false;
}
//========================================================================================================================================

void saveUsers() {
    ofstream file("users.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (const auto& user : users) {
        file << user.username << ' ' << user.email << ' ' << user.password << endl;
    }
}


void loadUsers() {
    ifstream file("users.txt");
    string line;

    users.clear(); // Clear existing users
    while (getline(file, line)) {
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            User user;
            user.username = line.substr(0, pos1);
            user.email = line.substr(pos1 + 1, pos2 - pos1 - 1);
            user.password = line.substr(pos2 + 1);
            users.push_back(user);
        }
    }
}
bool isValidEmail(const string& email) {
    // Check for exact format "user@email.com"
    size_t atPos = email.find('@');
    if (atPos == string::npos) {
        return false;
    }

    string domain = email.substr(atPos);
    return (domain == "@email.com");
}

//=======================================================================================================================================

    void registerUser() {

    cout<<" |-----------------------------------------------------------|"<<endl;
    cout<<" |                     [+1]. Register Account                |" << endl;
    cout<<" |-----------------------------------------------------------|"<<endl;
    cout<<endl;
    string username, email, password;
    cout << "      Username:       ";
    cin >> username;
    cout << "      Email:          ";
    cin >> email;
    cout << "      Password:       ";
    cin >> password;
    cout<<endl;


    // Add the new user to the vector
    users.push_back({username, email, password});
    saveUsers(); // Save immediately after registration

    cout << "User registered successfully!" << endl;
}
//=======================================================================================================================================

bool loginUser(const string& username, const string& password) {
    ifstream file("users.txt");
    string line;
     char ch;
    while (getline(file, line)) {
        // Assume each line is formatted as: username email password
        size_t pos1 = line.find(' ');
        if (pos1 != string::npos) {
            string existingUsername = line.substr(0, pos1);
            size_t pos2 = line.find(' ', pos1 + 1);
            if (pos2 != string::npos) {
                string existingPassword = line.substr(pos2 + 1);
                if (existingUsername == username && existingPassword == password) {
                    return true;
                }
            }
        }     
    }
    return false;
}

//========================================================================================================================================
void handleLogin() {
    char ch;
         cout << " |-----------------------------------------------------------|" << endl;
         cout << " |                     [+2]. Login Account                   |" << endl;
         cout << " |-----------------------------------------------------------|" << endl;
         cout << endl;

    string username, password;

            cout << "         USERNAME: ";
            cin >> username;

            cout << "         PASSWORD: ";
    ch = _getch();
    while (ch != 13) { // 13 is Enter key
        password.push_back(ch);
        cout << 'x'; // Mask the password input
        ch = _getch();
    }
    cout << endl;
    // Call the loginUser function to validate the username and password
    if (loginUser(username, password)) {
        cout << endl;
        cout << "You have logged in successfully!" << endl;
    } else {
        cout << "Invalid username or password! Please try again." << endl;
    }
}

//========================================================================================================================================
void forgotPassword() {
    cout<<endl;
    cout << " |-----------------------------------------------------------|" << endl;
    cout << " |                     Forgot Password                       |" << endl;
    cout << " |-----------------------------------------------------------|" << endl;
    cout<<endl;
    string username;
    cout << "Enter your username:       ";
    cin >> username;

    for (const auto& user : users) {
        if (user.username == username) {
            cout<<"_________________________________________"<<endl;
            cout<<"|Your password is:     " << user.password <<"|"<< endl; // Display the password
            cout<<"__________________________________________"<<endl;
            cout<<endl;
            return;
        }
    }
    cout << "Username not found!......" << endl;
}
//========================================================================================================================================
void secondMenu() {
    cout<<endl;
    cout << "......................................................................................................" << endl;
    cout << "|                                        [+1]. Register Account                                       | " << endl;
    cout << "......................................................................................................" << endl;
    cout << "|                                        [+2]. Login Account                                          | " << endl;
    cout << "......................................................................................................" << endl;
    cout << "|                                        [+0]. Exit                                                   |" << endl;
    cout << "......................................................................................................" << endl;
    cout<<endl;
    cout << "Please Enter your Choice: ";
}

//========================================================================================================================================

void loginRegisterUser() {
    int option;
    do {
        secondMenu();
        cin >> option;
        switch (option) {
            case 1:
                registerUser();
                break;
            case 2:
                handleLogin();
                break;
            
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid option. Please try again!" << endl;
        }
    } while (option != 0);
}

//========================================================================================================================================


//========================================================================================================================================
void changePassword() {
    cout<<endl;
    cout << " |-----------------------------------------------------------|" << endl;
    cout << " |                     Change Password                       |" << endl;
    cout << " |-----------------------------------------------------------|" << endl;
    cout<<endl;
    cout << "Enter username to change password:       ";
    string username;
    cin >> username;

    for (auto& user : users) {
        if (user.username == username) {
            string old_password;
            cout << "Enter old password:    ";
            cin >> old_password;

            if (old_password == user.password) {
                string new_password;
                cout << "Enter new password:   ";
                cin >> new_password;

                user.password = new_password;
                saveUsers(); // Save immediately after password change
                cout<<"_____________________________________"<<endl;
                cout << "Password changed successfully!...." << endl;
                return;
            } else {
                cout << "Incorrect old password!" << endl;
                return;
            }
        }
    }
    cout << "Username not found!" << endl;
}





///========================================================================================================================================

void MenuSetting() {
                cout<<endl;
                cout<<"|==============================================================================================================================|"<<endl;       
                cout<<"|                                                     User Setting                                                             |"<<endl;
                cout<<"|                                                                                                                              |"<<endl;
                cout<<"|==============================================================================================================================|"<<endl;
                cout<<"|              1.  Change Pasword                         |              3.   Veiw Account                                     |"<<endl;
                cout<<"|==============================================================================================================================|"<<endl;
                cout<<"|              2.  Forgot Password                        |              4.  Contact Us                                        |"<<endl;
                cout<<"|==============================================================================================================================|"<<endl;
                cout<<"                                        |          0.   Logout         |                                                       "<<endl;
                cout<<"                                        |==============================|                                                       "<<endl;
                cout<<endl;
                            cout<<" Enter Option:   ";
}
//========================================================================================================================================
// Function to contact support
void contactUs() {

                cout<<endl;
                cout<<"|_________________________________________________________________________________________________________|"<<endl;       
                cout<<"|                                          Contact Us                                                     |"<<endl;
                cout<<"|_________________________________________________________________________________________________________|"<<endl;
                cout<<"|    Email                       |      Cambobuy@email.com                                                |"<<endl;
                cout<<"|________________________________|________________________________________________________________________|"<<endl;
                cout<<"|    Phone                       |      093738334                                                         |"<<endl;
                cout<<"|________________________________|________________________________________________________________________|"<<endl;
                cout<<"|    Facebook                    |      www.cambobuy.fb.com                                               |"<<endl;
                cout<<"|________________________________|________________________________________________________________________|"<<endl;
                cout<<endl;
                
}
//=======================================================================================================================================
// Function to view all user accounts

void viewUserAccounts() {
    if (users.empty()) {
        cout << "No accounts to display!" << endl;
    } else {
        for (const auto& user : users) {
            cout << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "|                    Account                    |" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "| Username    :      " << user.username << string(28 - user.username.length(), ' ')<<"|" << endl;
            cout << "| Email       :      " << user.email << string(28 - user.email.length(), ' ')  <<"|"<<endl;
            cout << "| Password    :      " << user.password << string(28 - user.password.length(), ' ') <<"|" << endl;
            cout << "-------------------------------------------------" << endl;
        }
    }
}




//=======================================================================================================================================

void settingsMenu() {
    int option;
    do {
        MenuSetting();
        cin >> option;
        switch (option) {
            case 1:
                changePassword();
                break;
            case 2:
            forgotPassword();
            break;
            case 3:
                viewUserAccounts();
                break;
            case 4:
                contactUs();
                break;
            case 0:
                cout << "Back..." << endl;
                break;
            default:
                cout << "BACk......" << endl;

        }
    } while (option != 0);
}
//=======================================================================================================================================
class listProduct
{
public:
    string type;
    float price;
    int quantity, Date, Time;
    float total;

    void setType(string type)
    {
        this->type = type;
    }

    void setPrice(float price, int quantity, int Date, float total, int Time)
    {
        this->price = price;
        this->quantity = quantity;
        this->Date = Date;
        this->total = total;
        this->Time = Time;
    }
    void setDisplay(int total)
    {
        this->total = total;
    }
    void display()
    {
        cout << setw(65) << "Drink" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------\n";
        cout << setw(16) << "Type"
             << setw(20) << "Price"
             << setw(20) << "Quantity"
             << setw(20) << "Date"
             << setw(15) << "Time"
             << setw(15) << "Total" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------\n";

        time_t timestamp;
        time(&timestamp);
        struct tm datetime = *localtime(&timestamp);

        string drinkType = "Sting";
        int quantity = 3;
        float price = 2.50;
        total = price * quantity;

        cout << setw(16) << drinkType
             << setw(17) << fixed << setprecision(2) << price << "$"
             << setw(18) << quantity
             << setw(20) << datetime.tm_mday << "/" << datetime.tm_mon + 1 << "/" << datetime.tm_year + 1900
             << setw(12) << datetime.tm_hour << ":" << datetime.tm_min
             << setw(13) << fixed << setprecision(2) << total << "$" << endl;

        cout << "--------------------------------------------------------------------------------------------------------------------------\n";
    }

    void printQr()
    {
        system("python test.py");
    }

    void printPaid()
    {
        int choice;
        int back;
        cout << "Cash payment:       " << total << "$" << endl;
        cout<<endl;
                         cout<<"-------------------------------------------------------------"<<endl;
                         cout<<"|          Are you sure you want to pay?                    |"<< endl;
                         cout<<"-------------------------------------------------------------"<<endl;
                         cout<<"|   1.  Yes                |       2. No                    |"<<endl;
                         cout<<"|-----------------------------------------------------------|"<<endl;
                         cout<<endl;
                         cout << "Enter your choice:    ";
                         cin >> choice;
                         cout<<endl;
        if (choice == 1)
        {
            cout << "Payment successfully ..............!" << endl;
        }
        else
        {
            cout << "Payment cancelled!" << endl;
        }
        cout << "Thank You!" << endl;
    }

    void choice()
    {
        int choice;
    cout<<endl;
                cout<<"|==============================================================================================================================|"<<endl;       
                cout<<"|                                           Choose one way to Pay                                                              |"<<endl;
                cout<<"|==============================================================================================================================|"<<endl;
                cout<<"|              1.  cash Payment                         |              2.   QR Payment                                         |"<<endl;
                cout<<"|==============================================================================================================================|"<<endl;
                cout<<endl;
                     cout<<" Enter your Choice:   ";
         cin >> choice;
        switch (choice)
        {
        case 1:
            printPaid();
            break;
        case 2:
            printQr();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
};
//====================================================================================================================

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

//======================================================================================================================

void printCenteredWithTabs(const string &text, int width) {
    int padding = (width - text.length()) / 2;
    cout << string(padding, ' ') << text << endl;
}

//======================================================================================================================

string formatPrice(float price)
{
    ostringstream oss;
    oss << fixed << setprecision(2) << price;
    return oss.str();
}

//=========================================================================================================================
// Function to display products by pages
void displayPage(const vector<Product> &products, int pageNumber, int itemsPerPage, int consoleWidth)
{
    int start = (pageNumber - 1) * itemsPerPage;
    int end = min(start + itemsPerPage, static_cast<int>(products.size()));

    // Print some newlines before the content for vertical centering
    cout << string(5, '\n');

    if (start >= products.size())
    {
        printCenteredWithTabs("Page number out of range.", consoleWidth);
        return;
    }

    printCenteredWithTabs("Displaying page " + to_string(pageNumber) + ":", consoleWidth);

    for (int i = start; i < end; ++i)
    {
        const Product &product = products[i];
        string productInfo = " |ID:" + to_string(product.id) + " | Name: " + product.name +
                             " | Price: $" + formatPrice(product.price) +
                             " | Description: " + product.description +
                             " | Category: " + product.category;
        printCenteredWithTabs(" ____________________________________________________________________________", consoleWidth);
        printCenteredWithTabs(productInfo, consoleWidth);
    }
    cout << endl;
}

//=================================================================================================================================

// Calculate the total number of pages
int calculateTotalPages(const vector<Product> &products, int itemsPerPage)
{
    return (products.size() + itemsPerPage - 1) / itemsPerPage;
}
//=======================================================================================================================================

Product *searchProductById(vector<Product> &products, int id)
{
    auto it = find_if(products.begin(), products.end(), [id](const Product &p)
                      { return p.id == id; });
    if (it != products.end())
    {
        return &(*it);
    }
    return nullptr;
}

//==================================================================================================================================
// Function to display cart
void displayCart(const vector<Product> &cart, int consoleWidth)
{
    if (cart.empty())
    {
        printCenteredWithTabs("Your cart is empty.", consoleWidth);
        return;
    }

    printCenteredWithTabs("Your Cart:   ", consoleWidth);
    for (const auto &product : cart)
    {
        string productInfo = " |ID:" + to_string(product.id) + " | Name: " + product.name +
                             " | Price: $" + formatPrice(product.price);
        printCenteredWithTabs(productInfo, consoleWidth);
    }
}

//===================================================================================================================================
void displayReceipt(const vector<Product> &cart, int consoleWidth, double totalPrice, int totalQuantity) {
    system("cls");

    // Get current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream dateTime;
    dateTime << 1900 + ltm->tm_year << '-' 
             << setfill('0') << setw(2) << 1 + ltm->tm_mon << '-' 
             << setfill('0') << setw(2) << ltm->tm_mday;
    string date = dateTime.str();

    stringstream timeStream;
    timeStream << setfill('0') << setw(2) << ltm->tm_hour << ':' 
               << setfill('0') << setw(2) << ltm->tm_min;
    string time = timeStream.str();

    // Print header
    printCenteredWithTabs("Receipt Product", consoleWidth);
    printCenteredWithTabs(" ======================================================================================================", consoleWidth);
    printCenteredWithTabs("Date: " + date + " Time: " + time, consoleWidth);

    printCenteredWithTabs("|  ID  | Name            | Price       | Quantity   | Date       | Time   | Total          |", consoleWidth);
    printCenteredWithTabs(" ======================================================================================================", consoleWidth);


map<int, pair<string, double>> productDetails; // Map to store product ID, name, and price
map<int, int> productCount; // Map to store product ID and quantity

for (const auto &item : cart) {
    productCount[item.id]++; // Count quantity for each product
    if (productDetails.find(item.id) == productDetails.end()) {
        productDetails[item.id] = {item.name, item.price}; // Store name and price if not already stored
    }
}

// Print each product row
for (const auto &entry : productDetails) {
    int id = entry.first;
    const string& name = entry.second.first;
    double price = entry.second.second;
    int quantity = productCount[id];  // Quantity for the specific product
    double itemTotal = price * quantity; 
    
     // Total price for that product;

            // Print each product row
            stringstream line;
            line << " | " << setw(5) << id << " | " << setw(15) << name
                 << " | $" << setw(10) << formatPrice(price)
                 << " | " << setw(8) << quantity
                 << " | " << setw(10) << date
                 << " | " << setw(6) << time
                 << " | $" << setw(14) << formatPrice(itemTotal) << " |";

            printCenteredWithTabs(line.str(), consoleWidth);
        }
            
        
    

    // Print total price and quantity
    printCenteredWithTabs(" ======================================================================================================", consoleWidth);
    string totalLine = "Total Price: $" + formatPrice(totalPrice) + " | Total Quantity: " + to_string(totalQuantity);
    printCenteredWithTabs(totalLine, consoleWidth);

    // Print footer
    printCenteredWithTabs(" ======================================================================================================", consoleWidth);
    system("pause");
}



//=======================================================================================================================================
void showCart(const vector<Product> &cart, int consoleWidth)
{
    system("cls");
    displayCart(cart, consoleWidth);
    system("pause");
}

//====================================================================================================================================
// Function to display products by category
void displayProductsByCategory(const vector<Product> &products, const string &category, int consoleWidth)
{
    vector<Product> filteredProducts;
    copy_if(products.begin(), products.end(), back_inserter(filteredProducts),
            [&category](const Product &p)
            { return p.category == category; });

    if (filteredProducts.empty())
    {
        printCenteredWithTabs("No products found in category: " + category, consoleWidth);
    }
    else
    {
        printCenteredWithTabs("Products in Category: " + category, consoleWidth);
        for (const auto &product : filteredProducts)
        {
            string productInfo = "|ID:" + to_string(product.id) + " | Name: " + product.name +
                                 "| Price: $" + formatPrice(product.price) +
                                 "| Description: " + product.description +
                                 "| Category: " + product.category;
            printCenteredWithTabs(" ____________________________________________________________________________", consoleWidth);
            printCenteredWithTabs(productInfo, consoleWidth);
        }
    }
}

//======================================================================================================================================
 void all(){
    
    listProduct drinkList;
     vector<Product> products = {
        {1, "Banana", 0.3, "A healthy fruit.", "fruit"},
        {2, "Orange", 0.5, "A sweet fruit.", "fruit"},
        {3, "Mango", 1, "A tropical fruit.", "fruit"},
        {4, "Pineapple", 1.6, "A juicy fruit.", "fruit"},
        {5, "Coconut", 1.5, "Sweet water.", "drink"},
        {6, "Avocado", 1, "Yummy and sweet.", "fruit"},
        {7, "Papaya", 1.5, "Sweet.", "fruit"},
        {8, "Kiwi", 0.7, "Juicy fruit.", "fruit"},
        {9, "Apple", 0.8, "Sweet and fragile.", "fruit"},
        {10, "Plum", 0.5, "Juicy and sweet.", "fruit"},
        {11, "Sting", 0.5, "Energy drink.", "drink"},
        {12, "Karabav", 0.5, "Energy drink.", "drink"},
        {13, "Red-bull", 0.5, "Energy drink.", "drink"},
        {14, "Monster", 2, "Energy drink.", "drink"},
        {15, "Pepsi", 0.5, "Soft drink.", "drink"},
        {16, "Sprite", 0.5, "Soft drink.", "drink"},
        {17, "Water", 0.3, "Healthy drink.", "drink"},
        {18, "Kit-Kat", 1, "Snack.", "Snack"},
        {19, "Chocolate", 2, "Snack.", "Snack"},
        {20, "Brownie", 1, "Snack.", "snack"},
        {21, "beer", 2, "drink.", "drink"},
        {32, "Hotdog", 1, "snack.", "snack"},
        {33, "chip", 1, "snack.", "snack"},
        {34, "chees", 2, "snack.", "snack"},
        {35, "fries", 1, "snack.", "snack"},
        // Add the rest of your products here...
    };
    //====================================================================================================================================

    vector<Product> cart; // Shopping cart to hold selected products
    int itemsPerPage = 5;
    int totalPages = calculateTotalPages(products, itemsPerPage);
    int currentPage = 1;
    int consoleWidth = getConsoleWidth();

    while (true)
    {
        system("cls"); // Clear the console screen
        displayPage(products, currentPage, itemsPerPage, consoleWidth);
        printCenteredWithTabs("Page " + to_string(currentPage) + " of " + to_string(totalPages), consoleWidth);
        printCenteredWithTabs("Enter 'n' for next page.", consoleWidth);
        printCenteredWithTabs("Enter 'p' for previous page.", consoleWidth);
        printCenteredWithTabs("Enter 'c' to search by category or Type.", consoleWidth);
        printCenteredWithTabs("Enter 'v' to view cart.", consoleWidth);
        printCenteredWithTabs("Enter 'b' to checkout and buy.", consoleWidth);
        printCenteredWithTabs("Enter 'q' to quit.", consoleWidth);
        char command;
        cout << endl;
        cout << "\t\tEnter option:      ";

        //=====================================================================================================================================

        cin >> command;

        if (command == 'n')
        {
            if (currentPage < totalPages)
            {
                currentPage++;
            }
            else
            {
                printCenteredWithTabs("You are on the last page.", consoleWidth);
            }
            //=====================================================================================================================================
        }
       
        else if (command == 'p')
        {
            if (currentPage > 1)
            {
                currentPage--;
            }
            else
            {
                printCenteredWithTabs("You are on the first page.", consoleWidth);
            }
            //================================================================================================================================
        }
        else if (command == 'c')
        {
            string category;
            cout << "Enter category or Type Product:      ";
            cin.ignore();
            getline(cin, category);
            system("cls");
            displayProductsByCategory(products, category, consoleWidth);
            int id;
            cout<<endl;
            cout << "Enter Product ID You want to buy: ";
            cin >> id;
            Product *product = searchProductById(products, id);

            if (product)
            {
                system("cls");
                printCenteredWithTabs("Product found:", consoleWidth);
                string productInfo = "|ID:" + to_string(product->id) + " | Name: " + product->name + " | Price: $" + formatPrice(product->price);
                printCenteredWithTabs(productInfo, consoleWidth);
                char choice;
            cout<<endl;
            cout<<"|==============================================================================================================================|"<<endl;
            cout<<"|                        [a]. Add to Cart                           |                  [b]. Buy                                |"<<endl;
            cout<<"|==============================================================================================================================|"<<endl;   
            cout<<endl;
                    cout<<" Please Choose One [a] or [b] :      ";
                        cin >> choice;

                if (choice == 'a')
                {
                    cart.push_back(*product);
                    cout<<"..............................."<<endl;
                    printCenteredWithTabs("Product added to cart Successfully.", consoleWidth);
                    system("pause");
                }
                else if (choice == 'b')
                {
                    cart.push_back(*product);
                    // drinkList.choice();
                    // cout<<" You Buy it Succesfully, Please Enter and write 'b' to show Receipt......"<<endl;
                    displayCart(cart, consoleWidth);
                    cout<<endl;
                    cout<<" You Buy Successfully. Please Checked Out and Buy Product now,..............."<<endl;
                   
                    system("pause");
                }
            }
//======================================================================================================================================
            else
            {
                printCenteredWithTabs("Product not found.", consoleWidth);
                system("pause");
            }
        }
        else if (command == 'v')
        {
            showCart(cart, consoleWidth);
        }

//=========================================================================================================================================
        else if (command == 'b')
        { // Important
            system("cls");
            int id, quantity;
            double totalPrice = 0.0;
            int totalQuantity = 0;
            cout << "Enter Id Product you want to buy : ";
            cin >> id;

            if (id == 0)
                break;

            // Find the product with the entered ID
            bool productFound = false;
            Product *selectedProduct = nullptr;
            for (auto &product : products)
            {
                if (product.id == id)
                {
                    cout << "Enter quantity for " << product.name << ": ";
                    cin >> quantity;

                    totalPrice = product.price * quantity;
                    totalQuantity +=quantity;
                   ;
                    // Show receipt
                    displayReceipt(cart, consoleWidth, totalPrice, totalQuantity);
                    // cart.clear();
                    drinkList.choice();
                    system("pause");

                    productFound = true;
                    break;
                }
            }
 //==============================================================================================================================           
            if (!productFound)
            {
                cout << "Invalid product ID. Please try again." << endl;
                system("pause");
            }
        }
//=================================================================================================================================        
        else if (command == 'q')
        {
            break;
//=====================================================================================================================================            
        }
        else
        {
            printCenteredWithTabs("Invalid command.", consoleWidth);
            system("pause");
        }
    }


 }
 
//=======================================================================================================================================

void writeToFile() {
    ofstream outFile("productList.txt");

    for (const auto& product : products) {
        outFile << product.id << ", " << product.name << ", " 
                << product.price << ", " << product.description 
                << ", " << product.category << endl;
    }

    outFile.close();
    cout << "Product list saved to file.\n";
}
//=========================================================================================================================================

bool productExists(int id) {
    for (const auto& product : products) {
        if (product.id == id) {
            return true;  // Product with the same ID exists
        }
    }
    return false;
}
//=======================================================================================================================================
void addProduct() {
    Product newProduct;
    
    // Input product details
    cout << "Enter product ID: ";
    cin >> newProduct.id;
    cin.ignore();

    // Check if a product with the same ID already exists
    if (productExists(newProduct.id)) {
        cout << "Error: A product with ID " << newProduct.id << " already exists!\n";
        return;
    }

    cout << "Enter product name: ";
    getline(cin, newProduct.name);
    
    cout << "Enter product price: ";
    cin >> newProduct.price;
    cin.ignore();
    
    cout << "Enter product description: ";
    getline(cin, newProduct.description);
    
    cout << "Enter product category: ";
    getline(cin, newProduct.category);

    // Add the new product to the product list in memory
    products.push_back(newProduct);
    cout << "Product added successfully.\n";
    
    // Open the file in append mode to avoid overwriting existing products
    ofstream outFile("productList.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Could not open the file for writing!\n";
        return;
    }

    // Write the new product details to the file (no spaces around commas)
    outFile << newProduct.id << "," 
            << newProduct.name << "," 
            << newProduct.price << "," 
            << newProduct.description << "," 
            << newProduct.category << endl;

    outFile.close();
    cout << "Product list saved to file.\n";
}


//=======================================================================================================================================

void displayProducts() {
     ifstream inFile("productList.txt");
    if (!inFile) {
        cerr << "Error: Could not open the file!\n";
        return;
    }
   
    products.clear();
 
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Product product;
        string price;

        // Read product information from each line
        getline(ss, line, ','); product.id = stoi(line);
        getline(ss, product.name, ',');
        getline(ss, price, ','); product.price = stod(price);
        getline(ss, product.description, ',');
        getline(ss, product.category, ',');

        // Add the product to the product list
        products.push_back(product);
    }

    inFile.close();
    if (products.empty()) {
        cout << "No products available. Please add or load products.\n";
        return;
    }

    cout << "Product List:\n";
    for (const auto& product : products) {
        cout<<endl;
                         cout<<"|==========================================================================|"<<endl;
                         cout << "ID: " << product.id 
                              << " | Name: " << product.name 
                              << " | Price: $" << product.price 
                              << " | Description: " << product.description 
                              << " | Category: " << product.category << endl;
                         cout<<"|==========================================================================|"<<endl;     
        cout<<endl;                 
    }
}

//=======================================================================================================================================
void deleteProduct() {
    int deleteID;
    cout<<endl;
    cout << "Enter the Product ID you want to delete: ";
    cin >> deleteID;

    // Read all products from the file into a vector
    ifstream inFile("productList.txt");
    if (!inFile) {
        cerr << "Error: Could not open the file for reading!\n";
        return;
    }

    vector<Product> updatedProducts;  // To store products excluding the one to delete
    bool productFound = false;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Product product;
        string price;

        // Read product information
        getline(ss, line, ','); product.id = stoi(line);
        getline(ss, product.name, ',');
        getline(ss, price, ','); product.price = stod(price);
        getline(ss, product.description, ',');
        getline(ss, product.category, ',');

        if (product.id != deleteID) {
            updatedProducts.push_back(product);
        } else {
            productFound = true;
        }
    }

    inFile.close();

    // If the product was not found, notify the user
    if (!productFound) {
        cout << "Product with ID " << deleteID << " not found.\n";
        return;
    }

    // Rewrite the updated product list back to the file
    ofstream outFile("productList.txt");
    if (!outFile) {
        cerr << "Error: Could not open the file for writing!\n";
        return;
    }

    for (const auto& product : updatedProducts) {
        outFile << product.id << "," 
                << product.name << "," 
                << product.price << "," 
                << product.description << "," 
                << product.category << endl;
    }

    outFile.close();
    cout<<endl;
    cout << "Product with ID " << deleteID << " has been successfully deleted...\n";
}
//=======================================================================================================================================

void usercontrol(){
    listProduct list;
    int choice ;
        do {
        firstMenu();
        cin >> choice;
        switch (choice) {
            case 1:
            
                loginRegisterUser();
                break;
            case 2:
                all();
                
                break;
            case 3:
              settingsMenu();
                break;
            case 0:
                cout << "Exiting the program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 0);


}
//=======================================================================================================================================
void saveInputToFile(const std::string& users) {
    std::ofstream outFile(users); // Open the file in write mode

    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

}
//=======================================================================================================================================
void readInputFromFile(const string& users){
    ifstream inFile(users); // Open the file in read mode

    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    string fileContent;
    getline(inFile, fileContent); // Read the content of the file

    cout << "Content of the file: " << fileContent << '\n';
    inFile.close(); // Close the file
}
//=======================================================================================================================================

void admin() {
    string nameadmin, passwordAdmin;
    char ch;
                      cout<<endl;
                                      cout<<"_______________________________________________________"<<endl;
                                      cout<<"|                                                      |"<<endl;
                                      cout<<"|                       Admin Login                    |"<<endl;
                                      cout<<"|______________________________________________________|"<<endl;
                                      cout<<endl;

                                           cout << "          Username: ";
                                           cin >> nameadmin;
                                           cout << "          Password: ";

    // Read password characters one by one
    ch = _getch(); 
    while (ch != 13) { // 13 is Enter key
        passwordAdmin.push_back(ch);
        cout << 'x'; // Mask password input
        ch = _getch();
    }
     cout<<endl;
    
    
    if (nameadmin == "cambo" && passwordAdmin == "1234") {
        cout<<"........................."<<endl;
        cout<<"| Welcome  ,     Admin! |" << endl;
        
        int adminChoice;
        do {

    cout<<endl;
    cout<<"|==============================================================================================================================|"<<endl;
    cout<<"|                                             ADMIN CONTROL                                                                    | "<<endl;
    cout<<"|==============================================================================================================================|"<<endl;
    cout<<"|           [1]. Manage Product                              |    [0].         Logout                                          |"<<endl;
    cout<<"|==============================================================================================================================|"<<endl;        
    cout<<endl;                        
    
            cout << "Enter your choice: ";
            cin >> adminChoice;
            cout<<endl;
            switch (adminChoice) {
                case 1:{
                    int productChoice;
    cout<<endl;
    cout<<"|==============================================================================================================================|"<<endl;
    cout<<"|                                             Manage Product                                                                   | "<<endl;
    cout<<"|==============================================================================================================================|"<<endl;
    cout<<"|  [1]. Add Product         |    [2]. Display Product           |   [3]. Delete Product        |    [4]. Logout                |"<<endl;
    cout<<"|==============================================================================================================================|"<<endl;        
    cout<<endl;
            cout << "Enter your choice:   ";
            cin >> productChoice;

                    switch (productChoice) {
                        case 1:
                             addProduct();
                            break;
                        case 2:
                             displayProducts();
                            break;
                        case 3:
                           deleteProduct();
                            cout << "Deleting product..." << endl;
                            break;
                        case 4:
                            cout << "Logout successful!" << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again!" << endl;
                    }while(productChoice!=4);
                    break;
                }
                    case 2:
                    cout << "Logout successful!" << endl;
                    break;
                    default:
                    cout << "Invalid choice. Please try again!" << endl;
            }
        } while (adminChoice != 0); 
    } else {
        cout << "Invalid admin credentials. Please try again!" << endl;
    }
}
//=======================================================================================================================================

int main() {
    system("cls");
    vector<Product> products; // Store products in a vector
    saveInputToFile("users.txt");
    readInputFromFile("users.txt");


    int option;
    system("Color 0B");
    cout<<R"(

                        
                         __    __     _                            _        
                        / / /\ \ \___| | ___ ___  _ __ ___   ___  | |_ ___  
                        \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \ 
                         \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |
                          \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/                  
)"<<endl;
    Sleep(2000);
    system("cls"); 
    // system("Color 09");
    cout << R"(  

     __                                                       __ _                       _               __           _                 
    /__\     ___ ___  _ __ ___  _ __ ___   ___ _ __ ___ ___  / _\ |__   ___  _ __  _ __ (_)_ __   __ _  / _\_   _ ___| |_ ___ _ __ ___  
   /_\_____ / __/ _ \| '_ ` _ \| '_ ` _ \ / _ \ '__/ __/ _ \ \ \| '_ \ / _ \| '_ \| '_ \| | '_ \ / _` | \ \| | | / __| __/ _ \ '_ ` _ \ 
  //_|_____| (_| (_) | | | | | | | | | | |  __/ | | (_|  __/ _\ \ | | | (_) | |_) | |_) | | | | | (_| | _\ \ |_| \__ \ ||  __/ | | | | |
  \__/      \___\___/|_| |_| |_|_| |_| |_|\___|_|  \___\___| \__/_| |_|\___/| .__/| .__/|_|_| |_|\__, | \__/\__, |___/\__\___|_| |_| |_|
                                                                            |_|   |_|            |___/      |___/                       

)";
              
   do{
                cout<<endl;
                cout<<"______________________________________________________________________________________________________________________"<<endl;
                cout<<"|                                                             |                                                       |"<<endl;
                cout<<"|                         [1]. ADMIN                          |                     [2]. USER                         |"<<endl;
                cout<<"|                                                             |                                                       |"<<endl;
                cout<<"|_____________________________________________________________|_______________________________________________________|"<<endl;
                cout<<endl;

                      cout << "Enter your choice: ";
    cin >> option;
    switch (option) {
        case 1:
            admin();
            break;
        case 2:
            usercontrol();
            break;
        case 0:
            cout<<endl;
            cout << "Exiting the program. Thank you!....." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again!" << endl;
    }
      }while(option!=0);
    
    return 0;   
}