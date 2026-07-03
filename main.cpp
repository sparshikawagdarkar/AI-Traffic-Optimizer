#include <iostream>
#include <vector>
#include <string>
#include <windows.h> 

using namespace std;

class Vehicle {
public:
    string id;
    int position; 
    int speed;
    bool is_stopped;
    int total_wait_time; // Track individual car delay

    Vehicle(string vehicle_id, int spawn_position) {
        id = vehicle_id;
        position = spawn_position;
        speed = 2; 
        is_stopped = false;
        total_wait_time = 0;
    }

    void move() {
        if (!is_stopped) {
            position += speed;
        } else {
            total_wait_time++; // Accumulate delay if stopped
        }
    }
};

class TrafficLight {
public:
    string state; 
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
    cout << "--- Traffic Engine: Day 2 Metrics Baseline ---" << endl;
    
    TrafficLight light1;
    vector<Vehicle> traffic_lane;
    
    int intersection_position = 20; 
    int car_counter = 1;
    
    // Day 2 System Performance Metrics
    int global_cumulative_delay = 0;
    int max_queue_length = 0;

    // Simulate for 20 seconds today to gather more data
    for (int second = 1; second <= 20; second++) {
        cout << "\n[Second " << second << "] -----------------------" << endl;
        
        light1.update();
        cout << "Traffic Light: " << light1.state << " (Changes in " << light1.timer << "s)" << endl;

        // Spawn logic (every 3 seconds)
        if (second % 3 == 0) {
            string car_name = "CAR-" + to_string(car_counter++);
            if (traffic_lane.empty() || traffic_lane.back().position >= 2) {
                traffic_lane.push_back(Vehicle(car_name, 0));
                cout << ">> Spawned " << car_name << " at position 0" << endl;
            }
        }

        int current_frame_queue = 0;

        // Process Logic for Every Car
        for (size_t i = 0; i < traffic_lane.size(); i++) {
            // Intersection Light Check
            if (light1.state == "RED" && traffic_lane[i].position + traffic_lane[i].speed >= intersection_position && traffic_lane[i].position < intersection_position) {
                traffic_lane[i].is_stopped = true;
            } 
            // Queueing Check
            else if (i > 0 && traffic_lane[i-1].is_stopped && (traffic_lane[i-1].position - traffic_lane[i].position) <= 2) {
                traffic_lane[i].is_stopped = true; 
            } 
            // Light Green/Move Check
            else if (light1.state == "GREEN") {
                if (i == 0 || !traffic_lane[i-1].is_stopped || (traffic_lane[i-1].position - traffic_lane[i].position) > 2) {
                    traffic_lane[i].is_stopped = false;
                }
            }

            traffic_lane[i].move();
            
            // Track metrics for this specific frame
            if (traffic_lane[i].is_stopped) {
                current_frame_queue++;
                global_cumulative_delay++;
            }

            cout << "  " << traffic_lane[i].id << " position: " << traffic_lane[i].position 
                 << (traffic_lane[i].is_stopped ? " [STOPPED]" : " [DRIVING]") 
                 << " | Delay: " << traffic_lane[i].total_wait_time << "s" << endl;
        }

        // Keep track of the worst gridlock we encountered
        if (current_frame_queue > max_queue_length) {
            max_queue_length = current_frame_queue;
        }

        Sleep(1000); 
    }

    // Print final baseline performance scorecard
    cout << "\n=============================================" << endl;
    cout << "🚦 BASELINE SYSTEM PERFORMANCE SCORECARD 🚦" << endl;
    cout << "=============================================" << endl;
    cout << "Total Cumulative Delay: " << global_cumulative_delay << " vehicle-seconds." << endl;
    cout << "Maximum Traffic Queue Encountered: " << max_queue_length << " vehicles." << endl;
    cout << "=============================================" << endl;

    return 0;
}