// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the bull cows game!"));
    PrintLine(TEXT("Enter your input and press ENTER:"));
    HiddenWord = TEXT("punks");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if(HiddenWord == Input){
        PrintLine("That's right u punks!");
    }
    else{
        PrintLine("Nah, wrong answer");
    }
}