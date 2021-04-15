#include<iostream>
#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<string.h>



using namespace std;


#define MAX 100
int total_service_time = 0, total_spend_time = 0, total_waiting_time = 0, wait_var = 0, total_idle_time = 0;



class simulation{
public:
    int customer_number;
    int randomDigit_arrival;
    int randomDigit_service;
    int service_begin;
    int service_time;
    int time_ser_end;
    int waiting_time;
    int idle_time;
    int spend;
    int inter_arrival_time;
    int arrival_time;
    string server;


};

vector <simulation> ser1;
vector<simulation> ser2;



//Random digits genration for arrival and inter arrival time
//Probablity for arrival time
// 0.25  0.40  0.20   0.15

void  Random_digit_arrival(simulation arr[], int n) {
    int rn;
   

    arr[1].customer_number = 1;
    arr[1].randomDigit_arrival = 0;
    arr[1].inter_arrival_time = 0;

    for (int i = 2; i <= n; i++) {

        rn = rand() % 100 + 1;
        arr[i].randomDigit_arrival = rn;
        arr[i].customer_number = i;
        if (arr[i].randomDigit_arrival > 0 && arr[i].randomDigit_arrival < 26)  arr[i].inter_arrival_time = 1;
        else if (arr[i].randomDigit_arrival > 25 && arr[i].randomDigit_arrival < 66)  arr[i].inter_arrival_time = 2;
        else if (arr[i].randomDigit_arrival > 65 && arr[i].randomDigit_arrival < 86)  arr[i].inter_arrival_time = 3;
        else if (arr[i].randomDigit_arrival > 85 && arr[i].randomDigit_arrival < 101)  arr[i].inter_arrival_time = 4;
       
       
        else { cout << " Please Enter Random Digit for arrival time within limit: around 1-100" << endl; }
    }
}


//Arrival time scheduling

void Arrival_time_scheduling(simulation arr[], int n) {
    arr[1].arrival_time = 0;
    for (int i = 2; i <= n; i++) {
        arr[i].arrival_time = arr[i - 1].arrival_time + arr[i].inter_arrival_time;
    }
}


//Genration of Random NUMBERs for service

void RandomDigitService(simulation arr[], int n) {
    int rn2;
   

    arr[1].service_begin = 0;
    for (int i = 1; i <= n; i++) {

        rn2 = rand() % 100 + 1;
        arr[i].randomDigit_service = rn2;
       
    }
}



// Scheduling service time for Server 1
//Probablity For Server 1
// 0.3  0.28  0.25  0.17


void scheduling_service_time_server1(simulation arr[],int n, int randomDigit_service ,int i) {
    if (arr[i].randomDigit_service > 0 && arr[i].randomDigit_service < 31) arr[i].service_time = 1;
    else if (arr[i].randomDigit_service > 30 && arr[i].randomDigit_service < 59)  arr[i].service_time = 2;
    else if (arr[i].randomDigit_service > 58 && arr[i].randomDigit_service < 84)  arr[i].service_time = 3;
    else if (arr[i].randomDigit_service > 83 && arr[i].randomDigit_service < 101)  arr[i].service_time = 4;

    arr[i].server = "Server_1";
}



// Scheduling service time for Server 2
//Probablity For Server 2
// 0.35  0.25  0.20  0.20


void scheduling_service_time_server2(simulation arr[], int n, int randomDigit_service, int i) {
    if (arr[i].randomDigit_service > 0 && arr[i].randomDigit_service < 36) arr[i].service_time = 1;
    else if (arr[i].randomDigit_service > 35 && arr[i].randomDigit_service < 61)  arr[i].service_time = 2;
    else if (arr[i].randomDigit_service > 60 && arr[i].randomDigit_service < 81)  arr[i].service_time = 3;
    else if (arr[i].randomDigit_service > 80 && arr[i].randomDigit_service < 101)  arr[i].service_time = 4;


    arr[i].server = "Server_2";
}



// secheduling service begin, time service end, waiting time and idle time.


void scheduling_service_time(simulation arr[], int n) {
    scheduling_service_time_server1(arr, n, arr[1].randomDigit_service, 1);
    arr[1].service_begin = 0;
    arr[1].time_ser_end = arr[1].service_begin + arr[1].service_time;
   
    arr[1].waiting_time = 0;
    arr[1].idle_time = 0;
    ser1.push_back(arr[1]);
    

      
    int x=1, y=0;
    
    for (int i = 2; i <= n; i++) {

        if (arr[i].arrival_time >= ser1[x - 1].time_ser_end) {
            scheduling_service_time_server1(arr, n, arr[i].randomDigit_service, i);
            arr[i].service_begin = arr[i].arrival_time;
            arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
            ser1.push_back(arr[i]);
           
            arr[i].idle_time = arr[i].arrival_time - ser1[x - 1].time_ser_end;
            total_idle_time += arr[i].idle_time;
            arr[i].waiting_time = 0;

            x++;
}


        else if (arr[i].arrival_time < ser1[x - 1].time_ser_end && ser2.size() == 0) {
            scheduling_service_time_server2(arr, n, arr[i].randomDigit_service, i);
           
                arr[i].service_begin = arr[i].arrival_time;

            
            arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
            ser2.push_back(arr[i]);

           
            arr[i].idle_time = 0;
            total_idle_time += arr[i].idle_time;
            arr[i].waiting_time = 0;

            y++;
        }

        else if (arr[i].arrival_time < ser1[x - 1].time_ser_end && arr[i].arrival_time >= ser2[y - 1].time_ser_end) {
            scheduling_service_time_server2(arr, n, arr[i].randomDigit_service, i);
            
                arr[i].service_begin = arr[i].arrival_time;

            
            arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
            ser2.push_back(arr[i]);
            
            arr[i].idle_time = arr[i].arrival_time - ser2[y - 1].time_ser_end;
            total_idle_time += arr[i].idle_time;
            arr[i].waiting_time = 0;

            y++;
        }
      

        else if (arr[i].arrival_time < ser1[x - 1].time_ser_end && arr[i].arrival_time < ser2[y - 1].time_ser_end ) {
            if (ser1[x-1].time_ser_end <= ser2[y-1].time_ser_end) {
                scheduling_service_time_server1(arr, n, arr[i].randomDigit_service, i);
                arr[i].service_begin = ser1[x - 1].time_ser_end;
                arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
                ser1.push_back(arr[i]);


                arr[i].waiting_time = ser1[x - 1].time_ser_end - arr[i].arrival_time;
                total_waiting_time += arr[i].waiting_time;
                arr[i].idle_time = 0;
                x++;
            }

            else {
                scheduling_service_time_server2(arr, n, arr[i].randomDigit_service, i);
                arr[i].service_begin = ser2[y - 1].time_ser_end;
                arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
                ser2.push_back(arr[i]);

                arr[i].waiting_time = ser2[y - 1].time_ser_end - arr[i].arrival_time;
                total_waiting_time += arr[i].waiting_time;
                arr[i].idle_time = 0;
                y++;
            }
        }


        else if (arr[i].arrival_time >= ser1[x - 1].time_ser_end && arr[i].arrival_time >= ser2[y - 1].time_ser_end) {
            scheduling_service_time_server1(arr, n, arr[i].randomDigit_service, i);
            arr[i].service_begin = arr[i].arrival_time;
            arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
            ser1.push_back(arr[i]);


            arr[i].idle_time = arr[i].arrival_time - ser1[x - 1].time_ser_end;
            total_idle_time += arr[i].idle_time;
            arr[i].waiting_time = 0;

            x++;
        }

       


       
    }


}



void Customer_idle_waiting_time(simulation arr[], int n) {


    
    int x = 1, y = 0;
    for (int i = 2; i <= n; i++) {
        if (arr[i].arrival_time > max(ser1[x-1].time_ser_end,ser1[y].time_ser_end)){
            arr[i].idle_time = arr[i].arrival_time - max(ser1[x-1].time_ser_end, ser1[y].time_ser_end);
            total_idle_time += arr[i].idle_time;
            arr[i].waiting_time = 0;
        }
        else {
            arr[i].waiting_time = max(ser1[x-1].time_ser_end, ser1[y].time_ser_end) - arr[i].arrival_time;
            total_waiting_time += arr[i].waiting_time;
            arr[i].idle_time = 0;
        }
        if (arr[i].waiting_time != 0) {
            wait_var = wait_var + 1;
        }

    }







    
}


// time spent in system-

void Time_spent_in_server(simulation arr[], int n) {
    for (int i = 1; i <= n; i++) {
        arr[i].spend = arr[i].service_time + arr[i].waiting_time;
        total_spend_time += arr[i].spend;
    }
}


// Display function

void display(simulation arr[], int n) {
  
    cout << "\n\t--------------------------------------------------------------------------------------------------------------------------------";
    cout << "\n\t|server  | Call.  | RD. for | Inter_arrival | Arrival   | RD. for | Service | T.Service| T.Service| Waiting | Server   | spend |\n";
    cout << "\t|        | No.    |Arrival.T|     Time      |  Time     |Service.T|  Time   |  Begin   |    End   | in Queue| Idle.T   |  Time |";
    cout << "\n\t--------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 1; i <= n; i++) {
        cout <<"\t"<< arr[i].server ;
        printf("    %d\t       %d\t      %d\t         %d\t     %d\t       %d         %d\t     %d\t     %d\t       %d\t   %d\n"
            , arr[i].customer_number, arr[i].randomDigit_arrival, arr[i].inter_arrival_time, arr[i].arrival_time, arr[i].randomDigit_service, arr[i].service_time, arr[i].service_begin,
            arr[i].time_ser_end, arr[i].waiting_time, arr[i].idle_time,arr[i].spend);

        if (i != n) {
            printf("\t--------------------------------------------------------------------------------------------------------------------------------\n");
        }
        else {
            printf("\t--------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }

       
    printf("\n\n\n\n");
    
    cout<<"Total waiting time : "<<total_waiting_time<<endl;
    cout<<"Average waiting time : "<<total_waiting_time/n<<endl;

}




int main() {
    int n;
    cout << "Enter the Numbers of calls :";
    cin >> n;
   simulation arr[100];
   srand(time(NULL));      // initilizing the timing routine with func sran() and giving seed value as NULL. 
  
   Random_digit_arrival(arr,n);
   Random_digit_arrival(arr, n);
   Arrival_time_scheduling(arr, n);
   RandomDigitService(arr, n);
   scheduling_service_time(arr, n);
   Time_spent_in_server(arr, n);
       display( arr,  n);
}
