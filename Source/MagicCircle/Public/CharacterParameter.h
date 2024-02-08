// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MAGICCIRCLE_API CharacterParameter
{
public:

	// �̗�
	UPROPERTY()
	int HP = 0;

	// �ő�̗�
	UPROPERTY()
	int MAX_HP = 0;

	// �U����
	UPROPERTY()
	int ATTACK_POWER = 0;

	CharacterParameter();
	~CharacterParameter();
};
