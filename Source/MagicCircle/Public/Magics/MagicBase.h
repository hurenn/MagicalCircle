// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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
	UPROPERTY(BlueprintReadWrite)
	ACharacter* MagicUser;

	// ��������W
	FVector Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageTimer = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageValue = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* HitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitStopTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitCoolTime = 0.0f;

public:
	// �������閂�@
	virtual void Execute();

	// �g�p�Ґݒ�
	UFUNCTION(BlueprintCallable)
	void SetMagicUser(ACharacter* user);

	// ���@���x��
	UPROPERTY(EditAnywhere)
	int MagicLevel;
};