#include "route.hh"
#include <iostream>
#include <memory>
#include <cmath>
#include <iomanip>

Route::Route() {
}

Route::~Route() {
}

/**
 * Connecting points to create route
 * @param from; mista_rastisra
 * @param to; mihin_rastiin
 */
void Route::connect_route(shared_ptr<Point> from, shared_ptr<Point> to) {
    // Adding new route if it not exist already
    if (first_ == nullptr) {
        shared_ptr<RoutePoints> new_origin(new RoutePoints{from, nullptr});

        first_ = new_origin;
    }

    shared_ptr<RoutePoints> point_ptr = first_;

    // Adding another point to route end
    while (point_ptr->next != nullptr) {
        point_ptr = point_ptr->next;
    }

    // Adding new point to route
    shared_ptr<RoutePoints> new_destination(new RoutePoints{to, nullptr});

    point_ptr->next = new_destination;
}

/**
 * Printing points in given route
 */
void Route::print_route() {
    if (first_ != nullptr) {
        // Searching for first point
        shared_ptr<RoutePoints> point_ptr = first_;

        // Printing first point
        cout << point_ptr->data->name << std::endl;
        point_ptr = point_ptr->next;

        // Printing rest points
        while(point_ptr != nullptr) {
            cout << " -> " << point_ptr->data->name << std::endl;
            point_ptr = point_ptr->next;
        }
    }
}

/**
 * Counting route length
 * @param name
 */
void Route::route_length(string name) {
    // Searching for first point
    shared_ptr<RoutePoints> point_ptr = first_;
    double pituus = 0;

    int from_x = point_ptr->data->x;
    int from_y = point_ptr->data->y;

    // Counting route length
    while(point_ptr->next != nullptr) {
        int to_x = point_ptr->next->data->x;
        int to_y = point_ptr->next->data->y;

        // Counting length between two points with help of equation
        pituus += sqrt(pow(from_x-to_x, 2)+pow(from_y-to_y, 2));

        from_x = to_x;
        from_y = to_y;
        point_ptr = point_ptr->next;
    }

    // Printing length of route
    cout << setprecision(2) << "Route " << name <<" length was " << pituus << endl;
}

/**
 * Checking if point is on given route
 * Return true if there is, otherwise false
 * @param point_name
 * @return bool
 */
bool Route::contains(string point_name) {
    // Searching for first point on route
    shared_ptr<RoutePoints> point_ptr = first_;

    // Cheching if given point exist
    while(point_ptr != nullptr) {
        if(point_ptr->data->name == point_name) {
            return true;
        }
        point_ptr = point_ptr->next;
    }
    return false;
}

/**
 * Counting max rise
 * @param point_name
 * @return suurin_nousu
 */
int Route::max_rise(string point_name) {
    // Searching for first point on route
    shared_ptr<RoutePoints> point_ptr = first_;

    // Searching point from we want to count rise
    while(point_ptr != nullptr) {
        if(point_ptr->data->name == point_name)
            break;
        point_ptr = point_ptr->next;
    }

    int rise = 0;
    int start_height = point_ptr->data->height;

    // Counting rise as long as there isn't descent
    while(point_ptr->next != nullptr){
        // If there is start of descent -> break
        if(point_ptr->next->data->height < point_ptr->data->height)
            break;

        // Counting rise
        rise = point_ptr->next->data->height - start_height;
        point_ptr = point_ptr->next;
    }

    return rise;
}
