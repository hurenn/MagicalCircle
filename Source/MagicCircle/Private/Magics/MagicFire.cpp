// Fill out your copyright notice in the Description page of Project Settings.


#include "Magics/MagicFire.h"
#include "Kismet/KismetSystemLibrary.h"

void AMagicFire::Execute() {
	UKismetSystemLibrary::PrintString(this, TEXT("Fire"), true, true, FLinearColor::Red, 5.f);
}