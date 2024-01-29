// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/NoExportTypes.h"
#include "MagicBase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICCIRCLE_API UMagicBase : public UObject
{
	GENERATED_BODY()
protected:
	// 使用者
	ACharacter* User;

	// 発動先座標
	FVector Target;

public:
	// 発動する魔法
	virtual void Execute();
};
