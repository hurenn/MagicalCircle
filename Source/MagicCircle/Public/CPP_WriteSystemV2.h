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

	// 入力座標を取得
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector2D Input2D = FVector2D(0.0f, 0.0f);

	// 入力角度を取得
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		double Angle;

	// Lトリガーイベントハンドラー
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void PressedTriggerLeft(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	// Lトリガー入力終了
	void ReleasedTriggerLeft();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Magic")
	// 魔法発動
	void ExecuteMasic(EMagicName MagicName);

	// 魔法陣展開中か
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

	// Axis Input 呼び出し
	void EventAxis(const FInputActionValue& Value);

	float NormalizeAngle(float AngleInDegrees);

	// マウス操作か
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
	bool IsMouse = true;

	// マウス速度減速
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
	float MouseSpeedDown = 20.0f;

	// 文字列から空白を削除する
	FString RemoveWhiteSpace(FString str);

private:	
	// 入力リスト
	TArray<EAngle> AngleList;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Input設定
	void SetupInput();

	// InputEvent イベントハンドラー関数
	void PressedAxis(const FInputActionValue& Value);

	// 入力終了
	void ReleasedAxis();

	// 角度設定
	void SetAngle( double angle);

	// press状態を管理
	bool IsPressed = false;

	// 入力完了までの時間
	float InputLimitTime = 0.02f;

	// 直前に計測された時間
	float LastSeconds = 0.0;

	// 最後の入力
	EAngle LastInputAngle = EAngle::Nutral;

	// 現在の入力
	EAngle NowInputAngle = EAngle::Nutral;

	// 角度出力
	void OutputAngle( EAngle angle );

	// 方向入力実行
	void ExecuteAngleInput();

	// 入力完了までの時間計測
	FTimerHandle InputTimerHandle;

	// 全方向入力（円形）フラグ
	EAngle AllAngleFlag = EAngle::Nutral;
};
