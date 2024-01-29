// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Angle.generated.h"

UENUM(BlueprintType)
enum class EAngle : uint8
{
	Nutral =	0,
	Up =	    1<<0,
	Right =	    1<<1,
	Down =	    1<<2,
	Left =	    1<<3,
	RightUp =   1<<4,
	RightDown = 1<<5,
	LeftDown =	1<<6,
	LeftUp =	1<<7,
	Circle,
};
ENUM_CLASS_FLAGS(EAngle);
