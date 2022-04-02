/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# Student: Juliusz Kotelba // 150586775                                     #
# File: route                                                               #
# Description: Luokka jossa on tallennetut reitit                           #
#              ja sen pisteet jarjestyksessa                                #
#############################################################################
*/

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
    // Constructor
    Route();

    // Destructor
    ~Route();

    // Yhdistetaan reitin rastit
    void connect_route(shared_ptr<Point>, shared_ptr<Point>);

    // Tulostetaan reitin rastit
    void print_route();

    // Lasketaan reitin pituus
    void route_length(string);

    // Tarkistetaan onko piste reitilla
    bool contains(string);

    // Lasketaan suurin nousu
    int max_rise(string);

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
