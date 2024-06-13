// =========================================================
// File: bill.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 12/06/2024
// Description: Header file for Bill class
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill {
private:
    double limitAmount;
    double currentDebt;
    double totalMoneySpent;

public:
    Bill() : limitAmount(0), currentDebt(0), totalMoneySpent(0) {}
    Bill(double limit) : limitAmount(limit), currentDebt(0), totalMoneySpent(0) {}
    Bill(const Bill &other) : limitAmount(other.limitAmount), currentDebt(other.currentDebt), totalMoneySpent(other.totalMoneySpent) {}

    double getLimitAmount() const { return limitAmount; }
    double getCurrentDebt() const { return currentDebt; }
    double getTotalMoneySpent() const { return totalMoneySpent; }

    void add(double amount) {
        if (amount > 0) {
            currentDebt += amount;
        }
    }

    void pay(double amount) {
        if (amount > 0 && amount <= currentDebt) {
            currentDebt -= amount;
            totalMoneySpent += amount;
        }
    }

    void changeTheLimit(double amount) {
        if (amount > 0 && amount > currentDebt) {
            limitAmount = amount;
        }
    }

    bool check(double amount) const {
        return (currentDebt + amount <= limitAmount);
    }
};

#endif // BILL_H
