#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>

class Player {
  public:
    Player(std::string const& nimi);
    std::string get_name() const;
    int get_points() const;
    void add_points(int pts);
    bool has_won() const;

  private:
    std::string nimi_;
    int points_;

};

#endif // PLAYER_HH
