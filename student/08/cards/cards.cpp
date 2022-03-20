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
        bottom_->next = new_item;
        bottom_ = new_item;
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

void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* to_be_printed = top_;
    int nr = 1;

    while( to_be_printed != 0 ) {
       s << nr << ": " << to_be_printed->data << std::endl;
       to_be_printed = to_be_printed->next;
       ++nr;
    }
}

void Cards::print_from_bottom_to_top(std::ostream& s) {
    Card_data* to_be_printed = bottom_;
    int nr = 1;

    while(to_be_printed != 0 ) {
        s << nr << ": " << to_be_printed->data << std::endl;
        to_be_printed = to_be_printed->next;
        ++nr;
    }
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr ) {
        return false;
    }

    Card_data* item_to_be_removed = bottom_;

    int& removed_id = item_to_be_removed->data;

    Card_data* new_item = new Card_data{removed_id, nullptr};

    // Remove
    if (top_ == bottom_) {
        top_ = nullptr;
        bottom_ = nullptr;
    } else {
        bottom_ = nullptr;
    }

    delete item_to_be_removed;

    // Add
    if (top_ == nullptr) {
        top_ = new_item;
        bottom_ = new_item;
    } else {
        top_->next = new_item;
        top_ = new_item;
    }

    return true;
}

bool Cards::bottom_to_top() {
    if (top_ == nullptr ) {
        return false;
    }
    Card_data* item_to_be_removed = bottom_;

    int& removed_id = item_to_be_removed->data;

    Card_data* new_item = new Card_data{removed_id, nullptr};

    // Remove
    if (top_ == bottom_) {
        top_ = nullptr;
        bottom_ = nullptr;
    } else {
        bottom_ = nullptr;
    }

    delete item_to_be_removed;

    // Add
    if (top_ == nullptr) {
        top_ = new_item;
        bottom_ = new_item;
    } else {
        top_->next = new_item;
        top_ = new_item;
    }

    return true;
}
