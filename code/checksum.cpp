#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to calculate the one's complement of a binary string
string onesComplement(string data) {
    for (char& c : data) {
        c = (c == '0') ? '1' : '0';
    }
    return data;
}

// Function to calculate the checksum
string checksum(string data, int blockSize) {
    int n = data.length();
    if (n % blockSize != 0) {
        data = string(blockSize - (n % blockSize), '0') + data;
    }

    string result = "";
    for (int i = 0; i < n; i += blockSize) {
        string block = data.substr(i, blockSize);
        int carry = 0;
        for (int j = blockSize - 1; j >= 0; --j) {
            int sum = (block[j] - '0') + (result[j] - '0') + carry;
            result[j] = (sum % 2) + '0';
            carry = sum / 2;
        }
    }

    // If there's a carry after processing the last block, prepend it to the result
    if (carry) {
        result = '1' + result;
    }

    return onesComplement(result);
}

// Function to verify the integrity of the received message
bool checker(string sentMessage, string receivedMessage, int blockSize) {
    string checksumSent = checksum(sentMessage, blockSize);
    string checksumReceived = checksum(receivedMessage + checksumSent, blockSize);
    return count(checksumReceived.begin(), checksumReceived.end(), '0') == blockSize;
}

int main() {
    string sentMessage = "10000101011000111001010011101101";
    string receivedMessage = "10000101011000111001010011101101";
    int blockSize = 8;

    if (checker(sentMessage, receivedMessage, blockSize)) {
        cout << "No Error";
    } else {
        cout << "Error";
    }

    return 0;
}
