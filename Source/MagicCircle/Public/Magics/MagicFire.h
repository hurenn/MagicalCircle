// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Magics/MagicBase.h"
#include "MagicFire.generated.h"

/**
 * 
 */
UCLASS()
class MAGICCIRCLE_API AMagicFire : public AMagicBase
{
	GENERATED_BODY()
	
public:
	virtual void Execute() override;
};
