// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
void UBullCowCartridge::InitGame(){
    HiddenWord = TEXT("lol");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to the bull cows game!"));
    PrintLine(TEXT("Guess the %i letter word. You have %i lives"), HiddenWord.Len(), Lives);
}
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver){
        ClearScreen();
        InitGame();
    }
    else{
        if(Input.Len() != HiddenWord.Len()){
            PrintLine(FString::Printf(TEXT("Guess should be of length %i") , (HiddenWord.Len())));
        }
        else if(HiddenWord == Input){
            PrintLine(TEXT("That's right u punks!"));
            EndGame();
        }
        else{
            if(Lives > 0){
                PrintLine(TEXT("Wrong asnwer, you have %i lives left."), --Lives);
            }
            else{
                PrintLine(TEXT("You Lost!"));
                EndGame();
            }
        }
    }    
}
void UBullCowCartridge::EndGame(){
    //We're in the endgame now lol
    bGameOver = true;
    PrintLine(TEXT("Game Over! Press Enter to continue..."));
}