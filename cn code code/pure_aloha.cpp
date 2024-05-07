#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool isCollision(int timeA, int timeB, int tp) {
    if (timeA < timeB && timeB < timeA + tp) {
        return true;
    }
    if (timeB < timeA && timeA < timeB + tp) {
        return true;
    }
    return false;
}

int main() {
    srand(time(0));

    int tp = 1;
    int backoffTime = 0;

    int timeA = rand() % 10;
    int timeB = rand() % 10;

    cout << "Device A starts transmitting at time " << timeA << endl;
    cout << "Device B starts transmitting at time " << timeB << endl;

    if (isCollision(timeA, timeB, tp)) {
        cout << "Collision detected!" << endl;
        backoffTime = rand() % (2 * tp + 1);
        cout << "Device A waits for " << backoffTime << " time units before retransmitting." << endl;
        cout << "Device B waits for " << backoffTime << " time units before retransmitting." << endl;
    } else {
        cout << "No collision. Transmission successful." << endl;
    }

    return 0;
}
