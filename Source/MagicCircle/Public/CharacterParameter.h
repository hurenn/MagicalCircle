// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAGICCIRCLE_API CharacterParameter
{
public:

	// ‘Ì—Í
	UPROPERTY()
	int HP = 0;

	// Å‘å‘Ì—Í
	UPROPERTY()
	int MAX_HP = 0;

	// UŒ‚—Í
	UPROPERTY()
	int ATTACK_POWER = 0;

	CharacterParameter();
	~CharacterParameter();
};
