#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

// Initialize the database (create table if not exists)
void initializeDatabase(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS customers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "email TEXT UNIQUE NOT NULL,"
        "phone TEXT NOT NULL,"
        "isLead INTEGER NOT NULL);";

    char *errMsg = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Error creating table: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Database initialized successfully.\n");
    }
}

// Add a new customer
void addCustomer(sqlite3 *db) {
    char name[100], email[100], phone[20];
    int isLead;

    getchar(); // clear leftover newline from previous scanf
    printf("Enter full name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline

    printf("Enter customer email: ");
    scanf("%99s", email);
    printf("Enter customer phone: ");
    scanf("%19s", phone);
    printf("Is this customer a lead? (1 for yes, 0 for no): ");
    scanf("%d", &isLead);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO customers (name, email, phone, isLead) VALUES (?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, phone, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, isLead);

        if (sqlite3_step(stmt) == SQLITE_DONE)
            printf("Customer added successfully!\n");
        else
            printf("Error adding customer (email might already exist).\n");

        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement.\n");
    }
}

// View a customer by email
void viewCustomerDetails(sqlite3 *db) {
    char email[100];
    printf("Enter customer email to view details: ");
    scanf("%99s", email);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT name, email, phone, isLead FROM customers WHERE email = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("\nCustomer Details:\n");
            printf("Name: %s\n", sqlite3_column_text(stmt, 0));
            printf("Email: %s\n", sqlite3_column_text(stmt, 1));
            printf("Phone: %s\n", sqlite3_column_text(stmt, 2));
            printf("Lead Status: %s\n",
                   sqlite3_column_int(stmt, 3) ? "Lead" : "Not a Lead");
        } else {
            printf("Customer with email '%s' not found.\n", email);
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement.\n");
    }
}

// View all customers
void viewAllCustomers(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT name, email, phone, isLead FROM customers;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("\n%-20s %-25s %-15s %-10s\n", "Name", "Email", "Phone", "Lead");
        printf("--------------------------------------------------------------------------\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("%-20s %-25s %-15s %-10s\n",
                   sqlite3_column_text(stmt, 0),
                   sqlite3_column_text(stmt, 1),
                   sqlite3_column_text(stmt, 2),
                   sqlite3_column_int(stmt, 3) ? "Yes" : "No");
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement for viewing all customers.\n");
    }
}

// Update a customer's details
void updateCustomer(sqlite3 *db) {
    char email[100], newName[100], newPhone[20];
    int newIsLead;

    printf("Enter email of customer to update: ");
    scanf("%99s", email);

    getchar(); // clear newline
    printf("Enter New Name (full name): ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0'; // remove newline

    printf("Enter new phone: ");
    scanf("%19s", newPhone);
    printf("Is this customer a lead? (1 for yes, 0 for no): ");
    scanf("%d", &newIsLead);

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE customers SET name=?, phone=?, isLead=? WHERE email=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, newName, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, newPhone, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, newIsLead);
        sqlite3_bind_text(stmt, 4, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0)
            printf("Customer updated successfully!\n");
        else
            printf("Customer with email '%s' not found.\n", email);

        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare update statement.\n");
    }
}

// Delete a customer
void deleteCustomer(sqlite3 *db) {
    char email[100];
    printf("Enter email of customer to delete: ");
    scanf("%99s", email);

    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM customers WHERE email=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0)
            printf("Customer deleted successfully!\n");
        else
            printf("Customer with email '%s' not found.\n", email);

        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare delete statement.\n");
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("customers.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    initializeDatabase(db);

    int choice;
    while (1) {
        printf("\n--- Welcome to Deon's Shop :) ---\n");
        printf("1. Add Customer\n");
        printf("2. View Customer Details\n");
        printf("3. View All Customers\n");
        printf("4. Update Customer\n");
        printf("5. Delete Customer\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer(db);
                break;
            case 2:
                viewCustomerDetails(db);
                break;
            case 3:
                viewAllCustomers(db);
                break;
            case 4:
                updateCustomer(db);
                break;
            case 5:
                deleteCustomer(db);
                break;
            case 6:
                printf("Exiting. Have a great day!\n");
                sqlite3_close(db);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}
