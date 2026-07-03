#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // Handles native Windows Sleep

using namespace std;

class Vehicle {
public:
    string id;
    int position; 
    int speed;
    bool is_stopped;

    Vehicle(string vehicle_id, int spawn_position) {
        id = vehicle_id;
        position = spawn_position;
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
    int timer;    

    TrafficLight() {
        state = "GREEN"; 
        timer = 5;       
    }

    void update() {
        timer--;
        if (timer <= 0) {
            if (state == "GREEN") {
                state = "RED";
                timer = 5; 
            } else {
                state = "GREEN";
                timer = 5;
            }
        }
    }
};

int main() {
    cout << "--- Traffic Engine: Multi-Vehicle System ---" << endl;
    
    TrafficLight light1;
    vector<Vehicle> traffic_lane;
    
    int intersection_position = 20; // The light is further down the road now
    int car_counter = 1;

    // Simulate 15 seconds
    for (int second = 1; second <= 15; second++) {
        cout << "\n[Second " << second << "] -----------------------" << endl;
        
        // 1. Update Traffic Light
        light1.update();
        cout << "Traffic Light: " << light1.state << " (Changes in " << light1.timer << "s)" << endl;

        // 2. Spawn a new car every 3 seconds at the beginning of the road (position 0)
        if (second % 3 == 0) {
            string car_name = "CAR-" + to_string(car_counter++);
            // To prevent cars from instantly stacking on top of each other at spawn,
            // we only spawn if the lane is empty or the last car has moved forward.
            if (traffic_lane.empty() || traffic_lane.back().position >= 2) {
                traffic_lane.push_back(Vehicle(car_name, 0));
                cout << ">> Spawned " << car_name << " at position 0" << endl;
            }
        }

        // 3. Process Logic for Every Car (Front to Back)
        for (size_t i = 0; i < traffic_lane.size(); i++) {
            
            // Rule A: Check the Traffic Light (Only applies to the leading car near the intersection)
            if (light1.state == "RED" && traffic_lane[i].position + traffic_lane[i].speed >= intersection_position && traffic_lane[i].position < intersection_position) {
                traffic_lane[i].is_stopped = true;
            } 
            // Rule B: Check the car directly in front (Bumper-to-Bumper Queueing)
            else if (i > 0 && traffic_lane[i-1].is_stopped && (traffic_lane[i-1].position - traffic_lane[i].position) <= 2) {
                traffic_lane[i].is_stopped = true; // Stop because the car ahead is stopped
            } 
            // Rule C: Light is green, or road ahead cleared
            else if (light1.state == "GREEN") {
                // Leading car can always go on Green; subsequent cars only move if the gap is safe
                if (i == 0 || !traffic_lane[i-1].is_stopped || (traffic_lane[i-1].position - traffic_lane[i].position) > 2) {
                    traffic_lane[i].is_stopped = false;
                }
            }

            // Move the car based on its updated state
            traffic_lane[i].move();
            cout << "  " << traffic_lane[i].id << " position: " << traffic_lane[i].position 
                 << (traffic_lane[i].is_stopped ? " [STOPPED/QUEUEING]" : " [DRIVING]") << endl;
        }

        Sleep(1000); // 1-second delay
    }

    cout << "\n--- End of Sprint Day 1 ---" << endl;
    return 0;
}