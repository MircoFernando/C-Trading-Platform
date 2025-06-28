#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet()
{
     
}
void Wallet::insertCurrency(string type, double amount)
{
    double balance;
    if(amount < 0){

        throw exception{};

    }
    if(currency.count(type) == 0)
    {
        cout << "The amount is added" << endl;
        balance = 0;
    }
    else{
        balance = currency[type];
    }
    balance += amount;
    currency[type] = balance;
}
bool Wallet::removeCurrency(string type, double amount)
{
    double balance;
    if(amount < 0){

        return false;

    }
    if(currency.count(type) == 0)
    {
        return false;
    }
    else{
        if (containCurrency(type, amount))
        {
            currency[type] -= amount;
            return true; 
        }
        else return false;
    }
    
}
bool Wallet::containCurrency(string type, double amount)
{
    if(currency.count(type) == 0) return false;
    else return currency[type] >= amount;
}
string Wallet::toString(){

    string s;
    for(pair<string,double> pair : currency)
    {
        string curren = pair.first;
        double amount = pair.second;
        s += curren + ": " + to_string(amount) + "\n";
    }
    return s;
}
bool Wallet::canfulfillOrder(OrderBookEntry order)
{
    vector<string> curren = CVSReader::tokenise(order.product, '/');
    if(order.Ordertype == OrderBookType::ask)
    {
        double amount = order.amount;
        string currency = curren[0];
        cout << "canfulfillOrder: " << currency << amount <<  endl;
        return containCurrency(currency, amount);


    }
    if(order.Ordertype == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        string currency = curren[1];
        cout << "canfulfillOrder: " << currency << amount <<  endl;
        return containCurrency(currency, amount);
    }
    return false;

}
void Wallet::processSales(OrderBookEntry& sale)
{
    vector<string> curren = CVSReader::tokenise(sale.product, '/');

    if (sale.Ordertype == OrderBookType::asksale)
    {
        double outamount = sale.amount;
        string outcurrency = curren[0];

        double inamount = sale.amount * sale.price;
        string incurrency = curren[1];

        currency[incurrency] += inamount;
        currency[outcurrency] -= outamount;
    }

    if (sale.Ordertype == OrderBookType::bidsale)
    {
        double inamount = sale.amount;
        string incurrency = curren[0];

        double outamount = sale.amount * sale.price;
        string outcurrency = curren[1];

        currency[incurrency] += inamount;
        currency[outcurrency] -= outamount;
    }
}
