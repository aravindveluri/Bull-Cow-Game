// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
void UBullCowCartridge::InitGame(){
    HiddenWord = TEXT("punks");
    Lives = 4;
}
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the bull cows game!"));
    PrintLine(TEXT("Guess the 5 letter word you punk"));
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if(Input.Len() != HiddenWord.Len()){
        PrintLine(FString::Printf(TEXT("Guess should be of length %i") , (HiddenWord.Len())));
    }
    else if(HiddenWord == Input){
        PrintLine(TEXT("That's right u punks!"));
    }
    else{
        PrintLine(TEXT("Nah, wrong answer"));
    }
}