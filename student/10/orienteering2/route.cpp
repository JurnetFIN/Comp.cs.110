#include "route.hh"
#include <iostream>
#include <memory>

Route::Route() {
}

Route::~Route() {
}

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
