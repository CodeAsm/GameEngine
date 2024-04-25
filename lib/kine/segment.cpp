#include <string>
#include <cmath>
#include <imgui.h>
#include "segment.hpp"

using namespace std;





    void Segment2D::setAngle(double angle) {         // Calculate the new end point coordinates based on the given angle
        double length = this->length(); // Get the length of the vector
        endX = startX + length * cos(angle * M_PI / 180); // Calculate new endX
        endY = startY + length * sin(angle * M_PI / 180); // Calculate new endY
        return; }
    double Segment2D::getAngle() const{ 
        return atan2(endY - startY, endX - startX) * 180 / M_PI; 
        }
    /*double getStartX() const { return startX; }
    double getStartY() const { return startY; }
    double getEndX() const { return endX; }
    double getEndY() const { return endY; } */
    ImVec2 Segment2D::getStartPoint(int x, int y) const {return ImVec2(startX+(x/2), -(startY)+y); }
    ImVec2 Segment2D::getEndPoint(int x, int y) const {return ImVec2(endX+(x/2), -(endY)+y); }

    double Segment2D::length() const {
        double dx = endX - startX;
        double dy = endY - startY;
        return sqrt(dx * dx + dy * dy);
    }

    // Function to set the name of the vector from a wide string
    void Segment2D::setName(const std::wstring& newName) {
        Name = newName;
    }

    // Function to get the name of the vector
    
    wstring Segment2D::getName() const{
        return Name;
    }
