/*
 * 2016/4/22, Baidu online programming test
 * find the average waiting time of the Shortest Job First algorithm
*/
#include <iostream>
#include <queue>

using namespace std;

// a struct for storing in priority_queue
// without losing the connection between request_time and duration
struct task {
    int request_time;
    int duration;
    int index;
    bool operator < (const task &t2) const {
        return t2.duration < duration;
    }
};

//the requestTimes[] must be in non-decreasing order
double avgWaitingTime(int requestTimes[], int durations[], int n) {
    int waiting_time = 0, current_time = 0;
    priority_queue< task > pq;
    task tasks[n];
    //if the first requestTime is not 0, normalize them
    int base_time = requestTimes[0];
    //transform two arrays into one array of tasks
    for(int i = 0; i < n; ++i) {
        requestTimes[i] = requestTimes[i] - base_time;
        tasks[i].index = i;
        tasks[i].request_time = requestTimes[i];
        tasks[i].duration = durations[i];
    }

    task current_task;
    for(int i = 0; i < n; ++i) {
        //before putting the new task into pri-queue, check if there is some tasks can be shifted from the pri-queue
        while (!pq.empty() && tasks[i].request_time >= current_time && tasks[i].request_time > pq.top().request_time) {
            current_task = pq.top();
            pq.pop();
            waiting_time += current_time - current_task.request_time; //update total waiting time
            current_time += current_task.duration; //update the current time as the finished time of the current task
        }
        pq.push(tasks[i]);
    }
    //all tasks have been pri-queue, shift them out one by one and update the time
    while (!pq.empty()) {
        current_task = pq.top();
        pq.pop();
        waiting_time += current_time - current_task.request_time;
        current_time += current_task.duration;
    }
    return (double)waiting_time / n;
}

int main() {
    //Test cases
    int a[4] = {0, 1, 2, 3};
    int b[4] = {8, 4, 9, 5};
    int c[4] = {0, 0, 0, 0};
    int d[4] = {10, 15, 7, 4};
    int e[5] = {1, 2, 3, 4, 8};
    int f[5] = {3, 1, 2, 4, 3};
    cout << avgWaitingTime(a, b, 4) << endl;
    cout << avgWaitingTime(c, d, 4) << endl;
    cout << avgWaitingTime(e, f, 5) << endl;
    return 0;
}
