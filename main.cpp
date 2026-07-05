#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h> 

using namespace std;

class Vehicle {
public:
    string id;
    int position; 
    int speed;
    bool is_stopped;
    int total_wait_time;

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
            total_wait_time++;
        }
    }
};

int main() {
    cout << "--- Traffic Engine: Day 3 File I/O Bridging ---" << endl;
    
    // Clean start: remove any remnant action files
    DeleteFileA("action.txt");

    vector<Vehicle> traffic_lane;
    int intersection_position = 20; 
    int car_counter = 1;
    string current_light_state = "GREEN"; 
    
    int global_cumulative_delay = 0;
    int max_queue_length = 0;

    for (int second = 1; second <= 20; second++) {
        cout << "\n[Second " << second << "] -----------------------" << endl;
        
        // Spawn logic (every 3 seconds)
        if (second % 3 == 0) {
            string car_name = "CAR-" + to_string(car_counter++);
            if (traffic_lane.empty() || traffic_lane.back().position >= 2) {
                traffic_lane.push_back(Vehicle(car_name, 0));
                cout << ">> Spawned " << car_name << " at position 0" << endl;
            }
        }

        int current_frame_queue = 0;

        // Calculate queue size
        for (size_t i = 0; i < traffic_lane.size(); i++) {
            if (current_light_state == "RED" && traffic_lane[i].position + traffic_lane[i].speed >= intersection_position && traffic_lane[i].position < intersection_position) {
                traffic_lane[i].is_stopped = true;
            } else if (i > 0 && traffic_lane[i-1].is_stopped && (traffic_lane[i-1].position - traffic_lane[i].position) <= 2) {
                traffic_lane[i].is_stopped = true; 
            } else if (current_light_state == "GREEN") {
                if (i == 0 || !traffic_lane[i-1].is_stopped || (traffic_lane[i-1].position - traffic_lane[i].position) > 2) {
                    traffic_lane[i].is_stopped = false;
                }
            }
            if (traffic_lane[i].is_stopped) current_frame_queue++;
        }

        if (current_frame_queue > max_queue_length) {
            max_queue_length = current_frame_queue;
        }

        // --- 1. WRITE STATE FOR PYTHON ---
        ofstream outfile("state.txt");
        outfile << current_frame_queue << endl;
        outfile.close();

        // --- 2. WAIT AND READ ACTION FROM PYTHON ---
        // Instead of sleeping, loop until action.txt arrives
        while (GetFileAttributesA("action.txt") == INVALID_FILE_ATTRIBUTES) {
            Sleep(50); // Small sleep to avoid eating 100% CPU
        }

        ifstream infile("action.txt");
        string python_action;
        if (infile >> python_action) {
            if (python_action == "RED" || python_action == "GREEN") {
                current_light_state = python_action;
            }
        }
        infile.close();
        DeleteFileA("action.txt"); // Clear the action file for the next turn

        cout << "Traffic Light State (From Python Action File): " << current_light_state << endl;

        // Apply movement after light update
        for (size_t i = 0; i < traffic_lane.size(); i++) {
            traffic_lane[i].move();
            if (traffic_lane[i].is_stopped) {
                global_cumulative_delay++;
            }
            cout << "  " << traffic_lane[i].id << " position: " << traffic_lane[i].position 
                 << (traffic_lane[i].is_stopped ? " [STOPPED]" : " [DRIVING]") << endl;
        }

        Sleep(1000); // Maintain a visible 1-second pace per frame
    }

    cout << "\n=============================================" << endl;
    cout << "🚦 FILE I/O RUN COMPLETE 🚦" << endl;
    cout << "Total Cumulative Delay: " << global_cumulative_delay << " vehicle-seconds." << endl;
    cout << "Maximum Traffic Queue Encountered: " << max_queue_length << " vehicles." << endl;
    cout << "=============================================" << endl;

    return 0;
}