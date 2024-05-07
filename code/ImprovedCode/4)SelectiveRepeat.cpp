#include <bits/stdc++.h>

#define WINDOW_SIZE 4
#define MAX_PACKETS 10

// Function to simulate packet loss
int simulatePacketLoss(int windowSize) {
    srand(time(0));
    return rand() % windowSize;
}

// Function to simulate acknowledgement
int simulateAcknowledgement(int windowSize) {
    srand(time(0));
    return rand() % windowSize;
}

int main() {
    srand(time(0));
    int noOfPackets = rand() % MAX_PACKETS + 1; // Ensure at least one packet
    std::cout << "Number of packets to send: " << noOfPackets << std::endl;

    int windowSize = WINDOW_SIZE;
    int packetsSent = 0;
    int packetsAcknowledged = 0;
    int base = 0;

    while (packetsAcknowledged < noOfPackets) {
        // Send packets up to the window size
        for (int i = base; i < base + windowSize && i < noOfPackets; i++) {
            std::cout << "Sending packet " << i << std::endl;
            packetsSent++;
        }

        // Simulate acknowledgements
        int ackCount = simulateAcknowledgement(windowSize);
        packetsAcknowledged += ackCount;
        std::cout << "Received acknowledgements for " << ackCount << " packets" << std::endl;

        // Adjust the window size based on acknowledgements
        if (ackCount > 0) {
            base += ackCount;
            windowSize = WINDOW_SIZE;
        } else {
            // If no acknowledgements, reduce the window size
            windowSize = windowSize / 2;
            if (windowSize < 1) {
                windowSize = 1;
            }
        }

        // Simulate packet loss
        int lostPackets = simulatePacketLoss(windowSize);
        if (lostPackets > 0) {
            std::cout << "Simulating packet loss for " << lostPackets << " packets" << std::endl;
            // Retransmit lost packets
            for (int i = 0; i < lostPackets; i++) {
                std::cout << "Retransmitting packet " << base + i << std::endl;
            }
        }
    }

    std::cout << "All packets successfully transmitted." << std::endl;
    return 0;
}
