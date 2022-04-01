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
 * Yhdistetaan reitin rastit
 * @param from; mista_rastisra
 * @param to; mihin_rastiin
 */
void Route::connect_route(shared_ptr<Point> from, shared_ptr<Point> to) {
    // Lisataan reitti, jos sita ei ole olemassa
    if (first_ == nullptr) {
        shared_ptr<RoutePoints> new_origin(new RoutePoints{from, nullptr});

        first_ = new_origin;
    }

    // Lisataan uusi rasti reitille
    shared_ptr<RoutePoints> new_destination(new RoutePoints{to, nullptr});

    shared_ptr<RoutePoints> point_ptr = first_;

    // Lisataan rasti reitin loppuun
    while (point_ptr->next != nullptr) {
        point_ptr = point_ptr->next;
    }

    point_ptr->next = new_destination;
}

/**
 * Tulostetaan reitin rastit
 */
void Route::print_route() {
    if (first_ != nullptr) {
        // Haetaan ensimmainen rasti
        shared_ptr<RoutePoints> point_ptr = first_;

        // Tulosteetaan ensimmainen rasti
        cout << point_ptr->data->name << std::endl;
        point_ptr = point_ptr->next;

        // Tulostetaan muut rastit
        while(point_ptr != nullptr) {
            cout << " -> " << point_ptr->data->name << std::endl;
            point_ptr = point_ptr->next;
        }
    }
}

/**
 * Lasketaan reitin pituus
 * @param name
 */
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

        // Lasketaan kaavan avulla kahden rastin etaisyys
        pituus += sqrt(pow(from_x-to_x, 2)+pow(from_y-to_y, 2));

        from_x = to_x;
        from_y = to_y;
        point_ptr = point_ptr->next;
    }

    // Tulostetaan reitin pituus
    cout << setprecision(2) << "Route " << name <<" length was " << pituus << endl;
}

/**
 * Tutkitaan onko piste olemassa reitilla
 * Palauttaa true, jos on, muulloin false
 * @param point_name
 * @return bool
 */
bool Route::contains(string point_name) {
    // Haetaan ensimmainen piste
    shared_ptr<RoutePoints> point_ptr = first_;

    // Tutkitaan onko piste olemassa
    while(point_ptr != nullptr) {
        if(point_ptr->data->name == point_name) {
            return true;
        }
        point_ptr = point_ptr->next;
    }
    return false;
}

/**
 * Lasketaan suurin nousu
 * @param point_name
 * @return suurin_nousu
 */
int Route::max_rise(string point_name) {
    // Haetaan ensimmainen piste
    shared_ptr<RoutePoints> point_ptr = first_;

    // Haetaan rasti, josta aletaan laskea nousu
    while(point_ptr != nullptr) {
        if(point_ptr->data->name == point_name)
            break;
        point_ptr = point_ptr->next;
    }

    int rise = 0;
    int start_height = point_ptr->data->height;

    // Suoritaan silmukka niin kauan kunnes aletaan laskea alas
    while(point_ptr != nullptr) {
        rise = point_ptr->data->height - start_height;

        // Tapaus missa reitin korkein piste on myos reitin virhe
        if(point_ptr->next == nullptr)
            break;

        // Jos aletaan menemaan alaspain lopetetaan silmukka
        if(point_ptr->next->data->height < point_ptr->data->height)
            break;

        point_ptr = point_ptr->next;
    }

    return rise;
}
