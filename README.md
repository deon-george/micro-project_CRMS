# 💼 Customer Interaction System (SQLite)

A simple terminal-based **C program** for managing customer records using **SQLite** as the local database.  
You can add, view, update, and delete customers — perfect for small CRM-style systems or for learning database handling in C.


## 🚀 Features

- 📇 Add new customers with full name, email, and phone number  
- 🔍 View individual customer details using their email  
- 📋 View all customers in a formatted list  
- ✏️ Update customer records  
- ❌ Delete customers by email  
- 💾 SQLite database automatically initialized (`customers.db`)

## 🧠 Tech Stack

- **Language:** C  
- **Database:** SQLite  
- **Tested On:** Fedora 42 (Fish Shell), Ubuntu 24.04, Windows 10/11  

## ⚙️ Setup Instructions

### 🐧 Fedora / Linux (Fish or Bash)

1. **Install SQLite and development tools**
   ```bash
   sudo dnf install sqlite sqlite-devel
````

2. **Clone the repository**

   ```bash
   git clone https://github.com/<your-username>/<your-repo-name>.git
   cd <your-repo-name>
   ```

3. **Compile the program**

   ```bash
   gcc -o customer_app customer_app.c -lsqlite3
   ```

4. **Run it**

   ```bash
   ./customer_app
   ```

---

### 🐧 Ubuntu / Debian

1. **Install required packages**

   ```bash
   sudo apt update
   sudo apt install sqlite3 libsqlite3-dev build-essential
   ```

2. **Clone and build**

   ```bash
   git clone https://github.com/<your-username>/<your-repo-name>.git
   cd <your-repo-name>
   gcc -o customer_app customer_app.c -lsqlite3
   ```

3. **Run the app**

   ```bash
   ./customer_app
   ```

---

### 🪟 Windows (Using MinGW or Code::Blocks)

1. **Install dependencies**

   * Download and install **SQLite** from:
     👉 [https://www.sqlite.org/download.html](https://www.sqlite.org/download.html)
   * Install **MinGW** or use **Code::Blocks** IDE.

2. **If using MinGW (CMD or PowerShell):**

   ```bash
   gcc -o customer_app.exe customer_app.c -lsqlite3
   ```

   Make sure `sqlite3.dll` is either in the same folder as your `.exe` or in your system path.

3. **Run the program**

   ```bash
   ./customer_app.exe
   ```

---

## 🧩 Menu Options

| Option | Description           |
| -----: | --------------------- |
|      1 | Add Customer          |
|      2 | View Customer Details |
|      3 | View All Customers    |
|      4 | Update Customer       |
|      5 | Delete Customer       |
|      6 | Exit                  |

---

## 🗂 Database Schema

| Column | Type                  | Description              |
| ------ | --------------------- | ------------------------ |
| id     | INTEGER (Primary Key) | Auto-incremented ID      |
| name   | TEXT                  | Customer full name       |
| email  | TEXT                  | Unique customer email    |
| phone  | TEXT                  | Contact number           |
| isLead | INTEGER               | 1 → Lead, 0 → Not a lead |

---

## 🧰 Example Run

```
--- Customer Interaction System (SQLite) ---
1. Add Customer
2. View Customer Details
3. View All Customers
4. Update Customer
5. Delete Customer
6. Exit
Enter your choice: 1
Enter full name: John Doe
Enter customer email: john@example.com
Enter customer phone: 9876543210
Is this customer a lead? (1 for yes, 0 for no): 1
Customer added successfully!
```

---

## 🧑‍💻 Developer Notes

* The `customers.db` file is automatically created in the current directory.
* All SQL operations use **prepared statements** for safety and performance.
* Email field is **unique** — duplicate entries are prevented.
* Works cross-platform (Linux, macOS, Windows).

---

## 🏁 License

This project is released under the **MIT License** — feel free to use, modify, and distribute it.

---

## 👤 Author

**Deon George**
