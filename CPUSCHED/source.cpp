#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <bits/stdc++.h> 

#define numOfProcesses 500

using namespace std;

// Define a structure to represent a CPU process
struct CPU_Process{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;
    int responseTime;
};

// Function to read CPU process data from a file named "datafile.txt"
void readData(vector<CPU_Process>& processes){
    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    // if statement to determine if input file successfully opened
    if (!inFile) {
        cerr << "Error opening datafile.txt" << endl;
        return;
    } 

    int arrivalTime, CPU_BurstLength, priority;
    int processCounter = 0;

    // Read CPU process data from the input file
    getline(inFile, firstLine);
    while(inFile >> arrivalTime >> CPU_BurstLength >> priority){
        // Create a CPU_Process struct to push read in material to the processes vector
        CPU_Process p = {arrivalTime, CPU_BurstLength, priority};
        processes.push_back(p);
        processCounter++;
    }

    // Close the input file after reading in
    inFile.close();
    
    // **Test to see if input was successful**
    // for (CPU_Process p : processes) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }
}

// Function to calculate and display statistics for CPU processes
void calculations(int totalElapsedTime, int totalCPUBurstTime, int totalIdleTime, int totalWaitingTime, 
                  int totalResponseTime, int totalTurnaroundTime){

    // Calculate throughoutput (proccesses per unit of time) and CPU utilization
    double throughput = static_cast<double>(numOfProcesses) / totalElapsedTime;
    double cpuUtilization = static_cast<double>(totalCPUBurstTime) / totalElapsedTime;

    // Display calculations 
    cout << "Number of processes: " << numOfProcesses << endl;
    cout << "Total elapsed time (for the scheduler): " << totalElapsedTime << endl;
    cout << "Throughput (Number of processes executed in one unit " 
            "of CPU burst time): " << throughput << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time (in CPU burst times): " << static_cast<double>(totalWaitingTime)/numOfProcesses << endl;
    cout << "Average turnaround time (in CPU burst times): " << static_cast<double>(totalTurnaroundTime)/ numOfProcesses << endl;
    cout << "Average response time (in CPU burst times): " << static_cast<double>(totalResponseTime)/ numOfProcesses << endl << endl << endl;
}

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(vector<CPU_Process> processes){
    // Declare variables
    int totalElapsedTime        = 0;
    int numOfCompletedProcesses = 0;
    int totalCPUBurstTime       = 0;
    int totalWaitingTime        = 0;
    int totalTurnaroundTime     = 0;
    int totalResponseTime       = 0;
    int currentTime             = 0;

    for(CPU_Process p : processes){
        // Wait for the next proccess if the current one has not arrived
        if(p.arrivalTime > currentTime) {
            currentTime = p.arrivalTime;
        }

        // Calculate response time (FIX THIS)
        // int responseTime = currentTime - p.arrivalTime;
        // totalResponseTime += responseTime;

        // Calculate waiting time
        int waitingTime = currentTime - p.arrivalTime;
        totalWaitingTime += waitingTime;

        // Simulate the CPU's burst time
        currentTime += p.CPU_BurstLength;

        // Calculate turnaround time
        int turnaroundTime = currentTime - p.arrivalTime;
        totalTurnaroundTime += turnaroundTime;

        // Calculate total CPU burst time
        totalCPUBurstTime += p.CPU_BurstLength;

        // Increment the number of completed processes
        numOfCompletedProcesses++;

        // Exit the loop when 500 processes are completed
        if(numOfCompletedProcesses >= 500){
            break;
        }
    }

    currentTime = totalElapsedTime;

    cout << "\nStatistics for FIFO Scheduling\n\n";
    calculations(totalElapsedTime, totalCPUBurstTime, totalElapsedTime - totalCPUBurstTime,
                 totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes){
    // Declare variables
    int totalElapsedTime        = 0;
    int numOfCompletedProcesses = 0;
    int totalCPUBurstTime       = 0;
    int totalWaitingTime        = 0;
    int totalTurnaroundTime     = 0;
    int totalResponseTime       = 0;
    int currentTime             = 0;
    int totalIdleTime           = 0;

    vector<CPU_Process> buffer;

    // Arrival time CPU Burst length Priority
    // 10 22 1 
    // 68 12 6
    // 98 34 8
    // 148 28 10
    // 192 3 3
    // 223 8 3
    // 266 18 2
    // 268 14 10
    // 268 30 4

    for(CPU_Process p : processes){
        // Buffer is Empty
        if(buffer.empty())
        {
            totalIdleTime = totalIdleTime + p.arrivalTime - currentTime;
            currentTime = currentTime + (p.arrivalTime - currentTime);
            buffer.push_back(p);
        } 
        // There are ___ processes in the vector
        else 
        { 
            // Calculating Time Difference
            int diff = p.arrivalTime - currentTime;

            cout << "calculated time difference     " << numOfCompletedProcesses << endl;
            // Updating buffer based off time difference
            for(CPU_Process b : buffer){
                cout << "entered for loop looping on processes in buffer" << endl;
                if(b.CPU_BurstLength >= diff){
                    b.CPU_BurstLength -= diff;
                    diff = 0;
                    cout << "if statement complete" << endl;
                    break;
                } else {
                    cout << "entered else" << endl;
                    diff -= b.CPU_BurstLength;
                    b.CPU_BurstLength = 0;
                    if(b.CPU_BurstLength == 0){
                        cout << "Buffer process burst length == 0" << endl;
                        buffer.erase(buffer.begin());
                        cout << "erased first process from buffer" << endl;
                        numOfCompletedProcesses++;
                        if(numOfCompletedProcesses == numOfProcesses){
                            cout << "\nStatistics for SJF Scheduling\n\n";
                            calculations(totalElapsedTime, totalCPUBurstTime, totalIdleTime,
                                         totalWaitingTime, totalResponseTime, totalTurnaroundTime);
                        }
                    }
                } 
            }

            // Updating totalIdleTime
            if(diff > 0){
                totalIdleTime += diff;
            }

            currentTime = p.arrivalTime;

            buffer.push_back(p);

            // ***sort buffer by burst for SJF.***
            // sort(buffer.CPU_BurstLength);
        }
    }
}


// Function to perform Preemptive Priority Scheduling
void preemptivePriority(vector<CPU_Process>& processes){
    
    cout << "\nStatistics for Preemptive Priority Scheduling\n\n";
    // calculations(totalElapsedTime, totalCPUBurstTime, totalIdleTime,
    //              totalWaitingTime, totalResponseTime, totalTurnaroundTime);
} 

int main(){
    // Declare needed variables
    vector<CPU_Process> processes;

    // Read process data from the input file, save to vector of processes
    readData(processes);

    // Perform FIFO CPU scheduling 
    FIFO(processes);
 
    // Perform SJF CPU scheduling
    SJF(processes);

    // Perform Preemptive Priority Scheduling
    preemptivePriority(processes);

    return 0;
}

