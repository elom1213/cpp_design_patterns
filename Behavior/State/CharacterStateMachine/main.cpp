#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

enum class State{
  Stop, 
  MeetMonster, 
  AttackedByMonster, 
  DestroyMonster, 
  Dead, 
  Quit
};

enum class Trigger{
  MoveFront,
  Attack,
  Ignore,
  Runaway,
  Restart,
  QuitGame
};

ostream& operator<<(ostream& os, const State& s)
{
  switch(s)
  {
  case State::Stop:
    cout << "is stopped\n";
    break;
  case State::MeetMonster:
    cout << "meets a monster\n";
    break;
  case State::AttackedByMonster:
    cout << "is attacked by monster\n";
    break;
  case State::DestroyMonster:
    cout << "just destroyed a monster\n";
    break;
  case State::Dead:
    cout << "is dead\n";
    break;
  case State::Quit:
    cout << "quit the game\n";
    break;
  }
  return os;
}

ostream& operator<<(ostream& os, const Trigger& t)
{
  switch(t)
  {
  case Trigger::MoveFront:
    cout << "moves character\n";
    break;
  case Trigger::Attack:
    cout << "attacks monster\n";
    break;
  case Trigger::Ignore:
    cout << "ignores everything whatever happens\n";
    break;
  case Trigger::Runaway:
    cout << "runaway from current state\n";
    break;
  case Trigger::Restart:
    cout << "restart the game\n";
    break;
  case Trigger::QuitGame:
    cout << "quit the game\n";
    break;
  default:
    break;
  }
  return os;
}

using Transition = pair<Trigger, State>;
using Transitions = vector<Transition>;

int main() 
{
  map<State, Transitions> rules;

  rules[State::Stop] = {{Trigger::MoveFront, State::MeetMonster},
                        {Trigger::QuitGame, State::Quit}};
  rules[State::MeetMonster] = {{Trigger::Attack, State::DestroyMonster},
                               {Trigger::Ignore, State::AttackedByMonster}};
  rules[State::AttackedByMonster] = {{Trigger::Attack, State::DestroyMonster},
                                     {Trigger::Ignore, State::Dead},
                                     {Trigger::Runaway, State::Stop}};
  rules[State::Dead] = {{Trigger::Restart, State::Stop},
                        {Trigger::QuitGame, State::Quit}};
  rules[State::DestroyMonster] = {{Trigger::MoveFront, State::MeetMonster},
                                  {Trigger::QuitGame, State::Quit}};

  State currentState{State::Stop};
  State exitState{State::Quit};

  while(true)
  {
    cout << "\nCharacter " << currentState;
  select_trigger:

    // Display available states:
    size_t n = rules[currentState].size();
    for(int i = 1; i <= n; ++i)
      cout << i << ". " << rules[currentState][i-1].first;

    // Read selected action
    cout << "select number => ";
    size_t input;
    cin >> input;

    // handle errors
    if(input > n || input <= 0) 
    {
      cout << "incorrect option. please try again\n";
      goto select_trigger; 
    }

    // Update state based on the transition.
    currentState  = rules[currentState][input-1].second;
    if(currentState == exitState) break;
  }
  cout << "\nyou quit the game.\n";
  exit(0);
}