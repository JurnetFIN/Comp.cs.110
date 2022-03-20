#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle): first_(nullptr), last_(nullptr) {
    cycle_ = cycle;
}

Queue::~Queue() {
    while ( first_ != nullptr ) {
        Vehicle* car_to_be_released = first_;
        first_ = first_->next;

        delete car_to_be_released;
    }
}

void Queue::enqueue(string const& reg) {
    if (is_green_) {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        return;
    }

    Vehicle* new_car = new Vehicle{reg, nullptr};

    if ( first_ == nullptr ) {
       first_ = new_car;
       last_ = new_car;
    } else {
       last_->next = new_car;
       last_ = new_car;
    }
}

void Queue::switch_light() {
    if (first_ == nullptr ) {
        is_green_ = !is_green_;
        if (is_green_ == true) {
            cout << "GREEN: No vehicles waiting in traffic lights";
        } else {
            cout << "RED: No vehicles waiting in traffic lights";
        }
        cout << endl;

    } else {
        cout << "GREEN: Vehicle(s) ";
        for(unsigned int cycle_nro = 0; cycle_nro < cycle_; ++cycle_nro) {
            if (first_ == nullptr ) {
                cout << "can go on" << endl;
                return;
            }

            Vehicle* car_to_be_removed = first_;

            string& removed_car = car_to_be_removed->reg_num;
            cout << removed_car << " ";

            if ( first_ == last_ ) {
                first_ = nullptr;
                last_ = nullptr;
            } else {
                first_ = first_->next;
            }

            delete car_to_be_removed;
        }
        cout << "can go on" << endl;
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() const {
    if (first_ == nullptr ) {
        if (is_green_ == true) {
            cout << "GREEN: No vehicles waiting in traffic lights";
        } else {
            cout << "RED: No vehicles waiting in traffic lights";
        }
        cout << endl;
        return;
    }

    cout << "RED: Vehicle(s) ";
    Vehicle* item_to_be_printed = first_;
    while ( item_to_be_printed != nullptr ) {
       cout << item_to_be_printed->reg_num << " ";
       item_to_be_printed = item_to_be_printed->next;
    }
    cout << "waiting in traffic lights" << endl;
}
