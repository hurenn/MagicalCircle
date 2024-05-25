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
	// 炎+氷
	Annihilation,
	// ミラーシールド
	MirrorShield,
	// バリア
	Barrier,
	// 無限バリア
	UnlimitBarrier,
	Recovery,
	HealingArea,
	// 時間停止
	TimeStop,
	// 加速
	Accelerate,
	// 減速
	Decelerate,
	// 透明化
	Invisible,
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
