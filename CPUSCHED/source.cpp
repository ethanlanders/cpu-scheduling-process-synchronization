#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#define numOfProcesses 500

using namespace std;

struct CPU_Process{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;  
};

void readData(vector<CPU_Process>& process){
    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    int arrivalTime, CPU_BurstLength, priority;
    int processCounter = 0;
    getline(inFile, firstLine);
    while(inFile >> arrivalTime >> CPU_BurstLength >> priority){
        CPU_Process p = {arrivalTime, CPU_BurstLength, priority};
        process.push_back(p);
        processCounter++;
    }
    inFile.close();
}

void output(){
    cout << "Statistics for the Run\n\n";
    cout << "Number of processes: " << numOfProcesses << endl;
    cout << "Total elapsed time (for the scheduler): " << endl;
    cout << "Throughput (Number of processes executed in one unit " 
            "of CPU burst time): " << endl;
    cout << "CPU utilization: " << endl;
    cout << "Average waiting time (in CPU burst times): " << endl;
    cout << "Average turnaround time (in CPU burst times): " << endl;
    cout << "Average response time (in CPU burst times): " << endl;
}

void FIFO(queue<CPU_Process>& q){
    
    int time = 0;

    while(!q.empty()){
        CPU_Process process = q.front();

    }

    output();
}

void SJF(queue<CPU_Process>& q){
    output();
}

void preemptivePriority(queue<CPU_Process>& q){
    output();
}

int main(){
    // Declare needed variables
    queue<CPU_Process> q;
    vector<CPU_Process> process;

    // Read from input file
    readData(process);
    
    // for (const CPU_Process& p : process) {
    //     q.push(p);
    // }

    //FIFO(q);

    // Test
    for (const CPU_Process& p : process) {
        cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    }
    return 0;
}
