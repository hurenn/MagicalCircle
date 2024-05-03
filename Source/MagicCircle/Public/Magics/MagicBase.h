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

	// 使用者
	UPROPERTY(BlueprintReadWrite)
	ACharacter* MagicUser;

	// 発動先座標
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
	// 発動する魔法
	virtual void Execute();

	// 使用者設定
	UFUNCTION(BlueprintCallable)
	void SetMagicUser(ACharacter* user);

	// 魔法レベル
	UPROPERTY(EditAnywhere)
	int MagicLevel;
};