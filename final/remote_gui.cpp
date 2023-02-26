#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>
#include <queue>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

using namespace std;

class Remote_gui
{
public:
    Remote_gui(){
       // std::thread(&Remote_gui::foo_func, this);
       std::thread thread_obj(&Remote_gui::thread_send_loop, this);
       thread_obj.detach();
    }

    void send_log_gui(string log){
        send_queue.push(log);
    }

    void send_map_data_gui(string map){
        // Map data is sent as a string in the following format:
        // [[x,y,state,top,right,bottom,left],[x,y,state,top,right,bottom,left],...]
        // example: [[0,0,,0,0,1,0,0],[1,1,,2,0,0,1,0],[2,2,1,1,0,0,0],...]
        // Note: Send only the updated tiles and NOT the entire map
        send_queue.push("m:"+map);
    }

    void send_robot_location_gui(double x, double y, double angle){
        // converts the double to a int to send as a string
        int x_int = (int)(x*100);
        int y_int = (int)(y*100);
        int angle_int = (int)(angle*100);
        send_queue.push("r:["+to_string(x_int)+","+to_string(y_int)+","+to_string(angle_int)+"]");
    }
private:

    const char *sem_fn = "my_sem";
    sem_t *semdes;

    const int SHM_KEY = 32140895;
    const int SHM_SIZE = 2048;
    int SHM_ID = -1;

    queue<string> send_queue;
    string prev_sent_data = "";

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
        //cout << shm << endl;
        return shm;
    }

    bool received_data_from_gui(char* recieved){
        if(strcmp(recieved, "") == 0){ return true; } // If the gui has recived the data
        if(strcmp(prev_sent_data.c_str(), recieved) == 0){ return false; } // If it is the message that have been sent before

        if(*recieved == 'b'){   // The first letter is a identifier, b stands for button, v stands for variable
            cout << "button press" << endl;
        }

        if(*recieved == 'v'){
            cout << "variable change" << endl;
        }

        cout << recieved << endl;
        return true;
    }

    void thread_send_loop(){
        while(true){
            if(received_data_from_gui(ReadSHM())){
                string to_send = "";
                if(!send_queue.empty()){
                    to_send = send_queue.front();
                    send_queue.pop();
                }
                WriteSHM(to_send);
                prev_sent_data = to_send;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
    }
    }
};



int main()
{
    Remote_gui f;
    string temp = "map";
    while (true) {
        // for(int i = 0; i < 100; i++){
        //     f.send_log_gui(to_string(i));
        // }
        cout << "to write: ";
        string to_write;
        getline(cin, to_write);
        
        f.send_log_gui(to_write);
      
        // f.send_robot_location_gui(1.5,2.6,3.7);
        cout << "have written: " << to_write << endl;     
    }
    return 0;
}