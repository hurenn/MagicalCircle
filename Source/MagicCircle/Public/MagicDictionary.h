// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicName.h"
#include "Angle.h"
#include "InputScore.h"
#include "MagicDictionary.generated.h"

/// <summary>
/// 入力を受け取って名前を返す
/// </summary>
class MAGICCIRCLE_API MagicDictionary
{
private:
	// 入力のスコアを返す
	static EInputScore GetInputScore( const EAngle SampleAngle, const EAngle InputAngle );

	// リストインスタンス
	static TArray<FMagicElement> MagicList;

public:

	// 入力リストから取得
	static EMagicName GetMagic( const TArray<EAngle>& AngleList );

	// 初期登録
	static void Initialize();

	MagicDictionary();
};

/// <summary>
/// リストの要素
/// </summary>
USTRUCT()
struct FMagicElement{
	GENERATED_BODY()

public:
	// 名前
	UPROPERTY(EditAnywhere)
	EMagicName Name;

	// 入力リスト
	UPROPERTY(EditAnywhere)
	TArray<EAngle> AngleList;

	// 入力スコアリスト
	TArray<int> Score;

	// 入力進捗
	int Progress = 0;
};