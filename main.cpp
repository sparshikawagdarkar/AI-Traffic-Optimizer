#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <windows.h> 

using namespace std;

class Vehicle {
public:
    string id;
    int position; 
    int speed;
    bool is_stopped;

    Vehicle(string vehicle_id) {
        id = vehicle_id;
        position = 0;
        speed = 2; // Moves 2 units per second
        is_stopped = false;
    }

    void move() {
        if (!is_stopped) {
            position += speed;
        }
    }
};

class TrafficLight {
public:
    string state; // "RED", "GREEN"
    int timer;    // Seconds left in current state

    TrafficLight() {
        state = "GREEN"; // Start with green
        timer = 5;       // Stays green for 5 seconds
    }

    void update() {
        timer--;
        if (timer <= 0) {
            if (state == "GREEN") {
                state = "RED";
                timer = 5; // Stays red for 5 seconds
            } else {
                state = "GREEN";
                timer = 5;
            }
        }
    }
};

int main() {
    cout << "--- Advanced Traffic Engine Starting ---" << endl;
    
    Vehicle car1("MH-12-AB-1234");
    TrafficLight light1;
    
    int intersection_position = 10; // Light is located at position 10

    // Simulate 15 seconds of time ticking
    for (int second = 1; second <= 15; second++) {
        cout << "\n[Second " << second << "] -----------------------" << endl;
        
        // Update Traffic Light
        light1.update();
        cout << "Traffic Light is: " << light1.state << " (Changes in " << light1.timer << "s)" << endl;

        // Traffic Light Intersection Rule Logic
        if (light1.state == "RED" && car1.position + car1.speed >= intersection_position && car1.position < intersection_position) {
            car1.is_stopped = true;
        } else if (light1.state == "GREEN") {
            car1.is_stopped = false;
        }

        // Move the car
        car1.move();
        cout << "Vehicle " << car1.id << " position: " << car1.position << (car1.is_stopped ? " [STOPPED]" : " [DRIVING]") << endl;

        // Slow down the console print slightly so you can watch it live (1 second delay)
        Sleep(1000); // Sleeps for 1000 milliseconds (1 second)
    }

    cout << "\n--- Simulation Ended ---" << endl;
    return 0;
}