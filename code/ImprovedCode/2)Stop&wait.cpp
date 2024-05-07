#include <bits/stdc++.h>
using namespace std;

FILE *fp;

void openFile() {
    fp = fopen("frames.txt", "w+");
    if (fp == NULL) {
        cerr << "Could not open file frames.txt" << endl;
        exit(1);
    }
}

void closeFile() {
    fclose(fp);
}

void sendFrame() {
    fprintf(fp, "Sender: Sending frame\n");
    cout << "Sender: Sending frame\n";
}

void receiveFrame() {
    char frame[255];
    if (fgets(frame, 255, fp)!= NULL) {
        cout << "Receiver: Receiving frame\n" << frame << endl;
    }
}

void sendAck() {
    fprintf(fp, "Receiver: Sending Acknowledgement\n");
    cout << "Receiver: Sending Acknowledgement\n";
}

void receiveAck() {
    char ack[255];
    if (fgets(ack, 255, fp)!= NULL) {
        cout << "Sender: Receiving Acknowledgement\n" << ack << endl;
    }
}

void getData() {
    cout << "Sender: Getting data\n";
}

void makeFrame() {
    cout << "Sender: Making frame\n";
}

void extractData() {
    cout << "Receiver: Extracting data\n";
}

void deliverData() {
    cout << "Receiver: Delivering data to network layer\n";
}

bool waitForEvent() {
    this_thread::sleep_for(chrono::seconds(1));
    return true;
}

int main() {
    bool isSender = true;

    openFile();

    while (true) {
        if (waitForEvent()) {
            if (isSender) {
                getData();
                makeFrame();
                sendFrame();
                receiveAck();
            } else {
                receiveFrame();
                extractData();
                deliverData();
                sendAck();
            }
            isSender =!isSender;
        }
    }

    closeFile();

    return 0;
}
