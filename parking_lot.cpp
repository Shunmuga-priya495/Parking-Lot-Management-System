#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <cmath>

using namespace std;

// ─── Enums ───────────────────────────────────────────────────────────────────

enum class VehicleType { BIKE, CAR, TRUCK };
enum class SpotType    { BIKE, CAR, TRUCK };

string vehicleTypeStr(VehicleType t) {
    switch(t) { case VehicleType::BIKE: return "Bike"; case VehicleType::CAR: return "Car"; default: return "Truck"; }
}

// ─── Vehicle ─────────────────────────────────────────────────────────────────

class Vehicle {
public:
    string       plate;
    VehicleType  type;
    time_t       entryTime;

    Vehicle(const string& plate, VehicleType type)
        : plate(plate), type(type), entryTime(time(nullptr)) {}

    int ratePerHour() const {
        switch (type) {
            case VehicleType::BIKE:  return 20;
            case VehicleType::CAR:   return 40;
            case VehicleType::TRUCK: return 80;
        }
        return 40;
    }

    double durationHours() const {
        return difftime(time(nullptr), entryTime) / 3600.0;
    }

    int fee() const {
        double hrs = max(durationHours(), 1.0 / 60.0);
        return (int)ceil(hrs * ratePerHour());
    }

    virtual string describe() const {
        return vehicleTypeStr(type) + " [" + plate + "]";
    }

    virtual ~Vehicle() = default;
};

class Bike  : public Vehicle { public: Bike(const string& p)  : Vehicle(p, VehicleType::BIKE)  {} };
class Car   : public Vehicle { public: Car(const string& p)   : Vehicle(p, VehicleType::CAR)   {} };
class Truck : public Vehicle { public: Truck(const string& p) : Vehicle(p, VehicleType::TRUCK) {} };

// ─── ParkingSpot ─────────────────────────────────────────────────────────────

class ParkingSpot {
public:
    string     id;
    SpotType   type;
    shared_ptr<Vehicle> vehicle;

    ParkingSpot(const string& id, SpotType type) : id(id), type(type), vehicle(nullptr) {}

    bool isFree() const { return vehicle == nullptr; }

    void park(shared_ptr<Vehicle> v) {
        if (!isFree()) throw runtime_error("Spot " + id + " is already occupied.");
        vehicle = v;
    }

    shared_ptr<Vehicle> vacate() {
        if (isFree()) throw runtime_error("Spot " + id + " is already empty.");
        auto v = vehicle;
        vehicle = nullptr;
        return v;
    }

    void display() const {
        cout << "  [" << id << "] ";
        if (isFree()) cout << "(free)\n";
        else cout << vehicle->describe() << "\n";
    }
};

// ─── ParkingLot ──────────────────────────────────────────────────────────────

class ParkingLot {
    string name;
    vector<ParkingSpot> spots;

public:
    ParkingLot(const string& name) : name(name) {}

    void addSpot(const string& id, SpotType type) {
        spots.emplace_back(id, type);
    }

    ParkingSpot* findFreeSpot(SpotType type) {
        for (auto& s : spots)
            if (s.isFree() && s.type == type) return &s;
        return nullptr;
    }

    ParkingSpot* findByPlate(const string& plate) {
        for (auto& s : spots)
            if (!s.isFree() && s.vehicle->plate == plate) return &s;
        return nullptr;
    }

    // Park vehicle in first suitable free spot
    ParkingSpot* parkVehicle(shared_ptr<Vehicle> v) {
        SpotType needed = static_cast<SpotType>(v->type);
        ParkingSpot* spot = findFreeSpot(needed);
        if (!spot) throw runtime_error("No free spot available for " + vehicleTypeStr(v->type));
        spot->park(v);
        cout << "✓ " << v->describe() << " parked at spot " << spot->id << "\n";
        return spot;
    }

    // Exit by plate, returns fee
    int exitVehicle(const string& plate) {
        ParkingSpot* spot = findByPlate(plate);
        if (!spot) throw runtime_error("Vehicle " + plate + " not found.");
        int f = spot->vehicle->fee();
        double hrs = spot->vehicle->durationHours();
        cout << "✓ " << spot->vehicle->describe()
             << " exited from spot " << spot->id
             << " | Duration: " << fixed << setprecision(2) << hrs << "h"
             << " | Fee: Rs." << f << "\n";
        spot->vacate();
        return f;
    }

    void displayAll() const {
        int free = 0, occ = 0;
        for (auto& s : spots) s.isFree() ? ++free : ++occ;
        cout << "\n=== " << name << " ===\n";
        cout << "Total: " << spots.size() << "  |  Free: " << free << "  |  Occupied: " << occ << "\n";
        for (auto& s : spots) s.display();
        cout << "\n";
    }
};

// ─── Demo ─────────────────────────────────────────────────────────────────────

int main() {
    ParkingLot lot("Main Lot");

    // Add spots
    for (int i = 1; i <= 3; i++) lot.addSpot("B" + to_string(i), SpotType::BIKE);
    for (int i = 1; i <= 4; i++) lot.addSpot("C" + to_string(i), SpotType::CAR);
    for (int i = 1; i <= 2; i++) lot.addSpot("T" + to_string(i), SpotType::TRUCK);

    lot.displayAll();

    try {
        lot.parkVehicle(make_shared<Car>("KL01AB1234"));
        lot.parkVehicle(make_shared<Bike>("KL02CD5678"));
        lot.parkVehicle(make_shared<Truck>("KL03EF9012"));
        lot.parkVehicle(make_shared<Car>("KL04GH3456"));
        lot.displayAll();

        lot.exitVehicle("KL01AB1234");
        lot.exitVehicle("KL02CD5678");
        lot.displayAll();

        // Error: vehicle not found
        lot.exitVehicle("NOTHERE");
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}