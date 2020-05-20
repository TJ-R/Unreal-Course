// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "FileHelper.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    TArray<FString> Words;
    const FString WordsPath = FPaths::ProjectContentDir()/TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordsPath);

    Isograms = GetValidWords(Words);

    SetupGame(); //Setting up the game
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    //Welcome the player
    PrintLine(TEXT("Hi, welcome to the Bull Cows game."));
    PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives to guess the word."), Lives);
    PrintLine(TEXT("Type in your guess and"));
    PrintLine(TEXT("press enter to continue......"));
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); //Debug Line
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again......"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    //Check the player guess
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("\nYou win!"));
        EndGame();
        return;
    }
    else
    {

        if(HiddenWord.Len() != Guess.Len())
        {
            PrintLine(TEXT("\nThe Hidden Word is %i characters long"), HiddenWord.Len());
            PrintLine(TEXT("You have %i lives remaining."), Lives);
            PrintLine(TEXT("Guess again......"));
            return;
        }
        else if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("\nGuess is not an isogram."));
            PrintLine(TEXT("You have %i lives remaining."), Lives);
            PrintLine(TEXT("Guess again......"));
            return;
        }
        else
        {
            PrintLine(TEXT("\nYou have lost a life."));
            --Lives;

            if(Lives <= 0)
            {
                ClearScreen();
                PrintLine(TEXT("\nYou lose. You have no lives left!"));
                PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
                EndGame();
                return;
            }

            //Show the player the bulls and cows
            FBullCowCount Score = GetBullCows(Guess);

            PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);

            PrintLine(TEXT("You have %i lives remaining."), Lives);
        }   
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    //Loop through the character array for the Guess and check
    //each of the characters against each other. 
    //Return True if all are different
    //Return False if two characters match

    for(int32 Index = 0; Index < Word.Len() - 1; Index++)
    {
        for(int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison]) 
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWordsList;

    for(FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <= 8
            && IsIsogram(Word))
        {
            ValidWordsList.Emplace(Word);
        }
    }

    return ValidWordsList;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}