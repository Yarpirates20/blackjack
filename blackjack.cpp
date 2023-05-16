#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <vector>
using namespace std;

const vector<string> RANKS {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const vector<string> SUITS = {"Spades", "Hearts", "Diamonds", "Clubs"};
const int STARTING_CASH = 5000;

const string SPADES = "\u2660",
           CLUBS = "\u2663",
           HEARTS = "\u2665",
           DIAMONDS = "\u2666";

vector<string> deck;

void getDeck(vector<string>&);
// void shuffleDeck(vector<string>&);
int makeBet();
void showRules();
void displayHands();
int getHandValue();
char getMove();




int main() 
{
    int cash = STARTING_CASH;
    showRules();

    while (cash > 0)
    {
        cout << "Money: " << STARTING_CASH << endl;
        getDeck(deck);

        cout << deck.size();

        int bet = makeBet();
        cout << "Bet: " << bet << endl;
    }
    // cout << "2 " << HEARTS << " J " << SPADES << " A " << CLUBS << " 5 " << DIAMONDS << '\n';
    // getDeck(deck);
    // shuffleDeck(deck);
    // for (int card = 0; card < deck.size(); card++)
    // {
    //     cout << card + 1 << ": " << deck[card] << endl;
    // }   

    // int size = deck.size();
    // cout << size << endl;

    return 0;
}

void getDeck(vector<string> &deck)
{
    // vector<string> deck;
    for (const auto &suit : SUITS)
    {   
        for (const auto &rank : RANKS)
        {
            deck.push_back(rank + " of " + suit);
        }
    }

    random_device rd;
    mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
}

// void shuffleDeck(vector<string> &deck)
// {
//     random_device rd;
//     mt19937 rng(rd());
//     std::shuffle(deck.begin(), deck.end(), rng);
// }

int makeBet()
{
    int playerBet;
    cout << "How much do you bet? (1-5000): ";
    cin >> playerBet;

    return playerBet;
}

void showRules()
{
    cout << "\tRules:\n";

    cout << "\t\tTry to get as close to 21 wihout going over. \n"
            "\t\tKings, Queens, and Jacks are worth 10 points. \n"
            "\t\tAces are worth 1 or 11 points. \n"
            "\t\tCards 2 through 10 are worth their face value. \n"
            "\t\t(H)it to take another card. \n"
            "\t\t(S)tand to stop taking cards. \n"
            "\t\tOn your first play, you can (D)ouble down to increase your bet \n"
            "\t\tbut must hit exactly one more time before standing. \n"
            "\t\tIn case of a tie, the bet is returned to the player. \n"
            "\t\tThe dealer stops hitting at 17. \n";
}
