#include <player.hh>
#include <iostream>

Player::Player(std::string const& nimi):
    nimi_(nimi), points_(0)  {
}

std::string Player::get_name() const {
    return nimi_;
}

int Player::get_points() const {
    return points_;
}

void Player::add_points(int pts) {
    points_ += pts;
    if (points_ > 50) {
        std::cout << get_name() << " gets penalty points!" << std::endl;
        points_ = 25;
    }
}

bool Player::has_won() const {
    if (points_ == 50) {
        return true;
    } else {
        return false;
    }
}
