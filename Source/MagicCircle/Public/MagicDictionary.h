// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicName.h"
#include "Angle.h"
#include "InputScore.h"
#include "MagicDictionary.generated.h"

/// <summary>
/// ���͂��󂯎���Ė��O��Ԃ�
/// </summary>
UCLASS(BlueprintType, Blueprintable)
class MAGICCIRCLE_API UMagicDictionary : public UObject
{
	GENERATED_BODY()
private:
	// ���͂̃X�R�A��Ԃ�
	static EInputScore GetInputScore( const EAngle SampleAngle, const EAngle InputAngle );

public:

	// ���X�g�C���X�^���X
	static TArray<FMagicElement> MagicList;

	// ���̓��X�g����擾
	static FMagicElement GetMagic( const TArray<EAngle>& AngleList );

	// �����o�^
	static void Initialize();
};

/// <summary>
/// ���X�g�̗v�f
/// </summary>
USTRUCT()
struct FMagicElement{
	GENERATED_BODY()

public:
	// ���O
	UPROPERTY(EditAnywhere)
	EMagicName Name = EMagicName::None;

	// ���̓��X�g
	UPROPERTY(EditAnywhere)
	TArray<EAngle> AngleList = {};

	// ���̓X�R�A���X�g
	TArray<int> Score = {};

	// ���͐i��
	int Progress = 0;
};