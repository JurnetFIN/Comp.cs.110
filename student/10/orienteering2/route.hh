#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <memory>

using namespace std;

struct Point {
    string name;
    int x;
    int y;
    int height;
    char marker;
};

class Route
{
public:
    // Constructor that initializes the attribute cycle_.
    // (The other attibutes are initialized in the private part below.)
    Route();

    // Destructor
    ~Route();

    void connect_route(shared_ptr<Point>, shared_ptr<Point>);

    void print_route();

private:
    // A single route, i.e. list of points
    struct RoutePoints {
        shared_ptr<Point>  data;
        shared_ptr<RoutePoints> next;
    };

    // Pointer to the first marker in the route
    shared_ptr<RoutePoints> first_ = nullptr;
};

#endif // ROUTE_H
