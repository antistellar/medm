#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

int fCombatant, sCombatant, fRank, sRank, choice, gamesPlayed = 0, gamesWon = 0, gamesLost = 0, characterWins[20] = {0},
characterLosses[20] = {0}, betFor[20] = {0}, betAgainst[20] = {0};

float wallet = 1000, bet, creditsWon = 0, creditsLost = 0, totalBets = 0;

string fChar, sChar, choiceName;

const string namesList[20] = {"ashley williams", "kaidan alenko", "liara t'soni", "garrus vakarian", "urdnot wrex",
"tali'zorah", "commander shepard", "miranda lawson", "jacob taylor", "zaeed massani", "mordin solus",
"urdnot grunt", "jack", "kasumi goto", "thane krios", "samara", "legion", "james vega", "edi", "javik"};

void generateCombatants(), enterBet(), enterChoice(), getUserInput(), printResults(), playGame(), printStats();

string getMargin(int, int);

int main()
{
    srand(time(0));

    cout << "M A S S  E F F E C T  D E A T H M A T C H !" << endl << endl << "THE FIRST MATCH IS:" << endl;

    playGame();

    cout << endl << "thanks for playing!" << endl;

    int poop;
    cin >> poop;

    return 0;
}

void generateCombatants()
{
    const int rankList[20] = {/*ashley*/ 1, /*kaidan*/ 3, /*liara*/ 4, /*garrus*/ 6, /*wrex*/ 6, /*tali*/ 3,
    /*shep*/ 7, /*miranda*/ 3, /*jacob*/ 2, /*zaeed*/ 4, /*mordin*/ 5, /*grunt*/ 5, /*jack*/ 5, /*kasumi*/ 4,
    /*thane*/ 5, /*samara*/ 6, /*legion*/ 6, /*vega*/ 1, /*edi*/ 3, /*javik*/ 5};

    do
    {
        fCombatant = (rand() % 20);
        sCombatant = (rand() % 20);
    }while (fCombatant == sCombatant);

    fChar = namesList[fCombatant];
    sChar = namesList[sCombatant];

    do
    {
        fRank = rankList[fCombatant] + (rand() % 9);
        sRank = rankList[sCombatant] + (rand() % 9);
    }while (fRank == sRank);
}

string getMargin(int fRank, int sRank)
{
    int margin;

    const string margin6 = " destroys ", margin5 = " easily handles ", margin4 = " has little trouble with ",
    margin3 = " defeats ", margin2 = " emerges victorious after a tough battle with ", margin1 = " just barely wins against ";

    if (fRank > sRank)
    {
        margin = fRank - sRank;
    }
    else
    {
        margin = sRank - fRank;
    }

    switch (margin)
    {
        case 1:
            return margin1;
        case 2:
        case 3:
            return margin2;
        case 4:
        case 5:
            return margin3;
        case 6:
        case 7:
            return margin4;
        case 8:
        case 9:
            return margin5;
        default:
            return margin6;
    }
}

void enterBet()
{
    string input = "";
    for(;;)
    {
        cout << "you have " << wallet << " credits in the bank." << endl << "place your bet: ";
        getline(cin, input);
        stringstream myStream(input);
        if (myStream >> bet)
        {
            if (bet <= 0)
            {
                cout << endl << "*** bet more than zero. ***" << endl << endl;
            }
            else if(bet > wallet)
            {
                cout << endl << "*** you don't have that much. ***" << endl << endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << endl << "*** enter a number. ***" << endl << endl;
        }
    }

    totalBets += bet;
}

void enterChoice()
{
    string input = "";
    for(;;)
    {
        cout << endl << "who will you bet on?\n\n(1) " << fChar << endl << "(2) " << sChar << endl;
        getline(cin, input);
        stringstream myStream(input);
        if (myStream >> choice)
        {
            if (choice == 1 || choice == 2)
            {
                break;
            }
            else
            {
                cout << endl << "*** enter 1 or 2. ***" << endl;
            }
        }
        else
        {
            cout << endl <<  "*** enter 1 or 2. ***" << endl;
        }
    }

    if (choice == 1)
    {
        choiceName = fChar;
        betFor[fCombatant]++;
        betAgainst[sCombatant]++;
    }
    else
    {
        choiceName = sChar;
        betFor[sCombatant]++;
        betAgainst[fCombatant]++;
    }
}

void getUserInput()
{
    int w = 2;

    while (w == 2)
    {
        cout << endl << fChar << " vs. " << sChar << endl << endl;

        enterBet();
        enterChoice();

        string input = "";
        for(;;)
        {
            cout << endl << "bet " << bet << " credits on " << choiceName << "?\n(1) yes\n(2) no" << endl;

            getline(cin, input);
            stringstream myStream(input);
            if (myStream >> w)
            {
                if (w == 1 || w == 2)
                {
                    if(w == 2)
                    {
                        totalBets -= bet;

                        if (choice == 1)
                        {
                            betFor[fCombatant]--;
                            betAgainst[sCombatant]--;
                        }
                        else
                        {
                            betFor[sCombatant]--;
                            betAgainst[fCombatant]--;
                        }
                    }

                    break;
                }
                else
                {
                    cout << endl << "*** enter 1 or 2. ***" << endl;
                }
            }
            else
            {
                cout << endl << "*** enter 1 or 2. ***" << endl;
            }
        }
    }
}

void printResults()
{
    int winner;

    cout << endl << "RESULTS:" << endl << endl;

    if (fRank > sRank)
    {
        winner = 1;
        cout << fChar << getMargin(fRank, sRank) << sChar << "." << endl << endl;
        characterWins[fCombatant]++;
        characterLosses[sCombatant]++;
    }
    else
    {
        winner = 2;
        cout << sChar << getMargin(fRank, sRank) << fChar << "." << endl << endl;
        characterWins[sCombatant]++;
        characterLosses[fCombatant]++;
    }

    if (choice == winner)
    {
        wallet = wallet + bet;
        cout << "you win!" << endl;
        gamesWon++;
        creditsWon += bet;
    }
    else
    {
        wallet = wallet - bet;
        cout << "you lose." << endl;
        gamesLost++;
        creditsLost += bet;
    }

    cout << "you now have " << wallet << " credits in the bank." << endl;
}

void playGame()
{
    int z = 1;

    while(z != 2)
    {
        gamesPlayed++;
        generateCombatants();
        getUserInput();
        printResults();

        if (wallet == 0)
        {
            cout << endl << "you have run out of credits. better luck next time." << endl;

            string input = "";
            for(;;)
            {
                int a;

                cout << endl << "see final stats?\n(1) yes\n(2) no" << endl;
                getline(cin, input);

                // This code converts from string to number safely.
                stringstream myStream(input);
                if (myStream >> a)
                {
                    if(a == 1)
                    {
                        printStats();
                        break;
                    }
                    else if (a == 2)
                    {
                        break;
                    }
                    else
                    {
                        cout << endl << "*** enter 1 or 2. ***" << endl;
                    }
                }
                else
                {
                    cout << endl << "*** enter 1 or 2. ***" << endl;
                }
            }

            break;
        }
        else
        {
            string input = "";
            for(;;)
            {
                cout << endl << "play again?\n(1) yes\n(2) no" << endl;
                getline(cin, input);
                stringstream myStream(input);
                if (myStream >> z)
                {
                    if (z == 1 || z == 2)
                    {
                        if (z == 1)
                        {
                            cout << endl << "THE NEXT MATCH IS:" << endl;
                            break;
                        }
                        else
                        {
                            int a;

                            string input2 = "";
                            for(;;)
                            {
                                cout << endl << "see final stats?\n(1) yes\n(2) no" << endl;
                                getline(cin, input2);
                                stringstream myStream2(input2);
                                if (myStream2 >> a)
                                {
                                    if(a == 1)
                                    {
                                        printStats();
                                        break;
                                    }
                                    else if (a == 2)
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        cout << endl << "*** enter 1 or 2. ***" << endl;
                                    }
                                }
                                else
                                {
                                    cout << endl << "*** enter 1 or 2. ***" << endl;
                                }
                            }

                            break;
                        }
                    }
                    else
                    {
                        cout << endl << "*** enter 1 or 2. ***" << endl;
                    }
                }
                else
                {
                    cout << endl << "*** enter 1 or 2. ***" << endl;
                }
            }
        }
    }
}

void printStats()
{
    int mostWins = 0, mostLosses = 0, mostPicks = 0, mostPicksAgainst = 0;

    vector<string> mostWinChars(0), mostLossChars(0), mostPickChars(0), mostPickAgainstChars(0);

    for(int x = 0; x < 20; x++)
    {
        if(mostWins < characterWins[x])
        {
            mostWins = characterWins[x];
        }

        if(mostLosses < characterLosses[x])
        {
            mostLosses = characterLosses[x];
        }

        if(mostPicks < betFor[x])
        {
            mostPicks = betFor[x];
        }

        if(mostPicksAgainst < betAgainst[x])
        {
            mostPicksAgainst = betAgainst[x];
        }
    }

    for(int x = 0; x < 20; x++)
    {
        if(mostWins == characterWins[x])
        {
            mostWinChars.push_back(namesList[x]);
        }

        if(mostLosses == characterLosses[x])
        {
            mostLossChars.push_back(namesList[x]);
        }

        if(mostPicks == betFor[x])
        {
            mostPickChars.push_back(namesList[x]);
        }

        if(mostPicksAgainst == betAgainst[x])
        {
            mostPickAgainstChars.push_back(namesList[x]);
        }
    }

    cout << endl << "final bank total: " << wallet << endl;
    cout << "number of matches you bet on: " << gamesPlayed << endl;
    cout << "amount of credits you bet: " << totalBets << endl;
    cout << "amount of credits you won: " << creditsWon << endl;
    cout << "amount of credits you lost: " << creditsLost << endl;
    cout << "your average bet: " << totalBets/gamesPlayed << endl;
    cout << "number of matches you bet correctly on: " << gamesWon << endl;
    cout << "number of matches you bet incorrectly on: " << gamesLost << endl;
    cout << "character";

    if (mostWinChars.size() != 1)
    {
        cout << "s";
    }

    cout << " who won the most matches (" << mostWins << "): ";

    for (unsigned int x = 0; x < mostWinChars.size(); x++)
    {
        if(x > 0)
        {
            cout << ", ";
        }

        cout << mostWinChars[x];
    }

    cout << endl << "character";

    if (mostLossChars.size() != 1)
    {
        cout << "s";
    }

    cout << " who lost the most matches (" << mostLosses << "): ";

    for (unsigned int x = 0; x < mostLossChars.size(); x++)
    {
        if(x > 0)
        {
            cout << ", ";
        }

        cout << mostLossChars[x];
    }

    cout << endl << "character";

    if (mostPickChars.size() != 1)
    {
        cout << "s";
    }

    cout << " who you bet on the most (" << mostPicks << "): ";

    for (unsigned int x = 0; x < mostPickChars.size(); x++)
    {
        if(x > 0)
        {
            cout << ", ";
        }

        cout << mostPickChars[x];
    }

    cout << endl << "character";

    if (mostPickAgainstChars.size() != 1)
    {
        cout << "s";
    }

    cout << " who you bet against the most (" << mostPicksAgainst << "): ";

    for (unsigned int x = 0; x < mostPickAgainstChars.size(); x++)
    {
        if(x > 0)
        {
            cout << ", ";
        }

        cout << mostPickAgainstChars[x];
    }

    cout << endl;
}
