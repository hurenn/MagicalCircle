// Fill out your copyright notice in the Description page of Project Settings.


#include "Magics/MagicBase.h"

void AMagicBase::Execute() {
}

void AMagicBase::SetMagicUser(ACharacter* user) {
	MagicUser = user;
}

ACharacter* AMagicBase::GetMagicUser() {
	return MagicUser;
}