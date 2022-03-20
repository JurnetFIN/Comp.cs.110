#include "cards.hh"
#include <iostream>

Cards::Cards(): top_(nullptr), bottom_(nullptr) {
}

Cards::~Cards() {
    while ( top_ != nullptr ) {
        Card_data* item_to_be_released = top_;
        top_ = top_->next;

        delete item_to_be_released;
    }
}

void Cards::add(int id) {
    Card_data* new_item = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_item;
        bottom_ = new_item;
    } else {
        top_->next = new_item;
        top_ = new_item;
    }
}

bool Cards::remove(int& removed_id) {
    if (top_ == nullptr ) {
        return false;
    }

    Card_data* item_to_be_removed = top_;

    removed_id = item_to_be_removed->data;

    if (top_ == bottom_) {
        top_ = nullptr;
        bottom_ = nullptr;
    } else {
        top_ = top_->next;
    }

    delete item_to_be_removed;

    return true;
}
/*
void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* item_to_be_printed = top_;
    int running_number = 1;

    for(unsigned int i = 0; i < 6; ++i) {
        std::cout << running_number << ": " << item_to_be_printed->data << std::endl;
        ++running_number;
        print_from_top_to_bottom(item_to_be_printed->next);
    }
}
*/
