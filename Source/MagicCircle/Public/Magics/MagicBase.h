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
	// �g�p��
	ACharacter* User;

	// ��������W
	FVector Target;

public:
	// �������閂�@
	virtual void Execute();
};
