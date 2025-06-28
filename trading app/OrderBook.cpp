#include "OrderBook.h"
#include "CSVreader.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(string filename)
{
    orders = CVSReader::readCSV(filename);
    cout << "Debug: Loaded " << orders.size() << " orders from file." << endl;
}
    
vector<string>OrderBook::GetKnownProduct ()
{
    vector<string> products;
    map<string, bool> prodMap;

    for(OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;

    }

    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }
    return products;
}
vector<OrderBookEntry>OrderBook::GetOrders(OrderBookType type, string product, string timestamp)
{
    vector<OrderBookEntry> orders_sub;

    for(OrderBookEntry& e : orders)
    {
        if(e.Ordertype == type && e.product == product && e.timestampe == timestamp)
        {
            orders_sub.push_back(e);
        }
    }

    //cout << "Debug: Found " << orders_sub.size() << " matching orders." << endl;
    return orders_sub;
}

string OrderBook::getEarliestTime(){

    return orders[0].timestampe;
}
string OrderBook::getNextTime(string timestamp){
    string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestampe > timestamp)
        {
            next_timestamp = e.timestampe;
            break;
        }
        if(next_timestamp == ""){
            next_timestamp = orders[0].timestampe;
        }
    }
    return next_timestamp;

}
double OrderBook::GetAverage(vector<OrderBookEntry>& orders) {
    if (orders.empty()) {
        cerr << "Error: No orders available!" << endl;
        return 0.0; // Return 0 to avoid division by zero
    }

    double totalPrice = 0.0; // Accumulate total price

    for (const OrderBookEntry& e : orders) {
        totalPrice += e.price;
        //cout << e.price << endl;
    }

    return totalPrice / orders.size(); // Compute the average correctly
}
void OrderBook::insertOrder(OrderBookEntry& order){
    cout << "✅ Inserting order -> Product: " << order.product
         << ", Price: " << order.price << ", Amount: " << order.amount << endl;

    orders.push_back(order);  // Add to the order book

    // 🔍 Debugging: Print all stored orders
    cout << "📌 Current Orders in OrderBook:" << endl;
    for (const auto& o : orders) {
        cout << "  - Product: " << o.product << ", Price: " << o.price 
             << ", Amount: " << o.amount << endl;
    }
}

vector <OrderBookEntry> OrderBook::matchAskstoBids (string product, string timestamp){

    vector<OrderBookEntry> asks = GetOrders(OrderBookType::ask, product, timestamp);
    vector<OrderBookEntry> bids = GetOrders(OrderBookType::bid, product, timestamp);

    vector<OrderBookEntry> sales;

    sort(asks.begin(), asks.end(), OrderBookEntry::comparebyPriceAse);

    sort(asks.begin(), asks.end(), OrderBookEntry::comparebyPriceDec);

    for (OrderBookEntry& e : asks){

        for(OrderBookEntry& b : bids){

            if(b.price >= e.price){
                
                OrderBookEntry sale{e.price, 0, timestamp, product, OrderBookType::asksale};
               

                if(b.username == "simuser")
                {
                    
                    sale.username = "simuser";
                    sale.Ordertype = OrderBookType::bidsale;
                }
                if(e.username == "simuser")
                {
                    
                    sale.username = "simuser";
                    sale.Ordertype = OrderBookType::asksale;
                }
                

                if(b.amount == e.amount)
                {
                    sale.amount = e.amount;
                    sales.push_back(sale);
                    b.amount = 0;
                }

                if(b.amount > e.amount){
                    sale.amount = e.amount;
                    sales.push_back(sale);
                    b.amount = b.amount - e.amount;
                    break;

                }

                if(b.amount < e.amount && b.amount > 0)
                {
                    sale.amount = b.amount;
                    sales.push_back(sale);
                    e.amount = e.amount - b.amount;
                    b.amount = 0;
                    continue;
                }


            }
        }
    }
    return sales;
}


// double OrderBook::getHighPrice(vector<OrderBookEntry>& orders){

//     if (orders.empty()) {
//         cerr << "Error: No orders found!" << endl;
        
//     }

//     double max = orders[0].price;
//     for (OrderBookEntry& e : orders)
//     {
//         if(e.price > max)
//         {
//             max = e.price;
//         }
//     }

//     return max;

// }
// double OrderBook::getlowPrice(vector<OrderBookEntry>& orders){

//     double low = orders[0].price;
//     for (OrderBookEntry& e : orders)
//     {
//         if(e.price < low)
//         {
//             low = e.price;
//         }
//     }
//     return low;

// }