#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int windowsize = 4;
int noofPacket, morePacket;

int receiver(int tmp1) {
    srand(time(0));
    return rand() % tmp1;
}

int negack(int tmp1) {
    srand(time(0));
    return rand() % tmp1;
}

int simulate(int windowsize) {
    srand(time(0));
    int tmp1 = rand();
    if(tmp1 == 0)
        tmp1 = simulate(windowsize);
    int i = tmp1 % windowsize;
    if(i == 0)
        return windowsize;
    else
        return tmp1 % windowsize;
}

int main() {
    srand(time(0));
    noofPacket = rand() % 10;
    printf("Number of frames is: %d\n", noofPacket);
    morePacket = noofPacket;

    int tmp1, tmp2, tmp3 = 0, tmp4 = 0, tmp5 = 0;

    while(morePacket >= 0) {
        tmp1 = simulate(windowsize);
        windowsize -= tmp1;
        tmp4 += tmp1;

        if(tmp4 > noofPacket)
            tmp4 = noofPacket;

        for(int i = noofPacket - morePacket; i <= tmp4; i++)
            printf("\nSending Frame %d", i);

        tmp2 = receiver(tmp1);
        tmp3 += tmp2;

        if(tmp3 > noofPacket)
            tmp3 = noofPacket;

        tmp2 = negack(tmp1);
        tmp5 += tmp2;

        if(tmp5 != 0) {
            printf("\nNo acknowledgement for the frame %d", tmp5);
            printf("\nRetransmitting frame %d", tmp5);
        }
        morePacket -= tmp1;

        if(windowsize <= 0)
            windowsize = 4;
    }
    printf("\nSelective Repeat Protocol Ends. All packets are successfully transmitted.\n");
    return 0;
}