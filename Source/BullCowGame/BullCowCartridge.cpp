// Fill out your copyright notice in the Description page of Project Settings.
#include "HiddenWordsList.h"
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay(){
    Super::BeginPlay();
    InitGame();
}
void UBullCowCartridge::InitGame(){
    TArray<FString> FilteredWords = GetValidWords(Words);
    HiddenWord = FilteredWords[FMath::RandRange(0, FilteredWords.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to the bull cows game!"));
    PrintLine(TEXT("Guess the %i letter word. You have %i lives"), HiddenWord.Len(), Lives);
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const{
    TArray<FString> ValidWords;
    for(FString Word: WordList){
        if(UBullCowCartridge::IsIsogram(Word) && Word.Len() >= 4 && Word.Len() <= 8){
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}
void UBullCowCartridge::OnInput(const FString& Input){
 // When the player hits enter
    if(bGameOver){
        ClearScreen();
        InitGame();
    }
    else{
        ProcessGuess(Input);
    }    
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    if(Guess.Len() != HiddenWord.Len()){
        PrintLine(FString::Printf(TEXT("Guess should be of length %i") , (HiddenWord.Len())));
        return;
    }
    if(!IsIsogram(Guess)){
        PrintLine(TEXT("No repeating letters. Guess again\n"));
    }

    else if(HiddenWord == Guess){
        ClearScreen();
        PrintLine(TEXT("That's right u punks!"));
        EndGame();
        return;
    }
    else{
        if(Lives > 1){
            FBullCowCount Score = GetBullsCows(Guess); 
            PrintLine(TEXT("There are %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
            PrintLine(TEXT("Wrong asnwer, you have %i lives left."), --Lives);
            return;
        }
        else{
            PrintLine(TEXT("You Lost!"));
            ClearScreen();
            EndGame();
            return;
        }
    }
}
void UBullCowCartridge::EndGame(){
    //We're in the endgame now lol
    bGameOver = true;
    PrintLine(TEXT("Game Over!\nThe hidden word was %s\nPress Enter to continue..."), *HiddenWord);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const{
    for(int32 Index = 0; Index < Word.Len(); ++Index){
        for(int32 CompIdx = Index+1; CompIdx < Word.Len(); ++CompIdx){
            if(Word[Index] == Word[CompIdx]){
                return false;
            }
        }
    }
    return true;
}
FBullCowCount UBullCowCartridge::GetBullsCows(const FString& Guess) const{
    FBullCowCount Count;
    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++){
        if(Guess[GuessIndex] == HiddenWord[GuessIndex]){
            Count.Bulls++;
            continue;
        }
        for(int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++){
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex]){
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}
