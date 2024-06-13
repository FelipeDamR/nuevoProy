// =========================================================
// File: main.cpp
// Author: Felipe de Jesus Damian Rodriguez
// Date: 12/06/2024
// Description: Main file for project
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <memory>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputFile;
    ofstream outputFile;

    if (argc != 3) {
        cout << "usage: " << argv[0] << " input_file output_file\n";
        return -1;
    }

    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
        cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
        return -1;
    }

    outputFile.open(argv[2]);

    int C, O, N;
    inputFile >> C >> O >> N;

    vector<unique_ptr<Customer>> customers(C);
    vector<unique_ptr<Operator>> operators(O);

    int customerCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < N; ++i) {
        int operation;
        inputFile >> operation;

        if (operation == 1) {
            string name;
            int age, operatorId;
            double limitAmount;
            inputFile >> name >> age >> operatorId >> limitAmount;
            customers[customerCount] = make_unique<Customer>(customerCount, name, age, operators[operatorId].get(), limitAmount);
            customerCount++;
        } else if (operation == 2) {
            int opType;
            double talkingCharge, messageCost, networkCharge, discountRate;
            inputFile >> opType >> talkingCharge >> messageCost >> networkCharge >> discountRate;
            if (opType == 1) {
                operators[operatorCount] = make_unique<VoxOperator>(operatorCount, talkingCharge, messageCost, networkCharge, discountRate, VOX);
            } else if (opType == 2) {
                operators[operatorCount] = make_unique<InternetOperator>(operatorCount, talkingCharge, messageCost, networkCharge, discountRate, INTERNET);
            }
            operatorCount++;
        } else if (operation == 3) {
            int idCustomer1, idCustomer2, time;
            inputFile >> idCustomer1 >> idCustomer2 >> time;
            customers[idCustomer1]->talk(time, *customers[idCustomer2]);
        } else if (operation == 4) {
            int idCustomer1, idCustomer2, quantity;
            inputFile >> idCustomer1 >> idCustomer2 >> quantity;
            customers[idCustomer1]->message(quantity, *customers[idCustomer2]);
        } else if (operation == 5) {
            int idCustomer;
            double amount;
            inputFile >> idCustomer >> amount;
            customers[idCustomer]->connection(amount);
        } else if (operation == 6) {
            int idCustomer;
            double amount;
            inputFile >> idCustomer >> amount;
            customers[idCustomer]->pay(amount);
        } else if (operation == 7) {
            int idCustomer, idOperator;
            inputFile >> idCustomer >> idOperator;
            customers[idCustomer]->setOperator(operators[idOperator].get());
        } else if (operation == 8) {
            int idCustomer;
            double newLimit;
            inputFile >> idCustomer >> newLimit;
            customers[idCustomer]->getBill()->changeTheLimit(newLimit);
        }
    }

    for (const auto& op : operators) {
        if (op != nullptr) {
            outputFile << op->toString() << endl;
        }
    }

    for (const auto& cust : customers) {
        if (cust != nullptr) {
            outputFile << cust->toString() << endl;
        }
    }

    string maxTalkCustomer, maxMessageCustomer, maxInternetCustomer;
    int maxTalkTime = 0, maxMessages = 0;
    double maxInternet = 0.0;

    for (const auto& cust : customers) {
        if (cust != nullptr) {
            if (cust->getTotalSpentTalkingTime() > maxTalkTime) {
                maxTalkTime = cust->getTotalSpentTalkingTime();
                maxTalkCustomer = cust->getName();
            }
            if (cust->getTotalMessageSent() > maxMessages) {
                maxMessages = cust->getTotalMessageSent();
                maxMessageCustomer = cust->getName();
            }
            if (cust->getTotalInternetUsage() > maxInternet) {
                maxInternet = cust->getTotalInternetUsage();
                maxInternetCustomer = cust->getName();
            }
        }
    }

    outputFile << maxTalkCustomer << ": " << maxTalkTime << endl;
    outputFile << maxMessageCustomer << ": " << maxMessages << endl;
    outputFile << maxInternetCustomer << ": " << maxInternet << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}
