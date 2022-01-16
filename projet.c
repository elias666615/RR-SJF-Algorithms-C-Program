#include <stdio.h>

// Elias Bou Selwan
//  SJF and Round Robin

int main() {

// ---------- INPUT ----------
int algo;
printf("Enter (0) for Shortest Job First and (1) for Round Robin: ");
scanf("%d", &algo);
printf("===================================================================\n");
int number_of_processes;
printf("Enter the number of processes: ");
scanf("%d", &number_of_processes);
printf("===================================\n");
int process[number_of_processes]; // Will store the process ordered by arrival time
float bt[number_of_processes]; // Will store the burst times in order of input
float bt2[number_of_processes]; // Backup for calculating the output
float at[number_of_processes]; // Wi;; store the arrival times in order of input
for (int i = 0; i < number_of_processes; ++i) {
process[i] = i;
float arrival_time;
float burst_time;
printf("Process %d\n", i);
printf("Arrival time: ");
scanf("%f", &arrival_time);
at[i] = arrival_time;
printf("Burst time: ");
scanf("%f", &burst_time);
bt[i] = burst_time;
bt2[i] = burst_time;
printf("===================================\n");
}

// Sort the process array by arrival time
for(int i = 1; i < number_of_processes;  ++i){
for(int j = 0; j < number_of_processes - i; ++j){
if (at[process[j]] > at[process[j+1]] || (algo == 0 && ((at[process[j]] == at[process[j+1]]) && bt[process[j]] > bt[process[j+1]])))
{
int tmp = process[j];
process[j] = process[j+1];
process[j+1]=tmp;
}}}

// if user selects round robin he will be asked to give the time quantum
float tq;
if(algo == 1){
printf("Enter the time quantum: ");
scanf("%f", &tq);
}

// ---------- CALCULATE THE EXIT TIMES ----------
float et[number_of_processes]; // will store the exit times
float time = 0; // keeps track of time
int queue[number_of_processes]; //circular array
int start = 0; // Where the queue starts
int end = 0; // where the queue ends
int process_passed = 0;
int content = 0;
int current_process; // Points to the current process

// if Shortest Job First is selected
if(algo == 0){
int n = 0;
while(n < number_of_processes){
if(content == 0) {
queue[end] = process[process_passed];
++content;
++end;
++process_passed;
}
current_process = queue[start];
++start;
--content;
if(at[current_process] > time) time = at[current_process];
time = time + bt[current_process];
et[current_process] = time;
++n;

int j;
for(int i = process_passed; i < number_of_processes; i++){
if(at[process[i]] <= time){
queue[end] = process[i];
end++;
content++;
process_passed++;
}}

for(int i = 0; i < end - 1 - start;  ++i){
for(int j = start; j < (end -1)- i; ++j){
float bt1 = bt[queue[j]];
float bt2 = bt[queue[j+1]];
if (bt1 > bt2)
{
int tmp = queue[j];
queue[j] = queue[j+1];
queue[j+1]=tmp;
}
}}

}}

// if Round Robin is selected
if(algo == 1){

queue[end] = process[0];
++process_passed;
++end;
++content;

int n = 0;
while(n < number_of_processes) {
if (content == 0) { 
queue[end] = process[process_passed]; 
++process_passed;
++content; 
if (end != number_of_processes - 1) end++;
else end = 0; }
current_process = queue[start];
--content;
if (start != number_of_processes - 1) start++;
else start = 0;
if(at[current_process] > time) time = at[current_process];
if(bt[current_process] <= tq) {
time = time + bt[current_process];
et[current_process] = time;
++n;
}
else {
bt[current_process] = bt[current_process] - tq;
time = time + tq;

for(int h = process_passed; h < number_of_processes; h++) {
if (at[process[h]] <= time) {
queue[end] = process[h];
++process_passed;
++content;
if (end != number_of_processes - 1) end++;
else end = 0;
}
}
queue[end] = current_process;
++content;
if(end != number_of_processes - 1) end++;
else end = 0;
}
}
}

// ---------- OUTPUT ----------
float waiting_time_sum = 0;
float tat_sum = 0;
   printf("\n\nResults:\n");
printf("%20s %20s %20s %20s", " ", "Exit time", "Waiting time", "Turn Around time");
printf("\n================================================================================================\n");
int y;
for(y =0; y < number_of_processes; y++) {
printf("%19s%d %19f %19f %19f\n", "Process", y, et[y], (et[y] - at[y]) - bt2[y], et[y] - at[y]);
waiting_time_sum += (et[y] - at[y]) - bt2[y];
tat_sum += et[y] - at[y];
}
printf("\n");
printf("Average waiting time: %0.2f\n", waiting_time_sum/number_of_processes);
printf("Average turn around time: %0.2f\n", tat_sum/number_of_processes);


return 0;
}


