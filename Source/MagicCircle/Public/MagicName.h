// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMagicName : uint8
{
	None,
	FireTornado = 1,
	IceTornado,
	// ����
	Accelerate,
	// ����
	Decelerate,
	Thunder,
	ThunderShot,
	RushTornado,
	WaterShot,
	FireShot,
	//ThunderTornado,
	// �o���A
	Barrier,
	// �~���[�V�[���h
	MirrorShield,
	Recovery,
	HealingArea,
	// ������
	Invisible,
	// ���Ԓ�~
	TimeStop,
	// ��+�X
	Annihilation,
	// �|�[�^��
	// Portal,
	// �`���[�W
	// Charge,
	// �����o���A
	// UnlimitBarrier,
	//�����_��
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
