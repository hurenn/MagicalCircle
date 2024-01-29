// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EInputScore : uint8
{
	// ���͖���
	None = 0,

	// ���e
	OK = 1,

	// ����
	Great = 2,

	// ���s
	Failed = 100,
};
