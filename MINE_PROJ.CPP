#include <iostream>
#include <string>
using namespace std;

// Base Class: Transaction
// Demonstrates Encapsulation + Polymorphism

class Transaction
{
protected:
    string category;
    float amount;
    string date; // format: month name or number (for simplicity)
public:
    // Constructor
    Transaction(string cat = "", float amt = 0.0, string dt = "")
        : category(cat), amount(amt), date(dt) {} // for assigning values in data member when we pass ,
                                                  //    time of object creation is same as
                                                  //  category = cat;amount = amt;date = dt;

    // Virtual function (for Polymorphism)
    virtual void display()
    {
        cout << "Category: " << category << ", Amount: " << amount << ", Date: " << date << endl;
    }

    // Getters for Encapsulation
    float getAmount() { return amount; }
    string getCategory() { return category; }
    string getDate() { return date; }

    // Virtual function for transaction type
    virtual string getType() = 0; // pure virtual → makes class abstract
};

// Derived Class: Income
// Demonstrates Inheritance

class Income : public Transaction
{
public:
    Income(string cat, float amt, string dt) : Transaction(cat, amt, dt) {}

    void display() override
    {
        cout << "[INCOME] Category: " << category
             << ", Amount: +" << amount
             << ", Date: " << date << endl;
    }

    string getType() override
    {
        return "Income";
    }
};

// Derived Class: Expense
// Demonstrates Inheritance

class Expense : public Transaction
{
public:
    Expense(string cat, float amt, string dt) : Transaction(cat, amt, dt) {}

    void display() override
    {
        cout << "[EXPENSE] Category: " << category
             << ", Amount: -" << amount
             << ", Date: " << date << endl;
    }

    string getType() override
    {
        return "Expense";
    }
};

// Class: Budget (Additional object to represent monthly goal)

class Budget
{
private:
    float limit;

public:
    Budget(float l = 0.0) : limit(l) {}

    void setLimit(float l)
    {
        limit = l;
    }

    float getLimit()
    {
        return limit;
    }

    void checkBudget(float totalExpense)
    {
        cout << "\nYour budget limit: " << limit << endl;
        cout << "Total Expense: " << totalExpense << endl;
        if (totalExpense > limit)
            cout << " You have exceeded your budget!\n";
        else
            cout << " You are within your budget.\n";
    }
};

// Class: Account (Abstraction)
// Combines all functionalities and hides complex details

class Account
{
private:
    Transaction *transactions[100]; // store up to 100 transactions
    int count;
    Budget budget;

public:
    Account()
    {
        count = 0;
    }

    void setBudget()
    {
        float l;
        cout << "Enter your monthly budget limit: ";
        cin >> l;
        budget.setLimit(l);
        cout << "Budget set successfully!\n";
    }

    void addTransaction()
    {
        int choice;
        cout << "\n1. Add Income\n2. Add Expense\nChoose option: ";
        cin >> choice;

        string cat, dt;
        float amt;
        cout << "Enter category (e.g. food, rent, travel): ";
        cin >> cat;
        cout << "Enter amount: ";
        cin >> amt;
        cout << "Enter month (e.g. October or 10): ";
        cin >> dt;

        if (choice == 1)
            transactions[count++] = new Income(cat, amt, dt);
        else
            transactions[count++] = new Expense(cat, amt, dt);

        cout << "Transaction added successfully!\n";
    }

    void showAll()
    {
        if (count == 0)
        {
            cout << "No transactions available.\n";
            return;
        }
        cout << "\n--- All Transactions ---\n";
        for (int i = 0; i < count; i++)
        {
            transactions[i]->display(); // Polymorphism in action
        }
    }

    void monthlyReport()
    {
        string month;
        cout << "Enter month to generate report: ";
        cin >> month;

        float totalIncome = 0, totalExpense = 0;

        for (int i = 0; i < count; i++)
        {
            if (transactions[i]->getDate() == month)
            {
                if (transactions[i]->getType() == "Income")
                    totalIncome += transactions[i]->getAmount();
                else
                    totalExpense += transactions[i]->getAmount();
            }
        }

        cout << "\n----- Monthly Report (" << month << ") -----\n";
        cout << "Total Income : +" << totalIncome << endl;
        cout << "Total Expense: -" << totalExpense << endl;
        cout << "Savings      : " << (totalIncome - totalExpense) << endl;

        budget.checkBudget(totalExpense);
    }
};


// Main Function (Simple CLI Interface)
// Demonstrates Abstraction through menu


int main()
{
    Account acc;
    int choice;

    cout << "---- PERSONAL FINANCE TRACKER ----\n";

    do
    {
        cout << "\n1. Set Monthly Budget\n2. Add Transaction\n3. Show All Transactions\n4. Generate Monthly Report\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            acc.setBudget();
            break;
        case 2:
            acc.addTransaction();
            break;
        case 3:
            acc.showAll();
            break;
        case 4:
            acc.monthlyReport();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
