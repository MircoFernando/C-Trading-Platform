#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"
using namespace std;


class Wallet
{
private:
    /* data */
    map<string,double> currency;

public:
    Wallet();
    void insertCurrency(string type, double amount);
    bool removeCurrency(string type, double amount);
    bool containCurrency(string type, double amount);
    bool canfulfillOrder(OrderBookEntry order);
    string toString();
    void processSales(OrderBookEntry& sale);
    

};


