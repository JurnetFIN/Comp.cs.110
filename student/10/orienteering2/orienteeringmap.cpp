#include "orienteeringmap.hh"
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using namespace std;

OrienteeringMap::OrienteeringMap() {
}

OrienteeringMap::~OrienteeringMap() {
}

// Sets the width and height for the map.
void OrienteeringMap::set_map_size(int width, int height) {
    width_ = width;
    height_ = height;
};

// Adds a new point in the map, with the given name, position (x and y
// coordinates), height and marker.
void OrienteeringMap::add_point(string name, int x, int y, int height, char marker) {

    if ((x < 0) or (x > width_))
        return;

    if ((y < 0) or (y > height_))
        return;

    // Lisataan rasti mapille, jos se ei ole olemassa
    if (points_.find(marker) == points_.end()) {
        shared_ptr<Point> new_point(new Point{name, x, y, height, marker});

        points_.insert(std::pair<char, shared_ptr<Point>>(marker, new_point));
    }
};

// Connects two existing points such that the point 'to' will be
// immediately after the point 'from' in the route 'route_name'.
// The given route can be either a new or an existing one,
// if it already exists, the connection between points will be
// updated in the aforementioned way.
// Returns true, if connection was successful, i.e. if both the points
// exist, otherwise returns false.
bool OrienteeringMap::connect_route(string from,
                   string to,
                   string route_name) {

    // Haetaan muuttujat
    shared_ptr<Point> from_ptr = nullptr;
    shared_ptr<Point> to_ptr = nullptr;

    // Tarkistetaan onko molemmat rastit olemassa
    for(auto& p: points_) {
        if (p.second->name == from)
            from_ptr = p.second;

        if (p.second->name == to)
            to_ptr = p.second;
    }

    // Jos jompikumpi ei ole olemassa -> Virhe
    if ((from_ptr == nullptr) or (to_ptr == nullptr))
        return false;

    // Lisataan reitti
    if (routes_.find(route_name) == routes_.end()) {
        shared_ptr<Route> new_route(new Route());
        routes_.insert(pair<string, shared_ptr<Route>>(route_name, new_route));
    }

    routes_.at(route_name)->connect_route(from_ptr, to_ptr);

    return true;
}

// Prints the map.
void OrienteeringMap::print_map() const {
    // Muodostetaan "kartta", jossa on vain pisteita
    vector<vector<char>> points;
    for(int x=1; x <=width_; x++) {
        vector<char> chars;
        for(int y=1; y <=height_; y++) {
            chars.push_back('.');
        }
        points.push_back(chars);
    }

    // Korvataan pisteet rasteilla
    for(auto& p: points_)
        points.at((p.second->x)-1).at((p.second->y)-1) = p.second->marker;

    // Tulostetaan kartta
    // Ensin tulostetaan ylapalkki
    cout << " ";
    string prefix = "  ";
    for(int x=1; x <=width_; x++) {
        if(x>=10)
            prefix = " ";
        cout << prefix << x;
    }
    cout << endl;

    // Sen jalkeen tulostetaan rivi kerrallaan
    for(int y=1; y <= height_; y++) {
        if(y>=10)
            prefix = "";
        cout << prefix << y;

        for(int x=1; x <= width_; x++) {
            cout << "  " << points[x-1][y-1];
        }
        cout << endl;
    }
};

// Prints all routes' names, ordered alphabetically.
void OrienteeringMap::print_routes() const {
    cout << "Routes:" << endl;
    for (auto& r: routes_) {
        cout << " - " << r.first << endl;
    }
};

// Prints all points' names and their markers on the map.
void OrienteeringMap::print_points() const {
    cout << "Points:" << endl;
    for (auto& p: points_) {
        cout << " - " << p.second->name << " : " << p.first << endl;
    }
};

// Prints points belonging to the given route in the order they are
// in the route.
void OrienteeringMap::print_route(const std::string& name) const {

    if (routes_.find(name) == routes_.end()) {
        // Error
        cout << "Error: Route named " << name << " can't be found" << endl;
        return;
    }

    routes_.at(name)->print_route();
};

// Prints the given route's combined length,
// the length is counted as a sum of the distances of adjacent points.
void OrienteeringMap::route_length(const std::string& name) const {
    if (routes_.find(name) == routes_.end()) {
        // Error
        cout << "Error: Route named " << name << " can't be found" << endl;
        return;
    }
    routes_.at(name)->route_length(name);
};

// Finds and prints the highest rise in any of the routes after the given
// point.
void OrienteeringMap::greatest_rise(const std::string& point_name) const {
    cout << point_name << endl;
};
