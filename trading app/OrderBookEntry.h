#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class OrderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry
{
    public:
   OrderBookEntry();
    OrderBookEntry(double _price, double _amount, string _timestamps, string _product, OrderBookType _orderbooktype, string username = "dataset");

    static OrderBookType stringToOBT(string s);

    static bool comparebyTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);

    static bool comparebyPriceAse(OrderBookEntry& e1, OrderBookEntry& e2);\
    static bool comparebyPriceDec(OrderBookEntry& e1, OrderBookEntry& e2);
        
   
    
    double price;
    double amount;
    string timestampe;
    string product;
    OrderBookType Ordertype;
    string username;
    
};
