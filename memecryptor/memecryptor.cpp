#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include <sstream>

using namespace std;

void printByteArray(const vector<uint8_t>& byteArray, string& crypt);

int testvalue_g = 1;
int cryptoValue;
int temperatureValue;
int atmosphereValue;


// Max added value = 20+40+10+99
// Encryption algo that uses today's temperature, Bitcoin's price / Ethereum's price, moon phase, and a 2-digit random number from random.org

class manipulators {
public:
    // Take a string and convert it to a byte array
    vector<uint8_t> stringToByteArray(const string& input)
    {
        string stringToByte = "Original Byte Array: ";
        vector<uint8_t> byteArray;
        for (char c : input) {
            byteArray.push_back(static_cast<uint8_t>(c));
        }
        printByteArray(byteArray, stringToByte);
        return byteArray;
    }
    // Take a byte array and convert it to a string
    string byteArrayToString(const vector<uint8_t>& byteArray)
    {
        string byteToString = "byteArrayToString: ";
        string result;
        for (uint8_t byte : byteArray) {
            result += static_cast<char>(byte);
        }
        return result;
    }

};

class encryptors {
public:
    // Test function adds one to each element in the byte array
    vector<uint8_t> testAddByte(const vector<uint8_t>& byteArray, int testvalue_g)
    {
        string test = "testAddByte: ";
        vector<uint8_t> modifiedArray(byteArray);
        //cout << "testValue: " << testvalue_g << "\n";
        for (uint8_t& byte : modifiedArray) {
            byte = byte + testvalue_g;
        }
        //printByteArray(modifiedArray, test);
        return modifiedArray;
    }

    // Fetches the BTC and ETH prices and adds them to each element in the byte array
    vector<uint8_t> cryptoEncrypt(const vector<uint8_t>& byteArray)
    {
        string crypto = "cryptoEncrypt: ";
        int btcPrice = getBtcPrice();
        int ethPrice = getEthPrice();
        cryptoValue = btcPrice / ethPrice;
        //cout << "cryptoValue: " << cryptoValue << "\n";
        vector<uint8_t> modifiedArray(byteArray);
        for (uint8_t& byte : modifiedArray) {
            byte = byte + cryptoValue;
        }
        printByteArray(modifiedArray, crypto);
        return modifiedArray;
    }
    // Fetches the temperature in the united Kingdom and adds each element to the byte array
    vector<uint8_t> temperatureEncrypt(const vector<uint8_t>& byteArray)
    {
        string temperature = "temperatureEncrypt: ";
        temperatureValue = getCurrentTemperature();
        //cout << "temperatureValue: " << temperatureValue << "\n";
        vector<uint8_t> modifiedArray(byteArray);
        for (uint8_t& byte : modifiedArray) {
            byte = byte + temperatureValue;
        }
        printByteArray(modifiedArray, temperature);
        return modifiedArray;
    }
    // Fetches a random number and adds it to each element in the byte array
    vector<uint8_t> atmosphereEncrypt(const vector<uint8_t>& byteArray)
    {
        string atmosphere = "Encrypted Byte Array: ";
        atmosphereValue = getAtmosphere();
        //cout << "AtmosphereValue: " << atmosphereValue << "\n";
        vector<uint8_t> modifiedArray(byteArray);
        for (uint8_t& byte : modifiedArray) {
            byte = byte + atmosphereValue;
        }
        printByteArray(modifiedArray, atmosphere);
        return modifiedArray;
    }
};

// Helper function that prints the byte array
void printByteArray(const vector<uint8_t>& byteArray, string& cryptoMethod)
{
    cout <<" " << cryptoMethod;
    for (uint8_t byte : byteArray)
        cout << static_cast<int>(byte) << " ";
    cout << "\n";
    cout << "\n";
}

// Collects the user input string from the console
vector<uint8_t> inputCollector()
{
    vector<uint8_t> byteArray;
    string input;
    cout << " Please enter a string to be encrypted: \n ->: ";
    getline(cin, input);
    cout << "\n";
    manipulators inObj;
    byteArray = inObj.stringToByteArray(input);
    return byteArray;
}

// Decrypts the byte array by subtracting all of the values used from each element in the byte array
string decrypt(vector<uint8_t> modifiedArray)
{
    int values = cryptoValue + temperatureValue + testvalue_g + atmosphereValue;
    string decrypted = "Decrypted Byte Array: ";
    for (uint8_t& byte : modifiedArray) {
        byte = byte - values;
    }
    printByteArray(modifiedArray, decrypted);

    manipulators outObj;
    return outObj.byteArrayToString(modifiedArray);
}

// Main
int main()
{
    system("Color 0D");
    vector<uint8_t> modifiedArray;
    cout << " -------------------------------------------------------------------------" "\n";
    cout << " Hello and welcome to the Memecryptor a C++ project developed by Essplass!\n";
    cout << " -------------------------------------------------------------------------" "\n";
    cout << "\n";
    vector<uint8_t> byteArray = inputCollector();
    encryptors encObj;
    modifiedArray = encObj.cryptoEncrypt(byteArray);
    modifiedArray = encObj.testAddByte(modifiedArray, testvalue_g);
    modifiedArray = encObj.temperatureEncrypt(modifiedArray);
    modifiedArray = encObj.atmosphereEncrypt(modifiedArray);
    string decryptedString = decrypt(modifiedArray);
    cout << " Decrypted String: " << decryptedString << endl;
    return 0;
}