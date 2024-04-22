#include <string>
#include <cmath>

using namespace std;




// Define a class to represent a 2D vector
class Vector2D {
public:
    Vector2D(double startX, double startY, double endX, double endY)
        : startX(startX), startY(startY), endX(endX), endY(endY) {}

    double getStartX() const { return startX; }
    double getStartY() const { return startY; }
    double getEndX() const { return endX; }
    double getEndY() const { return endY; }

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
