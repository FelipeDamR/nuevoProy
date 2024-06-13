// =========================================================
// File: operator.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 12/06/2024
// Description: Header file for Operator class
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

typedef enum { VOX, INTERNET } OperatorType;

class Operator {
protected:
    int id;
    double talkingCharge, messageCost, networkCharge, discountRate;
    int totalSpentTalkingTime, totalMessageSent;
    double totalInternetUsage;
    OperatorType type;

public:
    Operator(int id, double talkingCharge, double messageCost, double networkCharge, double discountRate, OperatorType type)
        : id(id), talkingCharge(talkingCharge), messageCost(messageCost), networkCharge(networkCharge), discountRate(discountRate),
          totalSpentTalkingTime(0), totalMessageSent(0), totalInternetUsage(0), type(type) {}

    Operator(const Operator& other)
        : id(other.id), talkingCharge(other.talkingCharge), messageCost(other.messageCost), networkCharge(other.networkCharge),
          discountRate(other.discountRate), totalSpentTalkingTime(other.totalSpentTalkingTime), totalMessageSent(other.totalMessageSent),
          totalInternetUsage(other.totalInternetUsage), type(other.type) {}

    virtual ~Operator() = default;

    int getId() const { return id; }
    double getTalkingCharge() const { return talkingCharge; }
    double getMessageCost() const { return messageCost; }
    double getNetworkCharge() const { return networkCharge; }
    double getDiscountRate() const { return discountRate; }
    int getTotalSpentTalkingTime() const { return totalSpentTalkingTime; }
    int getTotalMessageSent() const { return totalMessageSent; }
    double getTotalInternetUsage() const { return totalInternetUsage; }
    OperatorType getType() const { return type; }

    void addTalkingTime(int minutes) {
        if (minutes > 0) {
            totalSpentTalkingTime += minutes;
        }
    }

    void addTotalMessageSent(int quantity) {
        if (quantity > 0) {
            totalMessageSent += quantity;
        }
    }

    void addTotalInternetUsage(double amount) {
        if (amount > 0) {
            totalInternetUsage += amount;
        }
    }

    virtual double calculateTalkingCost(int minutes, int age) = 0;
    virtual double calculateMessageCost(int quantity, int thisOpId, int otherOpId) = 0;
    virtual double calculateNetworkCost(double amount) = 0;

    std::string toString() const {
        std::stringstream ss;
        ss << "Operator #" << id << " : " << totalSpentTalkingTime << " " << totalMessageSent << " " << std::fixed << std::setprecision(2) << totalInternetUsage;
        return ss.str();
    }
};

#endif // OPERATOR_H
