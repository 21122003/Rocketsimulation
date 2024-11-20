#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <graphics.h>
using std::cin;
using std::cout;
using std::string;
using namespace std;

class Rocket {
private:
    string rocketName;
    double payloadMass, secondStageFuelMass, firstStageFuelMass;
    double legsMass, engineMass, fairingsMass, gridFinsMass;

public:
    Rocket(string name, double payload, double secondStageFuel, double firstStageFuel,
           double legs, double engine, double fairings, double gridFins)
        : rocketName(name), payloadMass(payload), secondStageFuelMass(secondStageFuel),
          firstStageFuelMass(firstStageFuel), legsMass(legs), engineMass(engine),
          fairingsMass(fairings), gridFinsMass(gridFins) {}

    string getName() const { return rocketName; }
    double getTotalMass() const {
        return payloadMass + secondStageFuelMass + firstStageFuelMass +
               legsMass + engineMass + fairingsMass + gridFinsMass;
    }

    void display() const {
        cout << "Rocket Name: " << rocketName << endl;
        cout << "Payload Mass: " << payloadMass << " kg" << endl;
        cout << "Second Stage Fuel Mass: " << secondStageFuelMass << " kg" << endl;
        cout << "First Stage Fuel Mass: " << firstStageFuelMass << " kg" << endl;
        cout << "Legs Mass: " << legsMass << " kg" << endl;
        cout << "Engine Mass: " << engineMass << " kg" << endl;
        cout << "Fairings Mass: " << fairingsMass << " kg" << endl;
        cout << "Grid Fins Mass: " << gridFinsMass << " kg" << endl;
    }
};

class RocketManager {
private:
    vector<Rocket> rockets;

    void loadFromFile() {
        ifstream file("rocket_data.txt");
        string name;
        double payload, secondStageFuel, firstStageFuel, legs, engine, fairings, gridFins;
        while (file >> name >> payload >> secondStageFuel >> firstStageFuel >> legs >> engine >> fairings >> gridFins) {
            rockets.emplace_back(name, payload, secondStageFuel, firstStageFuel, legs, engine, fairings, gridFins);
        }
        file.close();
    }

    void saveToFile(const Rocket& rocket) {
        ofstream file("rocket_data.txt", ios::app);
        if (file.is_open()) {
            file << rocket.getName() << " " << rocket.getTotalMass() << endl;
            file.close();
        }
    }

public:
    RocketManager() {
        loadFromFile();
    }

    void createRocket() {
        string name;
        double payload, secondStageFuel, firstStageFuel, legs, engine, fairings, gridFins;

        cout << "Enter rocket name: ";
        cin >> name;
        cout << "Enter payload mass: ";
        cin >> payload;
        cout << "Enter second stage fuel mass: ";
        cin >> secondStageFuel;
        cout << "Enter first stage fuel mass: ";
        cin >> firstStageFuel;
        cout << "Enter legs mass: ";
        cin >> legs;
        cout << "Enter engine mass: ";
        cin >> engine;
        cout << "Enter fairings mass: ";
        cin >> fairings;
        cout << "Enter grid fins mass: ";
        cin >> gridFins;

        Rocket rocket(name, payload, secondStageFuel, firstStageFuel, legs, engine, fairings, gridFins);
        rockets.push_back(rocket);
        saveToFile(rocket);

        cout << "Rocket created successfully!\n";
    }

    Rocket* findRocket(const string& name) {
        for (auto& rocket : rockets) {
            if (rocket.getName() == name)
                return &rocket;
        }
        return nullptr;
    }

    void displayRocket(const string& name) {
        Rocket* rocket = findRocket(name);
        if (rocket) {
            rocket->display();
        } else {
            cout << "Rocket not found.\n";
        }
    }
};

class Simulation {
public:
    void runSimulation(int fuel) {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, (char*)"");

        for (int i = 1; i <= fuel; i++) {
            // Draw ground
            line(50, 450, 550, 450);  // ground second
            line(50, 10, 550, 10);    // top boundary

            // Scale line
            line(80, 450, 80, -10010);

            // Rocket body (parallel lines)
            line(250, 400 + 450 - i, 250, 250 + 450 - i);
            line(300, 400 + 450 - i, 300, 250 + 450 - i);
            line(250, 250 + 450 - i, 300, 250 + 450 - i);
            line(300, 250 + 450 - i, 275, 200 + 450 - i);
            line(250, 250 + 450 - i, 275, 200 + 450 - i);
            line(250, 400 + 450 - i, 300, 400 + 450 - i);
            line(275, 400 + 450 - i, 250, 450 + 450 - i);
            line(275, 400 + 450 - i, 300, 450 + 450 - i);

            // Height display
            int number = i * 10;
            stringstream strs;
            strs << number;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();
            outtextxy(90, 420, char_type);

            delay(2);  // Delay for animation
            cleardevice();  // Clear screen

            if (i == 600) {
                // Re-draw the rocket at height 600
                line(50, 450, 550, 450);  // ground second
                line(50, 10, 550, 10);
                line(80, 450, 80, -10010);
                line(250, 400 + 450 - i, 250, 250 + 450 - i);
                line(300, 400 + 450 - i, 300, 250 + 450 - i);
                line(250, 250 + 450 - i, 300, 250 + 450 - i);
                line(300, 250 + 450 - i, 275, 200 + 450 - i);
                line(250, 250 + 450 - i, 275, 200 + 450 - i);
                line(250, 400 + 450 - i, 300, 400 + 450 - i);
                line(275, 400 + 450 - i, 250, 450 + 450 - i);
                line(275, 400 + 450 - i, 300, 450 + 450 - i);
            }

            if (i == fuel) {
                closegraph();  // Close graph when fuel limit is reached
                fndisplay(fuel);  // Show final display (implement this function)
                getch();
            }
        }
    }
     void fndisplay(int fuel) {
    // Final display function to show fuel status
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Display final fuel status and other relevant information
    stringstream finalMessage;
    finalMessage << "Rocket reached maximum height with " << fuel << " units of fuel remaining.";

    // Convert std::string to a char array
    char msg[256]; // Make sure the size is sufficient for your message
    strcpy(msg, finalMessage.str().c_str());

    // Use outtextxy with integer coordinates and the final message
    outtextxy(50, 200, msg);

    delay(5000);  // Keep the final message displayed for a while
    closegraph();  // Close the graphics window
}



};

class MainMenu {
private:
    RocketManager rocketManager;
    Simulation simulation;

public:
    void showMenu() {
        int choice;
        do {
            cout << "1. Create New Rocket\n";
            cout << "2. Display Rocket\n";
            cout << "3. Simulate Rocket Launch\n";
            cout << "4. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    rocketManager.createRocket();
                    break;
                case 2: {
                    string name;
                    cout << "Enter rocket name: ";
                    cin >> name;
                    rocketManager.displayRocket(name);
                    break;
                }
                case 3: {
                    int fuel;
                    cout << "Enter fuel (in liters): ";
                    cin >> fuel;
                    simulation.runSimulation(fuel);
                    break;
                }
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    MainMenu menu;
    menu.showMenu();
    return 0;
}
