// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hi, welcome to the Bull Cows game."));

    HiddenWord = TEXT("about");

    PrintLine(TEXT("Guess the five letter word.")); //Change hard coded word length!!!
    PrintLine(TEXT("Press enter to continue......"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    if(Input == HiddenWord)
    {
        PrintLine(TEXT("You guessed the hidden word correctly."));
        PrintLine(TEXT("You win!"));
    }
    else
    {
        PrintLine(TEXT("You guessed the hidden word incorrectly."));
        PrintLine(TEXT("You lose."));
    }
}