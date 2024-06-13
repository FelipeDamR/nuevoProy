// =========================================================
// File: customer.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 12/06/2024
// Description: Header file for Customer class
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "operator.h"
#include "bill.h"

class Customer {
private:
    int id;
    std::string name;
    int age;
    int totalSpentTalkingTime;
    int totalMessageSent;
    double totalInternetUsage;
    Operator* op;
    Bill* bill;

public:
    Customer(int id, const std::string& name, int age, Operator* op, double limitAmount)
        : id(id), name(name), age(age), totalSpentTalkingTime(0), totalMessageSent(0), totalInternetUsage(0), op(op) {
        bill = new Bill(limitAmount);
    }

    Customer(const Customer &other)
        : id(other.id), name(other.name), age(other.age), totalSpentTalkingTime(other.totalSpentTalkingTime),
          totalMessageSent(other.totalMessageSent), totalInternetUsage(other.totalInternetUsage), op(other.op),
          bill(new Bill(*other.bill)) {}

    ~Customer() {
        delete bill;
    }

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getTotalSpentTalkingTime() const { return totalSpentTalkingTime; }
    int getTotalMessageSent() const { return totalMessageSent; }
    double getTotalInternetUsage() const { return totalInternetUsage; }
    Operator* getOperator() const { return op; }
    Bill* getBill() const { return bill; }

    void setOperator(Operator* newOperator) {
        op = newOperator;
    }

    void talk(int minutes, Customer &other) {
        double cost = op->calculateTalkingCost(minutes, age);
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTalkingTime(minutes);
            totalSpentTalkingTime += minutes;
            other.totalSpentTalkingTime += minutes;
        }
    }

    void message(int quantity, const Customer &other) {
        double cost = op->calculateMessageCost(quantity, op->getId(), other.getOperator()->getId());
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTotalMessageSent(quantity);
            totalMessageSent += quantity;
        }
    }

    void connection(double amount) {
        double cost = op->calculateNetworkCost(amount);
        if (bill->check(cost)) {
            bill->add(cost);
            op->addTotalInternetUsage(amount);
            totalInternetUsage += amount;
        }
    }

    void pay(double amount) {
        bill->pay(amount);
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Customer #" << id << " : " << totalSpentTalkingTime << " " << totalMessageSent << " " << std::fixed << std::setprecision(2) << totalInternetUsage;
        return ss.str();
    }
};

#endif // CUSTOMER_H
