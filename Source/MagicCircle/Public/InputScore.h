// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EInputScore : uint8
{
	// “ü—Í–³‚µ
	None = 0,

	// ‹–—e
	OK = 1,

	// Š®àø
	Great = 2,

	// Ž¸”s
	Failed = 100,
};
