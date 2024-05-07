#include <bits/stdc++.h>
using namespace std;

FILE *fp;

void openFile(){
    fp=fopen("Frames.txt","w++");
    if(fp == NULL){
        cerr<<"Couldn't open file"<<endl;
    }
}

void closeFile(){
    fclose(fp);
}

//sender
void getData(){
    cout<<"Sender : Recieving Data/n";
}

void makeFrame(){
    cout<<"Sender : Making Frame/n";
}

void sendFrame(){
    fprintf(fp,"Sender : Sending Frame/n");
}

//Receiver
void recieveFrame(){
    char frame[255];
    if(fgets(frame,255,fp) != NULL){
        cout<<"Receiver : Recieving Frame/n" << frame << endl;
        exit(1);
    }
}


void extractData(){
    cout<<"Receiver : Extracting Data";
}

void deliverData(){
    cout<<"Receiver : Sending Data";
}


bool waitForEvent(){
    this_thread::sleep_for(chrono::seconds(1));
    return true;
}

int main(){
    bool isSender = true;
    openFile();
    while(true){
        if(waitForEvent()){
            if(isSender){
                getData();
                makeFrame();
                sendFrame();
            }
            else{
                recieveFrame();
                extractData();
                deliverData();
            }
            isSender=!isSender;
        }
    }
    closeFile();
    return 0;
}