// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAGICCIRCLE_API CharacterParameter
{
public:

	// 体力
	UPROPERTY()
	int HP = 0;

	// 最大体力
	UPROPERTY()
	int MAX_HP = 0;

	// 攻撃力
	UPROPERTY()
	int ATTACK_POWER = 0;

	CharacterParameter();
	~CharacterParameter();
};
