#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

FILE *fp;
bool ackReceived = false;
jmp_buf env;

void handle_alarm(int sig) {
    if (!ackReceived) {
        longjmp(env, 1);
    }
}

void openFile() {
    fp = fopen("frames.txt", "w+");
    if (fp == NULL) {
        printf("Could not open file frames.txt");
        exit(1);
    }
}

void closeFile() {
    fclose(fp);
}

void sendFrame() {
    fprintf(fp, "Sender: Sending frame\n");
    printf("Sender: Sending frame\n");
}

void receiveFrame() {
    char frame[255];
    if (fgets(frame, 255, fp) != NULL) {
        printf("Receiver: Receiving frame\n");
        printf("%s", frame);
    }
}

void sendAck() {
    fprintf(fp, "Receiver: Sending Acknowledgement\n");
    printf("Receiver: Sending Acknowledgement\n");
}

void receiveAck() {
    char ack[255];
    if (fgets(ack, 255, fp) != NULL) {
        printf("Sender: Receiving Acknowledgement\n");
        printf("%s", ack);
        ackReceived = true;
    }
}

void getData() {
    printf("Sender: Getting data\n");
}

void makeFrame() {
    printf("Sender: Making frame\n");
}

void extractData() {
    printf("Receiver: Extracting data\n");
}

void deliverData() {
    printf("Receiver: Delivering data to network layer\n");
}

bool waitForEvent() {
    sleep(1);
    return true;
}

int main() {
    bool isSender = true;

    openFile();

    signal(SIGALRM, handle_alarm);

    while (true) {
        if (waitForEvent()) {
            if (isSender) {
                if (setjmp(env) == 0) {
                    getData();
                    makeFrame();
                    sendFrame();
                    alarm(5); // Set a timer for 5 seconds
                    receiveAck();
                    alarm(0); // Cancel the timer
                } else {
                    printf("Timeout: Resending frame\n");
                    sendFrame();
                    alarm(5); // Set a timer for 5 seconds
                    receiveAck();
                    alarm(0); // Cancel the timer
                }
            } else {
                receiveFrame();
                extractData();
                deliverData();
                sendAck();
                isSender = !isSender; // Only switch to sender after receiving Ack
            }
        }
    }

    closeFile();

    return 0;
}