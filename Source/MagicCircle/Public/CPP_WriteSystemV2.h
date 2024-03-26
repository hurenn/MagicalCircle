// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Angle.h"
#include "CPP_WriteSystemV2.generated.h"

UCLASS()
class MAGICCIRCLE_API ACPP_WriteSystemV2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_WriteSystemV2();

	// ���͍��W���擾
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector2D Input2D = FVector2D(0.0f, 0.0f);

	// ���͊p�x���擾
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		double Angle;

	// L�g���K�[�C�x���g�n���h���[
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void PressedTriggerLeft(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	// L�g���K�[���͏I��
	void ReleasedTriggerLeft();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Magic")
	// ���@����
	void ExecuteMasic(EMagicName MagicName);

	// ���@�w�W�J����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
	bool IsOpenedCircle = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// MappingContext
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputMappingContext* MappingContextDefault;

	// AxisInput
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* AxisInputRight;

	// TriggerInput
	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* TriggerInputLeft;

	// Axis Input �Ăяo��
	void EventAxis(const FInputActionValue& Value);

	float NormalizeAngle(float AngleInDegrees);

	// �}�E�X���삩
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
	bool IsMouse = true;

	// �}�E�X���x����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
	float MouseSpeedDown = 20.0f;

	// �����񂩂�󔒂��폜����
	FString RemoveWhiteSpace(FString str);

private:	
	// ���̓��X�g
	TArray<EAngle> AngleList;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Input�ݒ�
	void SetupInput();

	// InputEvent �C�x���g�n���h���[�֐�
	void PressedAxis(const FInputActionValue& Value);

	// ���͏I��
	void ReleasedAxis();

	// �p�x�ݒ�
	void SetAngle( double angle);

	// press��Ԃ��Ǘ�
	bool IsPressed = false;

	// ���͊����܂ł̎���
	float InputLimitTime = 0.02f;

	// ���O�Ɍv�����ꂽ����
	float LastSeconds = 0.0;

	// �Ō�̓���
	EAngle LastInputAngle = EAngle::Nutral;

	// ���݂̓���
	EAngle NowInputAngle = EAngle::Nutral;

	// �p�x�o��
	void OutputAngle( EAngle angle );

	// �������͎��s
	void ExecuteAngleInput();

	// ���͊����܂ł̎��Ԍv��
	FTimerHandle InputTimerHandle;

	// �S�������́i�~�`�j�t���O
	EAngle AllAngleFlag = EAngle::Nutral;
};
