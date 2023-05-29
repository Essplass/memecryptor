#include <iostream>
#include <string>
#include <vector>
#include "header.h"

using namespace std;

void printByteArray(const vector<uint8_t>& byteArray);
int testvalue_g = 1;

// Encryption algo that uses todays temperature, bitcoins price / ethereums price, moon phase and a 2 digit random number from random.org

class manipulators {
public:
    // Take the input and convert it to a byte array
    vector<uint8_t> stringToByteArray(const string& input)
    {
        vector<uint8_t> byteArray;
        for (char c : input) {
            byteArray.push_back(static_cast<uint8_t>(c));
        }
        //cout << " ->: " << input << "\n"; // prints input
        printByteArray(byteArray);        // prints bytearray
        return byteArray;
    }

};

class encryptors {
public:
    vector<uint8_t> testAddByte(const vector<uint8_t>& byteArray, int testvalue_g)
    {
        vector<uint8_t> modifiedArray(byteArray);  // Create a new vector to store the modified values
        for (uint8_t& byte : modifiedArray) {      // Use a reference to each element
            byte = byte + testvalue_g;             // Modify the element in the new vector
        }
        printByteArray(modifiedArray);             // Print the modified byte array
        return modifiedArray;
    }

    vector<uint8_t> cryptoEncrypt(const vector<uint8_t>& byteArray)
    {
        int btcPrice = btc();
        int ethPrice = eth();
        int cryptoValue;
        cryptoValue = btcPrice / ethPrice;
        cout << "btcPrice: " << btcPrice << "\n";
        cout << "ethPrice: " << ethPrice << "\n";
        cout << "cryptoValue: " << cryptoValue << "\n";
        vector<uint8_t> modifiedArray(byteArray);
        for (uint8_t& byte : modifiedArray) {
            byte = byte + cryptoValue;
        }
        printByteArray(modifiedArray);
        return modifiedArray; cryptoValue;

    }
    vector<uint8_t> tempEncrypt(const vector<uint8_t>& byteArray, int temperature)
    {
    }
    vector<uint8_t> moonPhaseEncrypt(const vector<uint8_t>& byteArray, int moonPhase)
    {
    }
    vector<uint8_t> atmosphereEncrypt(const vector<uint8_t>& byteArray, int atmosphere)
    {
    }


};

//Helper function that prints the byte array
void printByteArray(const vector<uint8_t>& byteArray)
{
    cout << "byteArray: ";
    for (uint8_t byte : byteArray)
        cout << static_cast<int>(byte) << " ";
    cout << "\n";

}

// Collects the user input string from the console
vector<uint8_t> inputCollector()
{
    vector<uint8_t> byteArray;
    string input;
    cout << "Please enter a string to be encrypted: \n ->: ";
    getline(cin, input);
    manipulators inObj;
    byteArray = inObj.stringToByteArray(input);
    return byteArray;
}






int main()
{
    vector<uint8_t> modifiedArray;
    cout << "Hello User!\n";
    vector<uint8_t> byteArray = inputCollector();
    encryptors encObj;
    modifiedArray = encObj.cryptoEncrypt(byteArray);
    modifiedArray = encObj.testAddByte(modifiedArray, testvalue_g);
    return 0;
}