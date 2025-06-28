#include "OrderBookEntry.h"
#include <string>

using namespace std;

OrderBookEntry::OrderBookEntry(double _price, double _amount, string _timestamp, string _product, OrderBookType _orderType, string _username)
: price(_price), amount(_amount), timestampe(_timestamp), product(_product), Ordertype(_orderType), username(_username)
{
    cout << "🔍 Debug: Inside Constructor" << endl;
    cout << "Input Price: " << _price << " | Stored Price: " << price << endl;
    cout << "Input Amount: " << _amount << " | Stored Amount: " << amount << endl;
}



//OrderBookEntry::OrderBookEntry() : price(0.0), amount(0.0), timestampe(""), product(""), Ordertype(_orderbooktype) {}

OrderBookType OrderBookEntry::stringToOBT(string s){

    if(s == "ask"){
        return OrderBookType::ask;
    }
    if(s == "bid"){
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;

}

bool OrderBookEntry::comparebyTimestamp(OrderBookEntry& e1, OrderBookEntry& e2){
        
    return e1.timestampe < e2.timestampe;
}

bool OrderBookEntry::comparebyPriceAse(OrderBookEntry& e1, OrderBookEntry& e2){
        
    return e1.price < e2.price;
}
bool OrderBookEntry::comparebyPriceDec(OrderBookEntry& e1, OrderBookEntry& e2){
        
    return e1.price > e2.price;
}