#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBookEntry.cpp"
#include "OrderBook.h"
#include "OrderBook.cpp"
#include "tradingmain.cpp"
#include "tradingmain.h"
#include "CSVreader.h"
#include "CSVreader.cpp"
#include "Wallet.h"
#include "Wallet.cpp"

using namespace std;




// check when converting to string to double





int main ()
{
    

    TradingMain cal;

    

     cal.init();

     /*INSTRUCTIONS TO USE THE TRADING SYSTEM*/

     /**
      * PLACEASK --> CURRENCY-A/CURRENCY-B (LOSING CURRENCY A/GAINING CURRENCY B)
      * PLACEASK --> CURRENCY-A/CURRENCY-B (GAINING CURRENCY A/LOSING CURRENCY B)
      */

    // Wallet wallet;
    // wallet.insertCurrency("BTC", 10);
    // wallet.insertCurrency("USDT", 10000);
    
    // cout << wallet.toString() << endl;
    // wallet.removeCurrency("USDT", 1000);
    // cout << wallet.toString() << endl;
   // CVSReader reader;
    
//    Wallet wallet{};
//    std::cout << "Inserting 100 BTC" << std::endl;
//    wallet.insertCurrency("BTC", 10); 4

//    std::cout << "Wallet contents " << wallet.toString() << std::endl; 

}

