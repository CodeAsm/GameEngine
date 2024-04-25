#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <cmath>
#include <imgui.h>

using namespace std;

// Define a class to represent a 2D vector
class Segment2D {
public:
    // Constructor
    Segment2D(double startX, double startY, double endX, double endY, wstring Name )
        : startX(startX), startY(startY), endX(endX), endY(endY), Name(Name) {}

    // Function to set the angle of the vector
    void setAngle(double angle);

    // Function to get the angle of the vector
    double getAngle() const;

    // Function to get the starting point of the vector
    ImVec2 getStartPoint(int x, int y) const;

    // Function to get the ending point of the vector
    ImVec2 getEndPoint(int x, int y) const;

    // Function to get the length of the vector
    double length() const;

    // Function to set the name of the vector
    void setName(const std::wstring& newName);

    // Function to get the name of the vector
    wstring getName() const;

private:
    double startX;
    double startY;
    double endX;
    double endY;
    wstring Name;  // name (string variable)
};

#endif // SEGMENT_H
