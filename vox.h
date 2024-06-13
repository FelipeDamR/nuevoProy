// =========================================================
// File: vox_operator.h
// Author: Felipe de Jesus Damian Rodrigue
// Date: 12/06/2024
// Description: Header file for VoxOperator class
// =========================================================

#ifndef VOX_OPERATOR_H
#define VOX_OPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
    VoxOperator(int id, double talkingCharge, double messageCost, double networkCharge, double discountRate, OperatorType type)
        : Operator(id, talkingCharge, messageCost, networkCharge, discountRate, type) {}

    VoxOperator(const VoxOperator &other)
        : Operator(other) {}

    double calculateTalkingCost(int minutes, int age) override {
        if (minutes <= 0 || age <= 0) {
            return 0;
        }
        double cost = minutes * getTalkingCharge();
        if (age < 18 || age > 65) {
            cost *= (1 - getDiscountRate());
        }
        return cost;
    }

    double calculateMessageCost(int quantity, int thisOpId, int otherOpId) override {
        if (quantity <= 0) {
            return 0;
        }
        double cost = quantity * getMessageCost();
        if (thisOpId != otherOpId) {
            cost *= (1 - getDiscountRate());
        }
        return cost;
    }

    double calculateNetworkCost(double amount) override {
        if (amount <= 0) {
            return 0;
        }
        return amount * getNetworkCharge();
    }
};

#endif // VOX_OPERATOR_H
