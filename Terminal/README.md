# Airline Ticket Booking System

A colorful terminal-based application for managing airline ticket bookings with an intuitive user interface.

## 🚀 Features

- Book seats for flights
- Cancel reservations
- View available seats
- View all seat statuses
- Mark seats as broken
- Repair broken seats
- Color-coded interface for better visualization

## 🛠️ Tech Stack

<div align="left">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/Terminal-4D4D4D?style=for-the-badge&logo=windows-terminal&logoColor=white" alt="Terminal"/>
</div>

## 📋 Prerequisites

- C++ compiler (g++ or clang++)
- Terminal that supports ANSI color codes

## 🔧 Installation

1. Clone the repository:
```bash
git clone https://github.com/skurbro/Booking-airline-tickets.git
```

```bash
cd Booking-airline-tickets
```
2. Compile the program:
```bash
g++ -std=c++11 terminal/ticket_booking_system.cpp -o ticket_booking_system
```

## 🚀 Usage
Run the compiled program:
```bash
./ticket_booking_system
```

## 📖 How to Use
1. Use the menu to navigate through different options
2. Select seats by entering their number
3. Follow the color-coded interface:
   - 🟢 Green: Available seats
   - 🟡 Yellow: Reserved seats
   - 🔴 Red: Broken seats