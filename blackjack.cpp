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
int makeBet(int, int);
void showRules();
void displayHands(vector<string>, vector<string>, bool);
int getHandValue(vector<string>);
char getMove(vector<string>, int);
void displayCards(vector<string>);

int main() 
{
    vector<string> deck;
    int cash = 5000;
    char move;
    // int play = 1;
    char cashOut = 'n';

    showRules();

    while ((cash > 0) && (tolower(cashOut) == 'n'))
    {
        // Let player make their bet for this round:
        cout << "Money: " << cash << endl;
        int bet = makeBet(cash, cash);

        // while (bet > cash)
        // {
        //     cout << "Cannot bet more than you have!\n";
        //     bet = makeBet(cash);
        // }
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
        // cin.ignore();
        // Loop until player stands or busts
        char move = 'a';
        
        while (getHandValue(playerHand) <= 21 && tolower(move) != 's')
        { 
            displayHands(playerHand, dealerHand, false);
            
            move = getMove(playerHand, cash - bet);
            
            // Check if player busts
            if (getHandValue(playerHand) > 21)
            {
                cout << "Over 21 -- Player Busts\n";
                // Break out of current while loop to continue
                break;
            }
            
            // Get player move -- H, S, or D
            

            // if (tolower(move) == 'd')
            //     {
            //         // Player can increase bet if doubling down
            //         int additionalBet = makeBet(std::min(bet, (cash - bet)), cash);
            //         bet += additionalBet;
            //         cout << "\nBet is increased to " << bet << ". \n";
            //         cout << "Bet: " << bet << endl; 
            //     }

            if (tolower(move) == 'h' || tolower(move) == 'd')
                {
                    if (tolower(move) == 'd')
                    {
                        // Player can increase bet if doubling down
                        int additionalBet = makeBet(std::min(bet, (cash - bet)), cash);
                        bet += additionalBet;
                        cout << "\nBet is increased to " << bet << ". \n";
                        cout << "Bet: " << bet << endl; 
                    }

                    string newCard = (deck.back());
                    deck.pop_back();
                    cout << "You drew: " << newCard << endl;
                    playerHand.push_back(newCard);

                    if (getHandValue(playerHand) > 21)
                    {
                        cout << "Over 21 -- Player Busts\n";
                        // Break out of current while loop to continue
                        continue;
                    }
                }

            if (tolower(move) == 's' || tolower(move) == 'd')
                {
                    break;
                }
        }

        // Dealers actions
        if (getHandValue(playerHand) <= 21)
        {
            while (getHandValue(dealerHand) < 17)
            {
                // Dealer hits
                cout << "Dealer hits...\n";
                dealerHand.push_back(deck.back());
                deck.pop_back();

                displayHands(playerHand, dealerHand, false);

                if (getHandValue(dealerHand) > 21)
                {
                    break;  // Dealer busts
                }
            }
        }

        // Show final hands:
        displayHands(playerHand, dealerHand, true);
        
        int playerValue = getHandValue(playerHand);
        int dealerValue = getHandValue(dealerHand);

        // Lost, won, or tied
        if (dealerValue > 21)
        {
            cout << "Dealer busts! You won " << bet << "!\n";
            cash += bet;
        } 
        else if (playerValue > 21 || playerValue < dealerValue)
        {
            cout << "You lost!\n";
            cash -= bet;
        }
        else if (playerValue > dealerValue)
        {
            cout << "You won " << bet << "!\n";
            cash += bet;
        }
        else if (playerValue == dealerValue)
        {
            cout << "It's a tie, the bet is returned to you.\n";
        }

        cout << "Would you like to cash out and finish? (Y/N): ";
        cin >> cashOut;
        // cin.ignore();

        if (tolower(cashOut) == 'y')
        {
            cout << "Cash: " << cash << endl;
            cout << "Goodbye!\n";
        }
        // cout << "Your points: " << yourValue << endl;
        // cout << "Dealer points: " << yourValue << endl;
    }

    return 0;
    // cout << "2 " << HEARTS << " J " << SPADES << " A " << CLUBS << " 5 " << DIAMONDS << '\n'
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

int makeBet(int maxBet, int cash)
{
    int playerBet;
    cout << "How much do you bet? (Maximum additional bet: " << maxBet << "): ";
    cin >> playerBet;

    while (playerBet > maxBet || playerBet > cash)
    {
        cout << "Cannot bet more cash than you have!\n"
                "Enter bet: ";
                cin >> playerBet;
    }

    while (playerBet < 1)
    {
        cout << "Must bet a minimum of 1. \n";
        cout << "Enter bet: ";
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
        cout << "\nDEALER: ??? \n";

        for (int count = 0; count < dealerHand.size(); count++)
        {
            if (count == 0)
            {
                cout << "*** HIDDEN ***" << "\t";
            }
            else
            {
                cout << dealerHand[count] << "\t";
            }
        }

        //      << "\n** HIDDEN ** " << "\t" << dealerHand[1] << endl;
        
        cout << endl;

        cout << "\nPLAYER: " << yourValue << endl;

        cout << "Your hand: " << yourValue << endl;
        for (auto card : playerHand)
        {
            cout << card << "\t";
        }

        cout << endl;

            //  << "\n" << playerHand[0] << "\t" << playerHand[1] << endl;
    }
    else
    {
        cout << "\nDealer's hand: " << dealerValue << endl; 
        
        for (auto card : dealerHand)
        {
            cout << card << "\t";
        }

        cout << endl;

        cout << "\nYour hand: " << yourValue << endl;
        for (auto card : playerHand)
        {
            cout << card << "\t";
        }

        cout << endl;
            //  << playerHand[0] << "\t" << playerHand[1] << endl;
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
                if (handValue + 11 <= 21)
                {
                    handValue += 11;
                }
                else 
                {
                    handValue += 1;
                }
            }
            else if (rank == 'K' || rank == 'Q' || rank == 'J')
            {
                handValue+= 10;
            }
            else if (card == "10")
            {
                handValue += 10;
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
        cout << "\n(H)it, (S)tand, or (D)ouble Down: ";
        cin >> playerMove;

        while (tolower(playerMove) != 'h' && 
               tolower(playerMove) != 's' && 
               tolower(playerMove) != 'd'  )
        {
            cout << "\nInvalid entry. (H)it, (S)tand, or (D)ouble Down: ";
            cin >> playerMove;
        }
    }
    else if (playerHand.size() > 2 || cash < 1)
    {
        cout << "\n(H)it or (S)tand: ";
        cin >> playerMove;
                
        while (tolower(playerMove) != 'h' && 
               tolower(playerMove) != 's'  )
        {
            cout << "\nInvalid entry. (H)it or (S)tand:";
            cin >> playerMove;
        }
    }
    return playerMove;
}
