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
class MAGICCIRCLE_API MagicDictionary
{
private:
	// ���͂̃X�R�A��Ԃ�
	static EInputScore GetInputScore( const EAngle SampleAngle, const EAngle InputAngle );

	// ���X�g�C���X�^���X
	static TArray<FMagicElement> MagicList;

public:

	// ���̓��X�g����擾
	static EMagicName GetMagic( const TArray<EAngle>& AngleList );

	// �����o�^
	static void Initialize();

	MagicDictionary();
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
	EMagicName Name;

	// ���̓��X�g
	UPROPERTY(EditAnywhere)
	TArray<EAngle> AngleList;

	// ���̓X�R�A���X�g
	TArray<int> Score;

	// ���͐i��
	int Progress = 0;
};