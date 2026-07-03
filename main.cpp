#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class to represent an individual vehicle
class Vehicle {
public:
    string id;
    int position; // Distance from start of the lane
    int speed;

    Vehicle(string vehicle_id) {
        id = vehicle_id;
        position = 0;
        speed = 1; // Basic initial speed
    }

    void move() {
        position += speed;
    }
};

// Class to manage the traffic light state
class TrafficLight {
public:
    string state; // "RED", "YELLOW", "GREEN"

    TrafficLight() {
        state = "RED"; // Default starting state
    }

    void changeState(string newState) {
        state = newState;
    }
};

int main() {
    cout << "--- Traffic Simulation Engine Initialized ---" << endl;
    
    // Create a mock vehicle and traffic light to test setup
    Vehicle car1("MH-12-AB-1234");
    TrafficLight light1;

    cout << "Vehicle " << car1.id << " spawned at position " << car1.position << endl;
    cout << "Current traffic light state: " << light1.state << endl;

    return 0;
}