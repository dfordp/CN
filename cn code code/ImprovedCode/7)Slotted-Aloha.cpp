#include <bits/stdc++.h>

using namespace std;

bool simulateSlot(int numNodes, double p) {
    vector<bool> transmissionAttempts(numNodes, false);
    int successfulTransmissions = 0;

    for (int i = 0; i < numNodes; ++i) {
        if (rand() < p * RAND_MAX) {
            transmissionAttempts[i] = true;
        }
    }

    for (int i = 0; i < numNodes; ++i) {
        if (transmissionAttempts[i]) {
            successfulTransmissions++;
        }
    }

    if (successfulTransmissions > 1) {
        return false;
    }

    return true;
}

int main() {
    srand(time(0));

    int numNodes = 3;
    double p = 0.5;
    int numSlots = 10;

    int successfulTransmissions = 0;

    for (int i = 0; i < numSlots; ++i) {
        if (simulateSlot(numNodes, p)) {
            successfulTransmissions++;
        }
    }

    cout << "Number of successful transmissions: " << successfulTransmissions << endl;

    return 0;
}
