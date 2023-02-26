#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>
#include <queue>
#include <thread>

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

using namespace std;

const char *sem_fn = "my_sem";
sem_t *semdes;

const int SHM_KEY = 32140895;
const int SHM_SIZE = 2048;
int SHM_ID = -1;

void WriteSHM(string str){
    //string str = "Hello World";
    uint8_t* dataBuffer = (uint8_t*) str.c_str();
    size_t bufferLength = strlen(str.c_str());
    semdes = sem_open(sem_fn, O_CREAT, 0644, 0);
    if ( (SHM_ID = shmget(SHM_KEY, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    char* shm = (char*) shmat(SHM_ID,(void*)0,0);
    for(int i = 0; i < (int)bufferLength; i++)
        shm[i] = dataBuffer[i];
    for(int i = (int)bufferLength; i < SHM_SIZE; i++)
        shm[i] = '\0';
    shmdt(shm);
    sem_post(semdes);

}

char* ReadSHM(){
    semdes = sem_open(sem_fn, O_CREAT, 0644, 0);
    if ( (SHM_ID = shmget(SHM_KEY, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    char* shm = (char*) shmat(SHM_ID,(void*)0,0);
    sem_post(semdes);
    cout << shm << endl;
    return shm;
}



bool recieved_data_from_gui(char* recieved){
    //cout << "recieved some data:" << recieved << endl;
    if(strcmp(recieved, "ok")==0){
        // Do nothing, ok is confermation that the data was recieved
        cout << "ok" << endl;
        return true;
    }
    if(strcmp(recieved, "variable:")==0){
        // change varible data
        return true;
    }
    return false;
}


// Sometimes the gui-server have not read from shared mem yet,
// therefor the data is put in queue and sent together with the next message
queue<string> send_queue;
void send_queue_gui(string str){
    send_queue.push(str);
    char* new_recieved = ReadSHM();
    if(recieved_data_from_gui(new_recieved)){
        string to_send = "";
        for(int i = 0; i < send_queue.size(); i++){
            to_send += send_queue.front();
            send_queue.pop();
        }
        WriteSHM(to_send);
    }
}

void send_log_gui(string log){
    send_queue_gui("@l:"+log);
}

void send_map_data_gui(string map){
    // Map data is sent as a string in the following format:
    // [[x,y,top,right,bottom,left],[x,y,top,right,bottom,left],...]
    // example: [[0,0,0,1,0,0],[1,1,0,0,1,0],[2,2,1,0,0,0],...]
    // Note: Send only the updated tiles and NOT the entire map
    WriteSHM("@m:"+map);
}

int main(void) {
    while (true) {
        cout << "to write: ";
        string to_write;
        getline(cin, to_write);
        send_log_gui(to_write);
        cout << "have written: " << to_write << endl;     
    }
    return 0;
}

