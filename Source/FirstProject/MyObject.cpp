// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

UMyObject::UMyObject() {
	number = 0.5f;

}

void UMyObject::MyFunction() 
{
	UE_LOG(LogTemp, Warning, TEXT("Warning!"));
}