#include <iostream>
#include <vector>
#include <limits>
#include "OrderBookEntry.h"
#include "tradingmain.h"
#include "CSVreader.h"
using namespace std;

TradingMain::TradingMain(){

}
void TradingMain::init(){

 //   LoadOrderBook();
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
    
   
    DisplayMenu();
    int UserOption = getUserOption();
    ProcessUseroption(UserOption);

   
    }

}
// void TradingMain::LoadOrderBook(){

//     orders =  CVSReader::readCSV("1XejnIsmSmK3o5yLJkpiUg_2402656ae54246e880715f135341f5f7_20200317.csv");

// }

    
double TradingMain::computeAveragePrice(std::vector<OrderBookEntry>& entries){

    double total_price;
    double count;
    double average;

    for(int i = 0; i < entries.size(); ++i)
    {
        total_price = total_price + entries[i].price;
        count = count + i;
    }

    return average = total_price / count;

}
double TradingMain::computeLowPrice(std::vector<OrderBookEntry>& entries)
{
   
        double lowest = entries[0].price;
        for (size_t i = 1; i < entries.size(); ++i) {
            if (entries[i].price < lowest) {
                lowest = entries[i].price;
            }
        }
        return lowest;
}
double TradingMain::computeHighPrice(std::vector<OrderBookEntry>& entries)
{
    double highest = entries[0].price;
        for (size_t i = 1; i < entries.size(); ++i) {
            if (entries[i].price > entries[i-1].price) {
                highest = entries[i].price;
            }
        }
        return highest;
}

double TradingMain::computePriceSpread(std::vector<OrderBookEntry>& entries)
{
    //cout << computeHighPrice(entries) << endl;
   // cout << computeLowPrice(entries) << endl;

    double difference;

    difference = computeHighPrice(entries) - computeLowPrice (entries); 
    return difference;

}



void TradingMain::DisplayMenu(){
    cout << "1. print help" << endl;
    cout << "2. Print exchange stats" << endl;
    cout << "3. Place an ask" << endl;
    cout << "4. Place a bid" << endl;
    cout << "5. Print wallet" << endl;
    cout << "6. Continue" << endl;
    cout << "Current Time: " << currentTime << endl;
    cout << endl;
    

}
int TradingMain::getUserOption()
{
    int Useroption = 0;
    string line;
    cout << "Type in 1-6" << std::endl;
    getline(cin, line);
    try{
    Useroption = stoi(line);
    }catch(const exception& e)
    {
        //
    }
    cout << "You chose: " << Useroption << endl;
    return Useroption;
}
void TradingMain::PrintHelp(){
    std::cout << "Help- choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;

}
void TradingMain::PrintExStats(){

    //vector<OrderBookEntry> entries;

    for(string const s : orderBook.GetKnownProduct())
    {
        cout << "Products: " << s << endl;
        vector<OrderBookEntry> asks = orderBook.GetOrders(OrderBookType::ask, s, currentTime);
        cout << "Asks: " << asks.size() << endl;
        cout << "Average asks: " << OrderBook::GetAverage(asks) << endl;

        vector<OrderBookEntry> bids = orderBook.GetOrders(OrderBookType::bid, s, currentTime);
        cout << "Bids: " << bids.size() << endl;
        cout << "Average Bids: " << OrderBook::GetAverage(bids) << endl;
        
        //cout << "Max asks: " << OrderBook::getHighPrice(entries) << endl;
        //cout << "Lowest asks: " << OrderBook::getlowPrice(entries) << endl;
    }
    
    
    // cout << "You have choosen Print exchange stats" << endl;
    // //LoadOrderBook(); 
    // cout << "Total entries: " << orders.size() << endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    
    // for(OrderBookEntry& e : orders){
    //     if(e.Ordertype == OrderBookType::ask){
    //         asks ++;
    //     }
    //     if(e.Ordertype == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }
    // } 
    // cout << "Asks: " << asks << "Bids: " << bids << endl;

}
void TradingMain::Placebid(){
    cout << "You have chosen to place a bid" << endl;

    cout << "Enter: product, price, amount" << endl;
    string input;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    vector<string> tokens = CVSReader::tokenise(input, ',');

    // 🔍 Debugging: Print each token
    cout << "Tokens found: " << tokens.size() << endl;
    for (size_t i = 0; i < tokens.size(); i++) {
    cout << "Token " << i + 1 << ": [" << tokens[i] << "]" << endl;
    }
    if(tokens.size() != 3)
    {
        cout << "Bad input"  << input <<  endl;
    }
    else{
        try{
    OrderBookEntry obe = CVSReader::stringstoOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
    obe.username = "simuser";
    if (wallet.canfulfillOrder(obe))
    {
        cout << "Wallet is sufficient" << endl;
        orderBook.insertOrder(obe);
    }
    else {
        cout << "Wallet has insufficient amount" << endl;
    }
     
   
     
    }catch (const exception& e)
    {
        	cout << "Place bid: Bad input!!!" << endl;
    }
    
    cout << "You entered: "  << input <<  endl;
    }

}
    


void TradingMain::PlaceAsk(){
    cout << "You have chosen to place a ask" << endl;
    cout << "Enter: product, price, amount" << endl;
    string input;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    vector<string> tokens = CVSReader::tokenise(input, ',');

    // 🔍 Debugging: Print each token
    cout << "Tokens found: " << tokens.size() << endl;
    for (size_t i = 0; i < tokens.size(); i++) {
    cout << "Token " << i + 1 << ": [" << tokens[i] << "]" << endl;
    }
    if(tokens.size() != 3)
    {
        cout << "Bad input"  << input <<  endl;
    }
    else{
        try{
    OrderBookEntry obe = CVSReader::stringstoOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
    obe.username = "simuser";
    if (wallet.canfulfillOrder(obe))
    {
        cout << "Wallet is sufficient" << endl;
        orderBook.insertOrder(obe);
    }
    else {
        cout << "Wallet has insufficient amount" << endl;
    }
     
    }catch (const exception& e)
    {
        	cout << "Place ask: Bad input!!!" << endl;
    }

}
    cout << "You entered: "  << input <<  endl;
}
void TradingMain::PrintWallet(){

    cout << "You have chosen to Print the wallet" << endl;
    cout << wallet.toString() << endl;

}
void TradingMain::Continue(){
    cout << "You have chosen to continue" << endl;
    vector<OrderBookEntry> sales = orderBook.matchAskstoBids("ETH/BTC", currentTime);
    cout << "Sales: " << sales.size() << endl;
    for(OrderBookEntry& s : sales)
    {
        cout << "Sales price: " << s.price << " amount " << s.amount << endl;
        if(s.username == "simuser")
        {
            wallet.processSales(s);

        }
    }
    
    currentTime = orderBook.getNextTime(currentTime);
}
void TradingMain::ProcessUseroption(int userOption)
{
    switch(userOption){
             
        case 1: 
        PrintHelp();
        break;

        case 2: 
            PrintExStats();
            break;

        case 3: 
            PlaceAsk();
            break;
        case 4:
            Placebid();
            break;
        case 5:
            PrintWallet();
            break;
        case 6:
            Continue();
            break;

        default:
            cerr << "invalid option entered!" << endl;
        }
}
