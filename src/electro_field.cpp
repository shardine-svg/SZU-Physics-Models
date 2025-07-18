#include <iostream>
#include <cmath>
using namespace std;

struct Vector2D { double x, y; };

Vector2D electricField(double q, Vector2D pos, Vector2D point) {
    double dx = point.x - pos.x, dy = point.y - pos.y;
    double dist = sqrt(dx*dx + dy*dy);
    if(dist < 1e-5) return {0,0};
    double k = 9e9, mag = k*q/(dist*dist);
    return { mag*dx/dist, mag*dy/dist };
}

int main() {
    Vector2D E = electricField(1e-9, {0,0}, {0.1,0});
    cout << "电场强度: (" << E.x << ", " << E.y << ") V/m";
    return 0;
}