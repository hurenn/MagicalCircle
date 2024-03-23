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
	// 使用者
	ACharacter* MagicUser;

	// 発動先座標
	FVector Target;

public:
	// 発動する魔法
	virtual void Execute();

	// 使用者設定
	void SetMagicUser(ACharacter* user);

	// 使用者取得
	UFUNCTION(BlueprintCallable)
	ACharacter* GetMagicUser();

	// 魔法レベル
	UPROPERTY(EditAnywhere)
	int MagicLevel;
};