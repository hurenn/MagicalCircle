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
	// âä+ïX
	Annihilation,
	// íZÇ¢ñhå‰
	Shield,
	// É~ÉâÅ[ÉVÅ[ÉãÉh
	MirrorShield,
	// ñ≥ìGñhå‰
	Barrier,
	Recovery,
	HealingArea,
	// éûä‘í‚é~
	TimeStop,
	// â¡ë¨
	Accelerate,
	// å∏ë¨
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
