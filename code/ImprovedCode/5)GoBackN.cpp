#include <bits/stdc++.h>
using namespace std;

#define MAX_SEQ 7 // Maximum sequence number
#define TIMEOUT 5 // Timeout in seconds

vector<bool> ackReceived(MAX_SEQ + 1, false); // Vector to track acknowledgments
int base = 0; // Base sequence number
int nextSeqNum = 0; // Next sequence number to send

void sendFrame(int seqNum) {
    cout << "Sender: Sending frame " << seqNum << endl;
    // Simulate sending the frame
    ackReceived[seqNum] = false;
}

void receiveAck(int seqNum) {
    cout << "Receiver: Receiving Acknowledgement for frame " << seqNum << endl;
    ackReceived[seqNum] = true;
}

void resendFrames() {
    cout << "Timeout: Resending frames from " << base << endl;
    for (int i = base; i <= nextSeqNum; i++) {
        if (!ackReceived[i]) {
            sendFrame(i);
        }
    }
}

bool waitForEvent() {
    this_thread::sleep_for(chrono::seconds(1)); // Simulate waiting for an event
    return true;
}

int main() {
    bool isSender = true;

    while (true) {
        if (waitForEvent()) {
            if (isSender) {
                if (nextSeqNum <= MAX_SEQ) {
                    sendFrame(nextSeqNum);
                    nextSeqNum++;
                }

                // Simulate receiving an acknowledgment
                receiveAck(nextSeqNum - 1);

                // Check if all frames have been acknowledged
                if (ackReceived[base]) {
                    base++;
                }
            } else {
                // Simulate receiving a frame
                receiveAck(nextSeqNum - 1);
                isSender =!isSender; // Switch roles
            }
        }
    }

    return 0;
}
