# CamboBuy: An E-Commerce Shopping System 🛒

CamboBuy is a console-based e-commerce application built in C++. It allows users to browse products, add items to a shopping cart, and manage their accounts. The system includes both user and admin functionalities, with data persistence for users and products handled via text files.

## ✨ Features

- **User Authentication**: Register, log in, and manage user accounts.
- **Password Management**: Features for changing and recovering forgotten passwords.
- **Product Catalog**: Browse products in a paginated list.
- **Search & Filter**: Search products by category.
- **Shopping Cart**: Add items to a cart, view its contents, and proceed to checkout.
- **Payment Options**: Supports both cash and QR code payments (simulated).
- **Admin Panel**: A secure admin login to manage products, including adding, displaying, and deleting items from the catalog.
- **Data Persistence**: User and product data are saved to and loaded from text files (`users.txt` and `productList.txt`).

## 🛠️ How to Compile and Run

### Prerequisites

You need a C++ compiler installed on your system, such as **g++** (part of GCC).

### Compilation

Open your terminal or command prompt in the project directory and run the following command to compile all source files:

```sh
g++ Main.cpp admin.cpp product_management.cpp user_auth.cpp -o Main
