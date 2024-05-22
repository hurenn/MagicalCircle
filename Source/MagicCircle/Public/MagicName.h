// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMagicName : uint8
{
	None,
	FireShot,
	WaterShot,
	ThunderShot,
	RushTornado,
	FireTornado,
	IceTornado,
	ThunderTornado,
	Thunder,
	// ��+�X
	Annihilation,
	// �Z���h��
	Shield,
	// ���G�h��
	Barrier,
	Recovery,
	HealingArea,
	// ���Ԓ�~
	TimeStop,
	// ����
	Accelerate,
	// ����
	Decelerate,
	WarpUp,
	/*
	WarpRightUp,
	WarpRight,
	WarpRightDown,
	WarpDown,
	WarpLeftDown,
	WarpLeft,
	WarpLeftUp,
	*/
};
