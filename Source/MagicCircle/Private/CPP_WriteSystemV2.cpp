// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WriteSystemV2.h"
#include "Magics/MagicBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MagicDictionary.h"
#include <cmath>

class UInputMappingContext;

// Sets default values
ACPP_WriteSystemV2::ACPP_WriteSystemV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// �E�X�e�B�b�N���͎擾
	AxisInputRight = LoadObject<UInputAction>(NULL, TEXT("/Game/ThirdPerson/Input/Actions/IA_Write"), NULL, LOAD_None, NULL);
	
	// L�g���K�[���͎擾
	TriggerInputLeft = LoadObject<UInputAction>(NULL, TEXT("/Game/ThirdPerson/Input/Actions/IA_OpenCircle"), NULL, LOAD_None, NULL);

	// IMC�擾
	MappingContextDefault = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/ThirdPerson/Input/IMC_Default"), NULL, LOAD_None, NULL);
}

// Called when the game starts or when spawned
void ACPP_WriteSystemV2::BeginPlay()
{
	Super::BeginPlay();
	
	// Input�ݒ���s��
	SetupInput();

	// ���@���T������(���X�g�ɓo�^)
	UMagicDictionary::Initialize();
}

void ACPP_WriteSystemV2::SetupInput() {
	// PlayerController�擾
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// ���͂�L���ɂ���
	EnableInput(controller);

	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("SetupInput")), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	if (InputComponent) {
		// �A�N�V�����o�C���h
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
			// �X�e�B�b�N����
			EnhancedInputComponent->BindAction(AxisInputRight, ETriggerEvent::Triggered, this, &ACPP_WriteSystemV2::PressedAxis);
			EnhancedInputComponent->BindAction(AxisInputRight, ETriggerEvent::Completed, this, &ACPP_WriteSystemV2::ReleasedAxis);
			// ���g���K�[����
			EnhancedInputComponent->BindAction(TriggerInputLeft, ETriggerEvent::Triggered, this, &ACPP_WriteSystemV2::PressedTriggerLeft);
			EnhancedInputComponent->BindAction(TriggerInputLeft, ETriggerEvent::Completed, this, &ACPP_WriteSystemV2::ReleasedTriggerLeft);
		}
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MappingContextDefault, 0);
		}
	}
}

void ACPP_WriteSystemV2::PressedAxis(const FInputActionValue& Value) {

	// ���@�w�W�J���Ă��Ȃ���΃X�L�b�v
	/*if (!isOpenedCircle) {
		return;
	}*/

	// Vector2D����
	auto v = Value.Get<FVector2D>();
	if (IsMouse) {
		Input2D.X = FMath::Clamp(Input2D.X + v.X / MouseSpeedDown, -1, 1);
		Input2D.Y = FMath::Clamp(Input2D.Y - v.Y / MouseSpeedDown, -1, 1);

	}
	else {
		Input2D.X = FMath::Clamp(v.X, -1, 1);
		Input2D.Y = -FMath::Clamp(v.Y, -1, 1);
	}

	float Length = Input2D.Size();
	if (Length > 1.0f) {
		Input2D = Input2D / Length;
	}
	// UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%f, %f"), Length), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	
	auto r = FMath::Atan2(Input2D.Y, Input2D.X);
	if (r < 0) {
		r = r + 2 * PI;
	}

	// �ő���͔���
	if ( FMath::Abs(Input2D.X) + FMath::Abs(Input2D.Y) < 1.0) {
		return;
	}

	// 360���Ŏ擾
	double angle = FMath::RadiansToDegrees(r);
	SetAngle(angle);
	
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%f"), angle), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%f, %f"), Input2D.X, Input2D.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	// Axis Input Value
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), Input2D.X, Input2D.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));
}
float ACPP_WriteSystemV2::NormalizeAngle(float AngleInDegrees)
{
	const float MinAngle = -180.0f; // ���K���������͈͂̍ŏ��l
	const float MaxAngle = 180.0f; // ���K���������͈͂̍ő�l

	// ���͊p�x���w�肳�ꂽ�͈͂Ƀ}�b�s���O����
	float NormalizedAngle = (AngleInDegrees - MinAngle) / (MaxAngle - MinAngle);
	NormalizedAngle = FMath::Clamp(NormalizedAngle, 0.0f, 1.0f);

	// -1����1�͈̔͂Ƀ}�b�s���O����
	NormalizedAngle = 2.0f * NormalizedAngle - 1.0f;

	return NormalizedAngle;
}

void ACPP_WriteSystemV2::PressedTriggerLeft_Implementation(const FInputActionValue& Value) {

	if (IsOpenedCircle) {
		return;
	}
	IsOpenedCircle = true;

	// ���͊J�n
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Open Magic Circle")), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	// ���̓��X�g������
	AngleList.Empty();
	LastInputAngle = EAngle::Nutral;

	// �����ۑ�������
	AllAngleFlag = EAngle::Nutral;

	Input2D = FVector2D(0, 0);
}

void ACPP_WriteSystemV2::ReleasedTriggerLeft_Implementation() {
	IsOpenedCircle = false;

	// ���͏I��
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("End Circle")), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Note:��U�A���̓��X�g�݂̂ŏo�͂���
	FText EnumText;
	for (EAngle angle : AngleList) {
		EnumText = StaticEnum<EAngle>()->GetDisplayValueAsText(angle);
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%s"), *EnumText.ToString()), true, true, FColor::Red, 10.0f, TEXT("None"));
	}

	// ���̓��X�g��n��
	FMagicElement Magic = UMagicDictionary::GetMagic(AngleList);
	
	EnumText = StaticEnum<EAngle>()->GetDisplayValueAsText(Magic.Name);
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Magic:%s"), *EnumText.ToString() ), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	if (Magic.Name != EMagicName::None) {
		int ScoreSum = 0;
		float ScoreResult = 0;
		
		// �X�R�A���v�l���Z�o
		for (int Score : Magic.Score) {
			ScoreSum += Score;
		}

		ScoreResult = (float)ScoreSum / (float)(Magic.Score.Num() * (int)EInputScore::Great);

		ExecuteMasic(Magic.Name, ScoreResult);
	}
}

void ACPP_WriteSystemV2::ExecuteMasic_Implementation(EMagicName MagicName, float ScoreRate) {
	FString MAGIC_PATH = "/Game/ThirdPerson/Blueprints/Magics/";
	FString MagicType = "BP_Magic" + RemoveWhiteSpace(*StaticEnum<EMagicName>()->GetDisplayValueAsText(MagicName).ToString());

	// BP�N���X���쐬
	FString MagicPath = FString::Printf(TEXT("%s%s.%s_C"),
		*MAGIC_PATH, *MagicType, *MagicType);

	if (MagicPath.IsEmpty()) {
		UKismetSystemLibrary::PrintString(this, TEXT("GetClassError"));
		return;
	}
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s"), *MagicPath), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	// �p�X����BP�N���X���擾
	UClass* BPClass = LoadClass<AMagicBase>(nullptr, *MagicPath);
	if (!BPClass) {
		UKismetSystemLibrary::PrintString(this, TEXT("Not Found Magic Class"));
		return;
	}

	// �擾�����N���X�̃I�u�W�F�N�g�쐬
	AMagicBase* Magic = GetWorld()->SpawnActor<AMagicBase>(BPClass);

	// Transform�Z�b�g
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	FTransform PlayerTransform = PlayerPawn->GetActorTransform();
	Magic->SetActorTransform(PlayerTransform);

	auto User = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);

	// �N���g�p������
	// Magic->SetMagicUser(User);

	Magic->SetUp(User, ScoreRate, Magic);
}

FString ACPP_WriteSystemV2::RemoveWhiteSpace(FString str) {
	FString result;
	for (char c : str) {
		if (c != ' ') {
			result += c;
		}
	}
	return result;
}

void ACPP_WriteSystemV2::SetAngle(double angle) {
	if (angle < 22.5f || angle > 337.5f) {
		OutputAngle(EAngle::Right);
	}
	else if (angle < 67.5f) {
		OutputAngle(EAngle::RightDown);
	}
	else if (angle < 112.5f) {
		OutputAngle(EAngle::Down);
	}
	else if (angle < 157.5f) {
		OutputAngle(EAngle::LeftDown);
	}
	else if (angle < 202.5f) {
		OutputAngle(EAngle::Left);
	}
	else if (angle < 247.5f) {
		OutputAngle(EAngle::LeftUp);
	}
	else if (angle < 292.5f) {
		OutputAngle(EAngle::Up);
	}
	else {
		OutputAngle(EAngle::RightUp);
	}
}

void ACPP_WriteSystemV2::OutputAngle(EAngle InputAngle) {

	// �A�������������
	if (NowInputAngle == InputAngle) {
		return;
	}

	// ���݂̓��͂�ۑ�
	NowInputAngle = InputAngle;

	// ���͕�����ۑ��i�~�`���͗p�j
	AllAngleFlag |= InputAngle;
	EAngle AllFlagSample =
		EAngle::Up | EAngle::Right | EAngle::Down | EAngle::Left |
		EAngle::RightUp | EAngle::RightDown | EAngle::LeftUp | EAngle::LeftDown;
	if ((AllFlagSample & AllAngleFlag) == AllFlagSample) {
		UKismetSystemLibrary::PrintString(this, TEXT("Circle Input"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
		// �����ۑ�������
		AngleList.Add(EAngle::Circle);
		AllAngleFlag = EAngle::Nutral;
	}

	// 0.2�b��ɃR�[���o�b�N�N������^�C�}�[�J�n
	//GetWorldTimerManager().SetTimer(InputTimerHandle, this, &ACPP_WriteSystemV2::ExecuteAngleInput, InputLimitTime, false);

	ExecuteAngleInput();
}

// ���͎��s
void ACPP_WriteSystemV2::ExecuteAngleInput() {
	AllAngleFlag = EAngle::Nutral;

	// ���������ɓ��͂���Ȃ�
	if (LastInputAngle == NowInputAngle) {
		return;
	}
	LastInputAngle = NowInputAngle;
	AngleList.Add(NowInputAngle);

	auto text = "";
	switch (LastInputAngle) {
	case EAngle::Up:
		text = "Up";
		break;
	case EAngle::Right:
		text = "Right";
		break;
	case EAngle::Down:
		text = "Down";
		break;
	case EAngle::Left:
		text = "Left";
		break;
	}
	switch (LastInputAngle) {
	case EAngle::RightUp:
		text = "Right_Up";
		break;
	case EAngle::RightDown:
		text = "Right_Down";
		break;
	case EAngle::LeftUp:
		text = "Left_Up";
		break;
	case EAngle::LeftDown:
		text = "Left_Down";
		break;
	}
	UKismetSystemLibrary::PrintString(this, text, true, true, FColor::Cyan, 10.0f, TEXT("None"));
}

void ACPP_WriteSystemV2::ReleasedAxis() {
	NowInputAngle = EAngle::Nutral;
	if (!IsMouse) {
		Input2D = FVector2D(0, 0);
	}

	// ���̓^�C�}�[���Z�b�g
	GetWorldTimerManager().ClearTimer(InputTimerHandle);
}

// Called every frame
void ACPP_WriteSystemV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

