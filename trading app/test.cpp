#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> tokenise(string cvsline, char separator) {
    vector<string> tokens;
    size_t start = 0, end = 0;

    while ((end = cvsline.find(separator, start)) != string::npos) {
        tokens.push_back(cvsline.substr(start, end - start)); // Extract token
        start = end + 1; // Move to the next token start position
    }

    tokens.push_back(cvsline.substr(start)); // Last token after the last separator

    // Ensure we have at least 5 elements
    while (tokens.size() < 5) {
        tokens.push_back("0");  // Add missing columns as "0"
    }
    
    return tokens;
}

int main() {
    ifstream csvfile("1XejnIsmSmK3o5yLJkpiUg_2402656ae54246e880715f135341f5f7_20200317.csv");
    string line;
    vector<string> tokens;

    if (csvfile.is_open()) {
        cout << "File opened successfully!" << endl;
        
        while (getline(csvfile, line)) {
            cout << "Read line: " << line << endl;
            
            tokens.clear(); // Clear previous tokens before processing new line
            tokens = tokenise(line, ',');
            
            for (string& t : tokens) {
                cout << t << " ";
            }
            cout << endl;

            // Convert columns 3 and 4 to double (only if they exist)
            try{
            if (tokens.size() >= 5) {
                double price = stod(tokens[3]);
                double amount = stod(tokens[4]);
                cout << "Price: " << price << " / Amount: " << amount << endl;
            } else {
                cerr << "Error: Not enough columns in line!" << endl;
            }
        }catch(exception& e){
            cerr << "Bad float" << tokens[3] <<endl;
            cerr << "Bad float" << tokens[4] << endl;
            break;
        }
        }

        csvfile.close(); 
    } else {
        cout << "File not opened!" << endl;
    }

    return 0;
}
