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

Card_data* Cards::get_topmost() {
    return top_;
}

void Cards::add(int id) {
    Card_data* new_item = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_item;
    } else {
        new_item->next = top_;
        top_ = new_item;
    }
}

bool Cards::remove(int& removed_id) {
    if (top_ == nullptr ) {
        return false;
    }

    Card_data* item_to_be_removed = top_;

    removed_id = item_to_be_removed->data;

    top_ = top_->next;

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

int Cards::recursive_print(Card_data* top, std::ostream& s, int i=0) {
    if (top->next == nullptr) {
        std::cout << 1 << ": " << top->data << std::endl;
        return 1;
    }
    i = recursive_print(top->next, s, i);
    ++i;
    std::cout << i << ": " << top->data << std::endl;
    return i;
}

/*
   if (num < 10) {
        cout << num << endl;
        return;
    }
    print_vertical(num / 10);
    cout << num % 10 << endl;
*/

void Cards::print_from_bottom_to_top(std::ostream& s) {
    Card_data* to_be_printed = top_;
    recursive_print(to_be_printed, s);
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr ) {
        return false;
    }

    Card_data* item_ptr = top_;

    while (item_ptr->next != 0) {
        item_ptr = item_ptr->next;
    }

    item_ptr->next = top_;

    item_ptr = top_->next;

    top_->next = nullptr;

    top_ = item_ptr;

    return true;
}

bool Cards::bottom_to_top() {
    if (top_ == nullptr ) {
        return false;
    }

    Card_data* item_ptr = top_;

    while (item_ptr->next != 0) {
        item_ptr = item_ptr->next;
    }
    item_ptr->next = top_;

    top_ = item_ptr;

    while (item_ptr->next != top_) {
        item_ptr = item_ptr->next;
    }

    item_ptr->next = nullptr;

    return true;
}
