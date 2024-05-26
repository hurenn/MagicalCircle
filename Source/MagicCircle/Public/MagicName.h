// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMagicName : uint8
{
	None,
	FireTornado = 1,
	IceTornado,
	// 加速
	Accelerate,
	// 減速
	Decelerate,
	Thunder,
	ThunderShot,
	RushTornado,
	WaterShot,
	FireShot,
	//ThunderTornado,
	// バリア
	Barrier,
	// ミラーシールド
	MirrorShield,
	Recovery,
	HealingArea,
	// 透明化
	Invisible,
	// 時間停止
	TimeStop,
	// 炎+氷
	Annihilation,
	// ポータル
	// Portal,
	// チャージ
	// Charge,
	// 無限バリア
	// UnlimitBarrier,
	//ランダム
	// Random,
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
