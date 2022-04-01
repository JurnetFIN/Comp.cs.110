#include "route.hh"
#include <iostream>
#include <memory>
#include <cmath>
#include <iomanip>

Route::Route() {
}

Route::~Route() {
}

// Yhdistetaan reitin rastit
void Route::connect_route(shared_ptr<Point> from, shared_ptr<Point> to) {
    if (first_ == nullptr) {
        shared_ptr<RoutePoints> new_origin(new RoutePoints{from, nullptr});

        first_ = new_origin;
    }

    shared_ptr<RoutePoints> new_destination(new RoutePoints{to, nullptr});

    shared_ptr<RoutePoints> point_ptr = first_;

    while (point_ptr->next != nullptr) {
        point_ptr = point_ptr->next;
    }

    point_ptr->next = new_destination;
}
// Tulostetaan reitin rastit
void Route::print_route() {
    if (first_ != nullptr) {
        shared_ptr<RoutePoints> point_ptr = first_;

        cout << point_ptr->data->name << std::endl;
        point_ptr = point_ptr->next;

        while(point_ptr != nullptr) {
            cout << " -> " << point_ptr->data->name << std::endl;
            point_ptr = point_ptr->next;
        }
    }
}

// Lasketaan reitin pituus
void Route::route_length(string name) {
    // Haetaan ensimmainen piste
    shared_ptr<RoutePoints> point_ptr = first_;
    double pituus = 0;

    int from_x = point_ptr->data->x;
    int from_y = point_ptr->data->y;

    // Kaydaan lapi jokainen piste
    while(point_ptr->next != nullptr) {
        int to_x = point_ptr->next->data->x;
        int to_y = point_ptr->next->data->y;

        pituus += sqrt(pow(from_x-to_x, 2)+pow(from_y-to_y, 2));

        from_x = to_x;
        from_y = to_y;
        point_ptr = point_ptr->next;
    }

    // Tulostetaan reitin pituus
    cout << setprecision(2) << "Route " << name <<" length was " << pituus << endl;
}
