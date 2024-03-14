// Fill out your copyright notice in the Description page of Project Settings.


#include "Magics/MagicBase.h"
#include "Kismet/KismetSystemLibrary.h"

void AMagicBase::Execute() {
	UKismetSystemLibrary::PrintString(this, TEXT("Default Magic"), true, true, FLinearColor::Red, 5.f);
}