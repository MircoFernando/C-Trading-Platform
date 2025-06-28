#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CVSReader 
{
    public:
        CVSReader();

        static vector<OrderBookEntry> readCSV(string csvfile);
        static vector<string> tokenise(string cvsline, char separator);
        static OrderBookEntry stringstoOBE(string price, string amount, string timestamp, string product, OrderBookType OrderBookType);

    private:
        
        static OrderBookEntry stringstoOBE(vector<string> strings);



};