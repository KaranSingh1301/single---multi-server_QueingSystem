
#include <stdio.h>
#include <iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

int total_service_time = 0, total_spend_time = 0, total_waiting_time = 0, wait_var = 0, total_idle_time = 0;

class Simulation {
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


};

void RandomDigitService(Simulation arr[], int n);




//Random digit for arrival time

void Random_digit_arrival(Simulation arr[], int n) {
    int rn;
    srand(time(NULL));

    arr[1].customer_number = 1;
    arr[1].randomDigit_arrival = 0;
    arr[1].inter_arrival_time = 0;
    arr[1].arrival_time = 0;
    for (int i = 2; i <= n; i++) {

        rn = rand() % 1000 + 1;
        arr[i].randomDigit_arrival = rn;
        arr[i].customer_number = i;
        if (arr[i].randomDigit_arrival > 0 && arr[i].randomDigit_arrival < 126)  arr[i].inter_arrival_time = 1;
        else if (arr[i].randomDigit_arrival > 125 && arr[i].randomDigit_arrival < 251)  arr[i].inter_arrival_time = 2;
        else if (arr[i].randomDigit_arrival > 250 && arr[i].randomDigit_arrival < 376)  arr[i].inter_arrival_time = 3;
        else if (arr[i].randomDigit_arrival > 375 && arr[i].randomDigit_arrival < 501)  arr[i].inter_arrival_time = 4;
        else if (arr[i].randomDigit_arrival > 500 && arr[i].randomDigit_arrival < 626)  arr[i].inter_arrival_time = 5;
        else if (arr[i].randomDigit_arrival > 625 && arr[i].randomDigit_arrival < 751)  arr[i].inter_arrival_time = 6;
        else if (arr[i].randomDigit_arrival > 750 && arr[i].randomDigit_arrival < 876)  arr[i].inter_arrival_time = 7;
        else if (arr[i].randomDigit_arrival > 875 && arr[i].randomDigit_arrival < 1001)  arr[i].inter_arrival_time = 8;
        else { cout << " Please Enter Random Digit for arrival time within limit: around 1-1000" << endl; }
    }
}



//Arrival time scheduling

void Arrival_time_scheduling(Simulation arr[], int n) {

    for (int i = 2; i <= n; i++) {
        arr[i].arrival_time = arr[i - 1].arrival_time + arr[i].inter_arrival_time;
    }
}




//Random digit for service time

// Services (minutes)	1     2       3          4        5	      6//
//Probability	      0.10 	   0.20    	0.30	0.25	0.10	0.05//

void RandomDigitService(Simulation arr[], int n) {
    int rn;
    srand(time(NULL));

    arr[1].service_begin = 0;
    for (int i = 1; i <= n; i++) {

        rn = rand() % 100 + 1;
        arr[i].randomDigit_service = rn;
        if (arr[i].randomDigit_service > 0 && arr[i].randomDigit_service < 11) arr[i].service_time = 1;
        else if (arr[i].randomDigit_service > 10 && arr[i].randomDigit_service < 31)  arr[i].service_time = 2;
        else if (arr[i].randomDigit_service > 30 && arr[i].randomDigit_service < 61)  arr[i].service_time = 3;
        else if (arr[i].randomDigit_service > 60 && arr[i].randomDigit_service < 86)  arr[i].service_time = 4;
        else if (arr[i].randomDigit_service > 85 && arr[i].randomDigit_service < 96)  arr[i].service_time = 5;
        else if (arr[i].randomDigit_service > 95 && arr[i].randomDigit_service < 101)  arr[i].service_time = 6;
        else {
            cout << "please enter Random digit within 1-100" << endl;
            total_service_time += arr[i].service_time;
        }
    }
}



//Service time scheduling

void schedule_service_time(Simulation arr[], int n) {
    arr[1].time_ser_end = arr[1].service_time;
    for (int i = 2; i <= n; i++) {
        if (arr[i].arrival_time > arr[i - 1].time_ser_end) {
            arr[i].service_begin = arr[i].arrival_time;
            arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
        }
        else {
            arr[i].service_begin = arr[i - 1].time_ser_end;
            arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
        }
    }
}


// time for completion of service

void Service_time_completion(Simulation arr[], int n) {

    for (int i = 2; i <= n; i++) {
        arr[i].time_ser_end = arr[i].service_begin + arr[i].service_time;
    }
}


// waiting time

void Customer_idle_waiting_time(Simulation arr[], int n) {

    arr[1].waiting_time = 0;
    arr[1].idle_time = 0;
    for (int i = 2; i <= n; i++) {
        if (arr[i].arrival_time > arr[i - 1].time_ser_end) {
            arr[i].idle_time = arr[i].arrival_time - arr[i - 1].time_ser_end;
            total_idle_time += arr[i].idle_time;
            arr[i].waiting_time = 0;
        }
        else {
            arr[i].waiting_time = arr[i - 1].time_ser_end - arr[i].arrival_time;
            total_waiting_time += arr[i].waiting_time;
            arr[i].idle_time = 0;
        }
        if (arr[i].waiting_time != 0) {
            wait_var = wait_var + 1;
        }

    }
}

// time spent in system-

void Time_spent_in_server(Simulation arr[], int n) {
    for (int i = 1; i <= n; i++) {
        arr[i].spend = arr[i].service_time + arr[i].waiting_time;
        total_spend_time += arr[i].spend;
    }
}


void display(Simulation arr[], int n) {
    cout << "\n\t----------------------------------------------------------------------------------------------------------------------";
    cout << "\n\t| Cust.| RD. for | Inter_arrival | Arrival   | RD. for | Service | T.Service| T.Service| Waiting | Server | Spend in |\n";
    cout << "\t|  No. |Arrival.T|     Time      |  Time     |Service.T|  Time   |  Begin   |    End   | in Queue| Idle.T |  System  |";
    cout << "\n\t----------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 1; i <= n; i++) {
        printf("\t    %d\t   %d\t\t%d\t      %d           %d\t   %d         %d\t\t%d            %d      %d       %d\n"
            , arr[i].customer_number, arr[i].randomDigit_arrival, arr[i].inter_arrival_time, arr[i].arrival_time, arr[i].randomDigit_service, arr[i].service_time, arr[i].service_begin,
            arr[i].time_ser_end, arr[i].waiting_time, arr[i].idle_time, arr[i].spend);

        if (i != n) {
            printf("\t----------------------------------------------------------------------------------------------------------------------\n");
        }
        else {
            printf("\t----------------------------------------------------------------------------------------------------------------------\n");
        }
    }

    printf("\n\n\n\n");

}

int main() {
    int n;
    Simulation arr[100];
    cout << "Enter the number of calls : ";
    cin >> n;
    Random_digit_arrival(arr, n);
    Arrival_time_scheduling(arr, n);
    RandomDigitService(arr, n);

    schedule_service_time(arr, n);

   // Service_time_completion(arr, n);


    Customer_idle_waiting_time(arr, n);
    Time_spent_in_server(arr, n);
    display(arr, n);

}