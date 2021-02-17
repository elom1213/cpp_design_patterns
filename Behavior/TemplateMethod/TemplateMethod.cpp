#include <iostream>

using namespace std;

// general algorithm for a game
class Game
{
protected:
  int number_of_player, current_player{0};
  virtual void start() = 0;
  virtual bool have_winner() = 0;
  virtual void take_turn() = 0;
  virtual int get_winner() = 0;

public:
   explicit Game(int num) : number_of_player{num} {}

  // general implementation
  // run() just calls other methods
  void run()
  {
    start();
    while(!have_winner())
      take_turn();
    cout << "Player " << get_winner() << " wins\n";
  }
};

// particular implementation for a chess game
struct Chess : public Game
{
  explicit Chess() : Game{2} {}
protected:
  void start() override 
  {
    cout << "starting a Chess game with " 
         << number_of_player << "players\n";
  }
  bool have_winner() override {return turns == max_turns;}
  void take_turn() override 
  {
    cout << "player " << current_player 
         << " just takes turn " << turns << '\n';
    ++turns;
    ++current_player %= number_of_player;
  }
  int get_winner() override { return current_player;}

private:
  int turns{0}, max_turns{10};
};

int main() {
  Chess chess;
  chess.run();
  return 0;  
}