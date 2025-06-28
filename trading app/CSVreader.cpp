#include "CSVreader.h"
#include <fstream>

CVSReader::CVSReader(){

}

vector<string> CVSReader::tokenise(string cvsline, char separator){

    vector<string> tokens;
    size_t start = 0, end = 0;

    while ((end = cvsline.find(separator, start)) != string::npos) {
        tokens.push_back(cvsline.substr(start, end - start)); // Extract token
        start = end + 1; // Move to the next token start position
    }

    tokens.push_back(cvsline.substr(start)); // Last token after the last separator

    // Ensure we have at least 5 elements
    // while (tokens.size() < 5) {
    //     tokens.push_back("0");  // Add missing columns as "0"
    // }
    
    return tokens;

    
}

// OrderBookEntry CVSReader::stringstoOBE(vector<string> tokens){

//     double price = 0.0;
//     double amount = 0.0;
    
//         if (tokens.size() >= 5) {

//             try{
//             double price = stod(tokens[3]);
//             double amount = stod(tokens[4]);
//             cout << "Price: " << price << " / Amount: " << amount << endl;
            
//         } 
//     catch(exception& e){
//         cerr << "Bad float" << tokens[3] <<endl;
//         cerr << "Bad float" << tokens[4] << endl;
    
        
//     }

//     }else {
//         cerr << "Error: Not enough columns in line!" << endl;
//     }

//     cout << "Debug: Calling OrderBookEntry Constructor with -> " 
//     << "Price: " << price << ", Amount: " << amount << endl;

//      OrderBookEntry obe1{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOBT(tokens[2])};

    

//     return obe1;


//     //OrderBookEntry obe1{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOBT(tokens[2])};
    
// }

vector<OrderBookEntry> CVSReader::readCSV(string csvfilename) {
    vector<OrderBookEntry> entries;
    vector<string> tokens;
    ifstream csvfile(csvfilename);
    string line;

    if (!csvfile) {
        cerr << "Error: Cannot open file " << csvfilename << endl;
        return entries;
    }

    cout << "File opened successfully!" << endl;

    while (getline(csvfile, line)) {
        tokens = CVSReader::tokenise(line, ',');

        double price = 0.0;
        double amount = 0.0;

        if (tokens.size() >= 5) {
            try {
                price = stod(tokens[3]);
                amount = stod(tokens[4]);
                cout << "Price: " << price << " / Amount: " << amount << endl;
            } catch (const exception& e) {
                cerr << "Bad float: " << tokens[3] << " or " << tokens[4] << endl;
                price = 0.0;
                amount = 0.0;
            }
        } else {
            cerr << "Error: Not enough columns in line!" << endl;
            continue;  // Skip this line
        }

        try {
            OrderBookType obType = OrderBookEntry::stringToOBT(tokens[2]);
            entries.emplace_back(price, amount, tokens[0], tokens[1], obType);
        } catch (const std::exception& e) {
            cerr << "Error processing OrderBookType: " << e.what() << endl;
        }

        if (entries.size() > 100000) {  // Prevent memory overflow (Debugging)
            cerr << "Too many entries, stopping." << endl;
            break;
        }
    }

    cout << "Total Entries: " << entries.size() << endl;
    return entries;
}


OrderBookEntry CVSReader::stringstoOBE(string priceString, string amountString, string timestamp, string product, OrderBookType orderBookType) {
    double price = 0.0, amount = 0.0;

    cout << "🔍 Debug: Converting price [" << priceString << "] and amount [" << amountString << "]" << endl;

    try {
        price = stod(priceString);
        amount = stod(amountString);
        cout << "✅ Converted -> Price: " << price << ", Amount: " << amount << endl;
    } catch (const exception& e) {
        cout << "❌ Error: Invalid float conversion! " << e.what() << endl;
    }
    cout << "Debug: Calling OrderBookEntry Constructor with -> " 
     << "Price: " << price << ", Amount: " << amount << endl;

    return OrderBookEntry(price, amount, timestamp, product, orderBookType);
}
