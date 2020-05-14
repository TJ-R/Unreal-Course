#include <iostream>
#include <ctime>

void PrintIntroduction(int Difficulty)
{
    //Set up the story for TripleX via intro messages
    std::cout << "\n\nYou are the world's best spy sneaking into level " << Difficulty; 
    std::cout << " of a top secret facility to disarm the rocket...\n";
    std::cout << "Enter the correct codes to continue down to the lowest level where the rocket is stored...\n\n";
}

bool PlayGame(int Difficulty)
{
    PrintIntroduction(Difficulty);

    //declare the 3 number code
    const int CodeA = rand() % Difficulty + Difficulty;
    const int CodeB = rand() % Difficulty + Difficulty;
    const int CodeC = rand() % Difficulty + Difficulty;

    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;
    
    //print the CodeSum and CodeProduct to the terminal
    std::cout << "+ There are three numbers in the code";
    std::cout << "\n+ The codes add-up to: " << CodeSum;
    std::cout << "\n+ The codes multiply to give: " << CodeProduct << std::endl;

    //Store player guess
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    //Check if the players guess is correct
    if (CodeSum == GuessSum && CodeProduct == GuessProduct)
    {
        std::cout << "\n*** You did it! You got pass this floor, move onto the next...";
        return true;
    }
    else
    {
        std::cout << "\n*** You failed to get pass this floor, try again.";
        return false;
    }
}

int main()
{
    srand(time(NULL)); // create new random sequence based on time of day
    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;

    while (LevelDifficulty <= MaxDifficulty) //Loops the game till all levels are complete
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();   //clears any errors
        std::cin.ignore();  //discards the current buffer

        if (bLevelComplete)
        {
            ++LevelDifficulty;
        }
    }

    std::cout << "\n*** That was the final level great job! ";
    std::cout << "*** You were able to get the rocket and defuse it before it was launched!";

    return 0;
}