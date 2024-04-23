#include <string>
#include <cmath>
#include <imgui.h>

using namespace std;




// Define a class to represent a 2D vector
class Vector2D {
public:
    Vector2D(double startX, double startY, double endX, double endY)
        : startX(startX), startY(startY), endX(endX), endY(endY) {}

    void setAngle(double angle) {         // Calculate the new end point coordinates based on the given angle
        double length = this->length(); // Get the length of the vector
        endX = startX + length * cos(angle * M_PI / 180); // Calculate new endX
        endY = startY + length * sin(angle * M_PI / 180); // Calculate new endY
        return; }
    double getAngle() const{ return atan2(endY - startY, endX - startX) * 180 / M_PI; }
    /*double getStartX() const { return startX; }
    double getStartY() const { return startY; }
    double getEndX() const { return endX; }
    double getEndY() const { return endY; } */
    ImVec2 getp1(int x, int y) const {return ImVec2(startX+(x/2), -(startY)+y); }
    ImVec2 getp2(int x, int y) const {return ImVec2(endX+(x/2), -(endY)+y); }

    double length() const {
        double dx = endX - startX;
        double dy = endY - startY;
        return sqrt(dx * dx + dy * dy);
    }

    wstring Name;  // name (string variable)

private:
    double startX;
    double startY;
    double endX;
    double endY;
};
