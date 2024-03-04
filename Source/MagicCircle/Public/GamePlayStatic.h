// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MAGICCIRCLE_API GamePlayStatic : UBlueprintFunctionLibrary
{
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GamePlayStatic")
	static void ExecuteDamage(float damage);
};
