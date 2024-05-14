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
	
	// 右スティック入力取得
	AxisInputRight = LoadObject<UInputAction>(NULL, TEXT("/Game/ThirdPerson/Input/Actions/IA_Write"), NULL, LOAD_None, NULL);
	
	// Lトリガー入力取得
	TriggerInputLeft = LoadObject<UInputAction>(NULL, TEXT("/Game/ThirdPerson/Input/Actions/IA_OpenCircle"), NULL, LOAD_None, NULL);

	// IMC取得
	MappingContextDefault = LoadObject<UInputMappingContext>(NULL, TEXT("/Game/ThirdPerson/Input/IMC_Default"), NULL, LOAD_None, NULL);
}

// Called when the game starts or when spawned
void ACPP_WriteSystemV2::BeginPlay()
{
	Super::BeginPlay();
	
	// Input設定を行う
	SetupInput();

	// 魔法辞典初期化(リストに登録)
	UMagicDictionary::Initialize();
}

void ACPP_WriteSystemV2::SetupInput() {
	// PlayerController取得
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 入力を有効にする
	EnableInput(controller);

	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("SetupInput")), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	if (InputComponent) {
		// アクションバインド
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
			// スティック入力
			EnhancedInputComponent->BindAction(AxisInputRight, ETriggerEvent::Triggered, this, &ACPP_WriteSystemV2::PressedAxis);
			EnhancedInputComponent->BindAction(AxisInputRight, ETriggerEvent::Completed, this, &ACPP_WriteSystemV2::ReleasedAxis);
			// 左トリガー入力
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

	// 魔法陣展開していなければスキップ
	/*if (!isOpenedCircle) {
		return;
	}*/

	// Vector2D入力
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

	// 最大入力判定
	if ( FMath::Abs(Input2D.X) + FMath::Abs(Input2D.Y) < 1.0) {
		return;
	}

	// 360°で取得
	double angle = FMath::RadiansToDegrees(r);
	SetAngle(angle);
	
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%f"), angle), true, true, FColor::Cyan, 10.0f, TEXT("None"));
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%f, %f"), Input2D.X, Input2D.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	// Axis Input Value
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%f Y:%f"), Input2D.X, Input2D.Y), true, true, FColor::Cyan, 10.0f, TEXT("None"));
}
float ACPP_WriteSystemV2::NormalizeAngle(float AngleInDegrees)
{
	const float MinAngle = -180.0f; // 正規化したい範囲の最小値
	const float MaxAngle = 180.0f; // 正規化したい範囲の最大値

	// 入力角度を指定された範囲にマッピングする
	float NormalizedAngle = (AngleInDegrees - MinAngle) / (MaxAngle - MinAngle);
	NormalizedAngle = FMath::Clamp(NormalizedAngle, 0.0f, 1.0f);

	// -1から1の範囲にマッピングする
	NormalizedAngle = 2.0f * NormalizedAngle - 1.0f;

	return NormalizedAngle;
}

void ACPP_WriteSystemV2::PressedTriggerLeft_Implementation(const FInputActionValue& Value) {

	if (IsOpenedCircle) {
		return;
	}
	IsOpenedCircle = true;

	// 入力開始
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Open Magic Circle")), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	// 入力リスト初期化
	AngleList.Empty();
	LastInputAngle = EAngle::Nutral;

	// 方向保存初期化
	AllAngleFlag = EAngle::Nutral;

	Input2D = FVector2D(0, 0);
}

void ACPP_WriteSystemV2::ReleasedTriggerLeft_Implementation() {
	IsOpenedCircle = false;

	// 入力終了
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("End Circle")), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	//Note:一旦、入力リストのみで出力する
	FText EnumText;
	for (EAngle angle : AngleList) {
		EnumText = StaticEnum<EAngle>()->GetDisplayValueAsText(angle);
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("X:%s"), *EnumText.ToString()), true, true, FColor::Red, 10.0f, TEXT("None"));
	}

	// 入力リストを渡す
	FMagicElement Magic = UMagicDictionary::GetMagic(AngleList);
	
	EnumText = StaticEnum<EAngle>()->GetDisplayValueAsText(Magic.Name);
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Magic:%s"), *EnumText.ToString() ), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	if (Magic.Name != EMagicName::None) {
		int ScoreSum = 0;
		float ScoreResult = 0;
		
		// スコア合計値を算出
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

	// BPクラス名作成
	FString MagicPath = FString::Printf(TEXT("%s%s.%s_C"),
		*MAGIC_PATH, *MagicType, *MagicType);

	if (MagicPath.IsEmpty()) {
		UKismetSystemLibrary::PrintString(this, TEXT("GetClassError"));
		return;
	}
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s"), *MagicPath), true, true, FColor::Cyan, 10.0f, TEXT("None"));

	// パスからBPクラスを取得
	UClass* BPClass = LoadClass<AMagicBase>(nullptr, *MagicPath);
	if (!BPClass) {
		UKismetSystemLibrary::PrintString(this, TEXT("Not Found Magic Class"));
		return;
	}

	// 取得したクラスのオブジェクト作成
	AMagicBase* Magic = GetWorld()->SpawnActor<AMagicBase>(BPClass);

	// Transformセット
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	FTransform PlayerTransform = PlayerPawn->GetActorTransform();
	Magic->SetActorTransform(PlayerTransform);

	auto User = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);

	// 誰が使用したか
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

	// 連続処理を避ける
	if (NowInputAngle == InputAngle) {
		return;
	}

	// 現在の入力を保存
	NowInputAngle = InputAngle;

	// 入力方向を保存（円形入力用）
	AllAngleFlag |= InputAngle;
	EAngle AllFlagSample =
		EAngle::Up | EAngle::Right | EAngle::Down | EAngle::Left |
		EAngle::RightUp | EAngle::RightDown | EAngle::LeftUp | EAngle::LeftDown;
	if ((AllFlagSample & AllAngleFlag) == AllFlagSample) {
		UKismetSystemLibrary::PrintString(this, TEXT("Circle Input"), true, true, FColor::Cyan, 10.0f, TEXT("None"));
		// 方向保存初期化
		AngleList.Add(EAngle::Circle);
		AllAngleFlag = EAngle::Nutral;
	}

	// 0.2秒後にコールバック起動するタイマー開始
	//GetWorldTimerManager().SetTimer(InputTimerHandle, this, &ACPP_WriteSystemV2::ExecuteAngleInput, InputLimitTime, false);

	ExecuteAngleInput();
}

// 入力実行
void ACPP_WriteSystemV2::ExecuteAngleInput() {
	AllAngleFlag = EAngle::Nutral;

	// 同じ方向に入力されない
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

	// 入力タイマーリセット
	GetWorldTimerManager().ClearTimer(InputTimerHandle);
}

// Called every frame
void ACPP_WriteSystemV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

