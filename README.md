Overview

The Parking Lot Management System is a console-based application built using Object-Oriented Programming (OOP) concepts in C++. It simulates a real-world parking lot where different types of vehicles can enter and exit while automatically managing parking spaces and calculating parking fees based on the duration of stay.

This project demonstrates the use of classes, inheritance, polymorphism, smart pointers, exception handling, STL containers, and time-based calculations.

✨ Features
Park different types of vehicles
1) Bike
2) Car
3) Truck
Automatic parking spot allocation
Parking spot availability tracking
Vehicle search using registration number
Automatic parking fee calculation
Entry and exit time tracking
Occupied and free spot display
Exception handling for invalid operations
Vehicle not found
Spot already occupied
No available parking space

🛠 Technologies Used
C++
Object-Oriented Programming (OOP)
STL
Vector
String
Smart Pointers (shared_ptr)
Exception Handling
Time Library (ctime)
Math Library (cmath)

🏗 Object-Oriented Concepts Used
Classes
Vehicle
Bike
Car
Truck
ParkingSpot
ParkingLot
Inheritance

Bike, Car, and Truck inherit from the Vehicle class.

Polymorphism

Virtual functions are used to describe different vehicle types.

Encapsulation

Vehicle information and parking lot operations are encapsulated inside their respective classes.

Abstraction

The ParkingLot class hides the internal parking management logic from the user.

📂 Project Structure
ParkingLotManagement/
│
├── main.cpp
└── README.md
⚙️ How It Works
1. Create Parking Lot

A parking lot is initialized with predefined parking spaces for:

Bikes
Cars
Trucks
2. Park Vehicle

When a vehicle enters:

The system searches for the first available parking spot matching the vehicle type.
Entry time is recorded.
Vehicle is assigned to the spot.
3. Display Parking Lot

Displays

Total parking spots
Free spots
Occupied spots
Vehicle details occupying each spot
4. Exit Vehicle

When exiting,

Vehicle is searched using its registration number.
Parking duration is calculated.
Parking fee is generated.
Spot becomes available again.
💰 Parking Charges
Vehicle	Rate per Hour
Bike	₹20
Car	₹40
Truck	₹80

The fee is calculated based on the total parking duration using:

Fee = ceil(Duration × Hourly Rate)
▶️ Sample Output
=== Main Lot ===
Total: 9 | Free: 9 | Occupied: 0

✓ Car [KL01AB1234] parked at spot C1
✓ Bike [KL02CD5678] parked at spot B1
✓ Truck [KL03EF9012] parked at spot T1

=== Main Lot ===
Total: 9 | Free: 6 | Occupied: 3

✓ Car [KL01AB1234] exited from spot C1
Duration: 1.25h
Fee: Rs.50
🚀 How to Run

Compile using g++:

g++ main.cpp -o parking

Run:

./parking

For Windows:

g++ main.cpp -o parking.exe
parking.exe
📚 Concepts Demonstrated
Object-Oriented Design
Class Relationships
Inheritance
Polymorphism
Smart Pointer Memory Management
Exception Handling
STL Containers
Time-based Calculations
Modular Code Organization
🔮 Future Enhancements
Interactive menu-driven interface
Multiple parking floors
Different parking fee strategies
Reservation system
Admin dashboard
Database integration
File-based data persistence
Online payment integration
Parking history reports
Vehicle search by owner details

🎯 Learning Outcomes
This project helped in understanding:

1)Real-world application of OOP principles
2)Designing modular and maintainable C++ applications
3)Managing dynamic memory using smart pointers
4)Using STL effectively
5)Handling runtime exceptions gracefully
6)Building scalable software architecture

 Author :Naga Shunmuga Priya
Project Type: Console-Based C++ Application
Language: C++
Focus: Object-Oriented Programming & Data Structures
