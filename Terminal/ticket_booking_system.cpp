#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

// ANSI color codes for console output
namespace Color {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string BOLD = "\033[1m";
}

// Enum class for seat statuses
enum class SeatStatus {
    Available,  // Seat is available
    Reserved,   // Seat is reserved
    Broken      // Seat is broken
};

// Enum class for menu options
enum class MenuOptions {
    BookSeat,           // Book a seat
    CancelReservation,  // Cancel a reservation
    ViewAvailableSeats, // View available seats
    ViewAllSeatStatus,  // View all seat statuses
    MarkBroken,         // Mark seat as broken
    RepairSeat,         // Repair broken seat
    Exit                // Exit the program
};

// Seat class to represent a single seat
class Seat {
private:
    int seatNumber;
    SeatStatus status;

public:
    Seat(int number, SeatStatus initialStatus = SeatStatus::Available) 
        : seatNumber(number), status(initialStatus) {}

    int getNumber() const { return seatNumber; }
    SeatStatus getStatus() const { return status; }
    
    void setStatus(SeatStatus newStatus) { status = newStatus; }

    // Operator overloading for displaying seat information with colors
    friend std::ostream& operator<<(std::ostream& os, const Seat& seat) {
        os << "Seat #" << seat.seatNumber << " - Status: ";
        switch (seat.status) {
            case SeatStatus::Available: 
                os << Color::GREEN << "Available" << Color::RESET; 
                break;
            case SeatStatus::Reserved: 
                os << Color::YELLOW << "Reserved" << Color::RESET; 
                break;
            case SeatStatus::Broken: 
                os << Color::RED << "Broken" << Color::RESET; 
                break;
        }
        return os;
    }
};

// Namespace for ticket booking system
namespace TicketingSystem {
    // Booking logic namespace
    namespace Booking {
        // Function to book a seat
        bool bookSeat(std::vector<Seat>& seats, int seatNumber) {
            if (seatNumber < 1 || seatNumber > seats.size()) {
                std::cout << "Invalid seat number. Please choose a seat between 1 and " << seats.size() << std::endl;
                return false;
            }
            
            Seat& seat = seats[seatNumber - 1];
            if (seat.getStatus() == SeatStatus::Available) {
                seat.setStatus(SeatStatus::Reserved);
                std::cout << "Seat #" << seatNumber << " has been reserved successfully." << std::endl;
                return true;
            } else if (seat.getStatus() == SeatStatus::Reserved) {
                std::cout << "Seat #" << seatNumber << " is already reserved." << std::endl;
                return false;
            } else {
                std::cout << "Seat #" << seatNumber << " is broken and cannot be reserved." << std::endl;
                return false;
            }
        }

        // Function to cancel a reservation
        bool cancelReservation(std::vector<Seat>& seats, int seatNumber) {
            if (seatNumber < 1 || seatNumber > seats.size()) {
                std::cout << "Invalid seat number. Please choose a seat between 1 and " << seats.size() << std::endl;
                return false;
            }
            
            Seat& seat = seats[seatNumber - 1];
            if (seat.getStatus() == SeatStatus::Reserved) {
                seat.setStatus(SeatStatus::Available);
                std::cout << "Reservation for seat #" << seatNumber << " has been cancelled." << std::endl;
                return true;
            } else if (seat.getStatus() == SeatStatus::Available) {
                std::cout << "Seat #" << seatNumber << " is not reserved." << std::endl;
                return false;
            } else {
                std::cout << "Seat #" << seatNumber << " is broken and has no reservation to cancel." << std::endl;
                return false;
            }
        }

        // Function to mark a seat as broken
        bool markSeatAsBroken(std::vector<Seat>& seats, int seatNumber) {
            if (seatNumber < 1 || seatNumber > seats.size()) {
                std::cout << Color::RED << "Invalid seat number. Please choose a seat between 1 and " << seats.size() << Color::RESET << std::endl;
                return false;
            }
            
            Seat& seat = seats[seatNumber - 1];
            if (seat.getStatus() == SeatStatus::Broken) {
                std::cout << Color::YELLOW << "Seat #" << seatNumber << " is already marked as broken." << Color::RESET << std::endl;
                return false;
            } else {
                seat.setStatus(SeatStatus::Broken);
                std::cout << Color::GREEN << "Seat #" << seatNumber << " has been marked as broken." << Color::RESET << std::endl;
                return true;
            }
        }

        // Function to repair a broken seat
        bool repairSeat(std::vector<Seat>& seats, int seatNumber) {
            if (seatNumber < 1 || seatNumber > seats.size()) {
                std::cout << Color::RED << "Invalid seat number. Please choose a seat between 1 and " << seats.size() << Color::RESET << std::endl;
                return false;
            }
            
            Seat& seat = seats[seatNumber - 1];
            if (seat.getStatus() != SeatStatus::Broken) {
                std::cout << Color::YELLOW << "Seat #" << seatNumber << " is not broken and doesn't need repair." << Color::RESET << std::endl;
                return false;
            } else {
                seat.setStatus(SeatStatus::Available);
                std::cout << Color::GREEN << "Seat #" << seatNumber << " has been repaired and is now available." << Color::RESET << std::endl;
                return true;
            }
        }
    }

    // UI namespace for menu and user interaction
    namespace UI {
        // Function to display the menu with improved visuals
        void displayMenu() {
            std::cout << "\n" << Color::CYAN << Color::BOLD << "╔═════════════════════════════╗" << Color::RESET << std::endl;
            std::cout << Color::CYAN << Color::BOLD << "║    Ticket Booking System    ║" << Color::RESET << std::endl;
            std::cout << Color::CYAN << Color::BOLD << "╚═════════════════════════════╝" << Color::RESET << std::endl;
            
            std::cout << Color::BLUE << " 1. " << Color::RESET << "Book a seat" << std::endl;
            std::cout << Color::BLUE << " 2. " << Color::RESET << "Cancel a reservation" << std::endl;
            std::cout << Color::BLUE << " 3. " << Color::RESET << "View available seats" << std::endl;
            std::cout << Color::BLUE << " 4. " << Color::RESET << "View all seat statuses" << std::endl;
            std::cout << Color::BLUE << " 5. " << Color::RESET << "Mark seat as broken" << std::endl;
            std::cout << Color::BLUE << " 6. " << Color::RESET << "Repair broken seat" << std::endl;
            std::cout << Color::BLUE << " 7. " << Color::RESET << "Exit" << std::endl;
            
            std::cout << Color::CYAN << "\nEnter your choice (1-7): " << Color::RESET;
        }

        // Function to get user choice with updated validation
        MenuOptions getUserChoice() {
            int choice;
            std::cin >> choice;
            
            // Input validation
            while (std::cin.fail() || choice < 1 || choice > 7) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << Color::RED << "Invalid choice. Please enter a number between 1 and 7: " << Color::RESET;
                std::cin >> choice;
            }
            
            return static_cast<MenuOptions>(choice - 1);
        }

        // Function to display available seats in a grid format with improved visuals
        void displaySeatsGrid(const std::vector<Seat>& seats) {
            std::cout << "\n" << Color::CYAN << Color::BOLD << "╔═════════════════════════════╗" << Color::RESET << std::endl;
            std::cout << Color::CYAN << Color::BOLD << "║          Seat Status        ║" << Color::RESET << std::endl;
            std::cout << Color::CYAN << Color::BOLD << "╚═════════════════════════════╝" << Color::RESET << std::endl;
            
            std::cout << Color::GREEN << "Available" << Color::RESET << " | " 
                      << Color::YELLOW << "Reserved" << Color::RESET << " | " 
                      << Color::RED << "Broken" << Color::RESET << "\n\n";
            
            int columns = 5; // Display 5 seats per row
            for (int i = 0; i < seats.size(); i++) {
                if (i > 0 && i % columns == 0) {
                    std::cout << std::endl;
                }
                
                std::string color;
                
                switch (seats[i].getStatus()) {
                    case SeatStatus::Available:
                        color = Color::GREEN;
                        break;
                    case SeatStatus::Reserved:
                        color = Color::YELLOW;
                        break;
                    case SeatStatus::Broken:
                        color = Color::RED;
                        break;
                }
                
                // Add padding for single-digit numbers
                std::string padding = (i + 1 < 10) ? " " : "";
                std::cout << color << "[" << padding << (i + 1) << "]" << Color::RESET << " ";
            }
            std::cout << std::endl;
        }
    }

    // Filtering and sorting namespace
    namespace Fil {
        // Lambda function to filter available seats
        auto filterAvailable = [](const Seat& seat) { return seat.getStatus() == SeatStatus::Available; };
        
        // Lambda function to sort seats by number
        auto sortByNumber = [](const Seat& a, const Seat& b) { return a.getNumber() < b.getNumber(); };
        
        // Function to display seats based on a filter
        void displayFilteredSeats(const std::vector<Seat>& seats, 
                                 std::function<bool(const Seat&)> filter) {
            bool found = false;
            for (const auto& seat : seats) {
                if (filter(seat)) {
                    std::cout << seat << std::endl;
                    found = true;
                }
            }
            
            if (!found) {
                std::cout << "No seats match the criteria." << std::endl;
            }
        }
    }
}

int main() {
    // Initialize 20 seats
    std::vector<Seat> seats;
    for (int i = 1; i <= 20; ++i) {
        seats.emplace_back(i);
    }
    
    // Set a few seats as broken for testing
    seats[4].setStatus(SeatStatus::Broken);
    seats[12].setStatus(SeatStatus::Broken);
    
    bool running = true;
    
    while (running) {
        TicketingSystem::UI::displayMenu();
        MenuOptions choice = TicketingSystem::UI::getUserChoice();
        
        int seatNumber;
        
        switch (choice) {
            case MenuOptions::BookSeat:
                // Display seats grid before booking
                TicketingSystem::UI::displaySeatsGrid(seats);
                std::cout << Color::CYAN << "Enter seat number to book: " << Color::RESET;
                std::cin >> seatNumber;
                TicketingSystem::Booking::bookSeat(seats, seatNumber);
                break;
                
            case MenuOptions::CancelReservation:
                // Display seats grid before cancellation
                TicketingSystem::UI::displaySeatsGrid(seats);
                std::cout << Color::CYAN << "Enter seat number to cancel reservation: " << Color::RESET;
                std::cin >> seatNumber;
                TicketingSystem::Booking::cancelReservation(seats, seatNumber);
                break;
                
            case MenuOptions::ViewAvailableSeats:
                // Display only the grid view
                TicketingSystem::UI::displaySeatsGrid(seats);
                break;
                
            case MenuOptions::ViewAllSeatStatus:
                // Display only the grid view
                TicketingSystem::UI::displaySeatsGrid(seats);
                break;
                
            case MenuOptions::MarkBroken:
                // Display seats grid before marking as broken
                TicketingSystem::UI::displaySeatsGrid(seats);
                std::cout << Color::CYAN << "Enter seat number to mark as broken: " << Color::RESET;
                std::cin >> seatNumber;
                TicketingSystem::Booking::markSeatAsBroken(seats, seatNumber);
                break;
                
            case MenuOptions::RepairSeat:
                // Display seats grid before repairing
                TicketingSystem::UI::displaySeatsGrid(seats);
                std::cout << Color::CYAN << "Enter seat number to repair: " << Color::RESET;
                std::cin >> seatNumber;
                TicketingSystem::Booking::repairSeat(seats, seatNumber);
                break;
                
            case MenuOptions::Exit:
                std::cout << Color::GREEN << "Thank you for using the Ticket Booking System. Goodbye!\n" << Color::RESET;
                running = false;
                break;
        }
    }
    
    return 0;
}