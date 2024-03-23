// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/Actor.h"
#include "MagicBase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICCIRCLE_API AMagicBase : public AActor
{
	GENERATED_BODY()
protected:
	// �g�p��
	ACharacter* MagicUser;

	// ��������W
	FVector Target;

public:
	// �������閂�@
	virtual void Execute();

	// �g�p�Ґݒ�
	void SetMagicUser(ACharacter* user);

	// �g�p�Ҏ擾
	UFUNCTION(BlueprintCallable)
	ACharacter* GetMagicUser();

	// ���@���x��
	UPROPERTY(EditAnywhere)
	int MagicLevel;
};