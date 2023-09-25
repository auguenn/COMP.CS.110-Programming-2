#include "player.hh"

Player::Player(const std::string& name):
    name_(name), points_(0), win_(false){
}

std::string Player::get_name()
{
    return name_;
}

void Player::add_points(int point)
{
    points_ += point;
        if (points_ > 50) {
            points_ = 25;
            std::cout << name_ << " gets penalty points!" << std::endl;
        }
}


int Player::get_points()
{
    return points_;
}

bool Player::has_won() {
    if (points_ == 50) {
        return true;
    } else {
        return false;
    }
}
