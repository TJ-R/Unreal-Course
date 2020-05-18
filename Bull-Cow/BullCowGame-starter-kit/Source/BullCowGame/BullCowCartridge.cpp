// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame(); //Setting up the game

    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);

    //Welcome the player
    PrintLine(TEXT("Hi, welcome to the Bull Cows game."));
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess and"));
    PrintLine(TEXT("press enter to continue......"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    //Check the player guess
    if(Input == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
        //Exit the game
    }
    else
    {
        if(HiddenWord.Len() != Input.Len())
        {
            PrintLine(TEXT("The Hidden Word is %i characters long,"), HiddenWord.Len());
            PrintLine(TEXT("Please guess again......"));
        }
        else
        {
            PrintLine(TEXT("You lose."));
        }
    }
    // Check If Isogram
    // Prompt to guess again.

    // Remove a life

    //Check If life is >0

    //If yes prompt for new guess
    //Show lives left

    //If no print GameOver and show the hidden word
    //Prompt user to play again, press enter
    //Check user input
    //PlayAgain or Quit
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("about");
    Lives = HiddenWord.Len();
}