#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <vector>
using namespace std;

const vector<string> RANKS {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

// const int STARTING_CASH = 5000;

const string SPADES = "\u2660",
           CLUBS = "\u2663",
           HEARTS = "\u2665",
           DIAMONDS = "\u2666";

const vector<string> SUITS = {SPADES, HEARTS, DIAMONDS, CLUBS};

vector<string> getDeck();
// void shuffleDeck(vector<string>&);
int makeBet(int);
void showRules();
void displayHands(vector<string>, vector<string>, bool);
int getHandValue(vector<string>);
char getMove(vector<string>, int);
void displayCards(vector<string>);

int main() 
{
    vector<string> deck;
    int cash = 5000;
    showRules();

    // while (cash > 0)
    // {
        char move;
        int play = 1;
        char cashOut = 'n';

        // cout << deck.size();

    while ((cash > 0) && (cashOut = tolower('n')))
    {
        // Let player make their bet for this round:
        cout << "Money: " << cash << endl;
        int bet = makeBet(cash);
        cout << "Bet: " << bet << endl;
        
        deck = getDeck();
        
        // Give player and dealer their cards:
        vector<string> playerHand;
        vector<string> dealerHand;

        // Remove the cards in the hand from the deck
        playerHand.push_back(deck.back());
        deck.pop_back();
        playerHand.push_back(deck.back());
        deck.pop_back();

        dealerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();

        // Display player and dealer hands:
        displayHands(playerHand, dealerHand, false);

        move = getMove(playerHand, cash);
        
        // int yourValue = getHandValue(playerHand);
        // int dealerValue = getHandValue(dealerHand);
        // cout << "Your points: " << yourValue << endl;
        // cout << "Dealer points: " << yourValue << endl;
    }


    // }
    // cout << "2 " << HEARTS << " J " << SPADES << " A " << CLUBS << " 5 " << DIAMONDS << '\n';

    // for (int card = 0; card < deck.size(); card++)
    // {
    //     cout << card + 1 << ": " << deck[card] << endl;
    // }   

    // int size = deck.size();
    // cout << deck.size() << endl;

    return 0;
}

vector<string> getDeck()
{
    
    vector<string> deck;

    // vector<string> deck;
    for (const auto &suit : SUITS)
    {   
        for (const auto &rank : RANKS)
        {
            deck.push_back(rank + suit);
        }
    }

    random_device rd;
    mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);

    return deck;
}

int makeBet(int cash)
{
    int playerBet;
    cout << "How much do you bet? (1-5000): ";
    cin >> playerBet;

    while (playerBet > cash)
    {
        cout << "Cannot bet more cash than you have!\n"
                "How much do you bet?(1-5000): ";
                cin >> playerBet;
    }

    while (playerBet > 5000)
    {
        cout << "Maximum bet is 5000. \n"
                "How much do you bet?(1-5000): ";
                cin >> playerBet;
    }

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

// Displays player's and dealer's cards. Hide the dealer's first card if showDealerHand is false.
void displayHands(vector<string> playerHand, vector<string> dealerHand, bool showDealerHand)
{
    int yourValue = getHandValue(playerHand);
    int dealerValue = getHandValue(dealerHand);
    
    if (showDealerHand == false)
    {
        cout << "DEALER: ??? " 
             << "\n** HIDDEN ** " << "\t" << dealerHand[1] << endl;
        
        cout << "PLAYER: " << yourValue 
             << "\n" << playerHand[0] << "\t" << playerHand[1] << endl;
    }
    else
    {
        cout << "Dealer's hand: " << dealerValue  
             << dealerHand[0] << " || " << dealerHand[1] << endl;

        cout << "Your hand: " << yourValue 
             << playerHand[0] << " || " << playerHand[1] << endl;
    }
}

int getHandValue(vector<string> hand)
{
    int position = 0;
    string card = hand[position];
    int handValue = 0;

    for (auto card : hand)
    {
        if (!card.empty())
        {
            char rank = card[0];

            if (rank == 'A')
            {
                if (handValue > 10)
                {
                    handValue += 1;
                }
                else 
                {
                    handValue += 11;
                }
            }
            else if (rank == 'K' || rank == 'Q' || rank == 'J')
            {
                handValue+= 10;
            }
            else
            {
                handValue += rank - '0';
            }
        }
    }

    return handValue;
}

char getMove(vector<string> playerHand, int cash)
{
    char playerMove;

    if (playerHand.size() == 2 && cash > 0)
    {
        cout << "(H)it, (S)tand, or (D)ouble Down: ";
        cin >> playerMove;

        while (tolower(playerMove) != 'h' && 
               tolower(playerMove) != 's' && 
               tolower(playerMove) != 'd'  )
        {
            cout << "Invalid entry. (H)it, (S)tand, or (D)ouble Down: ";
            cin >> playerMove;
        }
    }
    else if (playerHand.size() > 2)
    {
        cout << "(H)it or (S)tand: ";
        cin >> playerMove;
                
        while (tolower(playerMove) != 'h' && 
               tolower(playerMove) != 's'  )
        {
            cout << "Invalid entry. (H)it or (S)tand:";
            cin >> playerMove;
        }
    }
    return playerMove;
}

// void displayCards(vector<string> card)
// {
    
// }

// char *card = """
//  ___ 
// |2  |
// |   |
// |__2|
  
// """;

//  ___   ___
// |## | |2  |
// |###| | ♥ |
// |_##| |__2|
