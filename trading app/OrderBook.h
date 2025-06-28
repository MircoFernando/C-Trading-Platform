#pragma once
#include "OrderBook.h"
#include "CSVreader.h"
#include <string>
#include <vector>

class OrderBook
{
private:
    vector<OrderBookEntry> orders;
public:
    OrderBook(string filename);
    vector<string> GetKnownProduct();
    vector<OrderBookEntry> GetOrders(OrderBookType type, string product, string timestamp);
                                                                                                                                                                
    string getEarliestTime();
    string getNextTime(string timestamp);
    static double GetAverage(vector<OrderBookEntry>& orders);
    void insertOrder(OrderBookEntry& order);
    vector<OrderBookEntry> matchAskstoBids(string product, string timestamp);
    //static double getPrice(vector<OrderBookEntry>& orders);
    // static double getHighPrice(vector<OrderBookEntry>& orders);
    //static double getlowPrice(vector<OrderBookEntry>& orders);


    
};


