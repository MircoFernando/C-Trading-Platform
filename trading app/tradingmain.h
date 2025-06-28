#pragma once
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

using namespace std;

class TradingMain{

    public: 
    TradingMain();
    void init();

    private: 
    
    void LoadOrderBook();
    void DisplayMenu();
    
    int getUserOption();
    void PrintHelp();
    void PrintExStats();
    void PlaceAsk();
    void Placebid();
    void PrintWallet();
    void Continue();
    void ProcessUseroption(int userOption);
    double computeAveragePrice(std::vector<OrderBookEntry>& entries);
    double computeLowPrice(std::vector<OrderBookEntry>& entries);
    double computeHighPrice(std::vector<OrderBookEntry>& entries);
    double computePriceSpread(std::vector<OrderBookEntry>& entries);

    string currentTime;

    OrderBook orderBook{"1XejnIsmSmK3o5yLJkpiUg_2402656ae54246e880715f135341f5f7_20200317.csv"};
    
    Wallet wallet;



};
