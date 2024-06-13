// =========================================================
// File: internet_operator.h
// Author: Felipe de Jesus Damian Rodriguez
// Date: 12/06/2024
// Description: Header file for InternetOperator class
// =========================================================

#ifndef INTERNET_OPERATOR_H
#define INTERNET_OPERATOR_H

#include "operator.h"

class InternetOperator : public Operator {
private:
    const double LIMITGB = 1.0;

public:
    InternetOperator(int id, double talkingCharge, double messageCost, double networkCharge, double discountRate, OperatorType type)
        : Operator(id, talkingCharge, messageCost, networkCharge, discountRate, type) {}

    InternetOperator(const InternetOperator &other)
        : Operator(other) {}

    double calculateTalkingCost(int minutes, int age) override {
        if (minutes <= 0 || age <= 0) {
            return 0;
        }
        double cost = minutes * getTalkingCharge();
        if (minutes < 2) {
            cost *= (1 - getDiscountRate());
        }
        return cost;
    }

    double calculateMessageCost(int quantity, int thisOpId, int otherOpId) override {
        if (quantity <= 0) {
            return 0;
        }
        double cost = quantity * getMessageCost();
        if (quantity < 3) {
            cost *= (1 - getDiscountRate());
        }
        return cost;
    }

    double calculateNetworkCost(double amount) override {
        if (amount <= 0) {
            return 0;
        }
        if (amount <= LIMITGB) {
            return 0;
        }
        return (amount - LIMITGB) * getNetworkCharge();
    }
};

#endif // INTERNET_OPERATOR_H
