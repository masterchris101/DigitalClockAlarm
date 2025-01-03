#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <string>
#include <atomic>

using namespace std; // Allows you to avoid prefixing with std::

// Global flag to stop threads
atomic<bool> stopClock(false);
atomic<bool> alarmTriggered(false);

// Function to display the clock
void displayClock() {
    while (!stopClock) {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        cout << "\rCurrent Time: " << ctime(&currentTime) << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to handle the alarm logic
void alarmLogic(const string &alarmTime) {
    while (!stopClock) {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        string currentStr = ctime(&currentTime);

        // Check if the current time matches the alarm time
        if (currentStr.find(alarmTime) != string::npos && !alarmTriggered) {
            cout << "\n[ALARM] Time to wake up!\n";
            alarmTriggered = true;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Main function
int main() {
    string alarmTime;
    cout << "Enter alarm time (format: HH:MM:SS): ";
    cin >> alarmTime;

    cout << "Clock is running. Press Ctrl+C to stop.\n";

    // Launch threads for clock display and alarm
    thread clockThread(displayClock);
    thread alarmThread(alarmLogic, alarmTime);

    // Wait for threads to finish
    clockThread.join();
    alarmThread.join();

    return 0;
}


