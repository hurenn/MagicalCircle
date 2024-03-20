// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicDictionary.h"
#include "Engine/Engine.h"

MagicDictionary::MagicDictionary()
{
}

// リスト初期化
TArray<FMagicElement> MagicDictionary::MagicList;

void MagicDictionary::Initialize() {
	MagicList = {
		// 三角形
		{EMagicName::FireTornado, {{EAngle::Up},{EAngle::RightDown},{EAngle::LeftDown}, {EAngle::Up}}},
		{EMagicName::FireTornado, {{EAngle::Up},{EAngle::LeftDown},{EAngle::RightDown}, {EAngle::Up}}},
		{EMagicName::FireTornado, {{EAngle::RightDown},{EAngle::Up},{EAngle::LeftDown}, {EAngle::RightDown}}},
		{EMagicName::FireTornado, {{EAngle::RightDown},{EAngle::LeftDown},{EAngle::Up}, {EAngle::RightDown}}},
		{EMagicName::FireTornado, {{EAngle::LeftDown},{EAngle::Up},{EAngle::RightDown}, {EAngle::LeftDown}}},
		{EMagicName::FireTornado, {{EAngle::LeftDown},{EAngle::RightDown},{EAngle::Up}, {EAngle::LeftDown}}},

		// 逆三角形
		{EMagicName::IceTornado, {{EAngle::Down},{EAngle::RightUp},{EAngle::LeftUp}, {EAngle::Down}}},
		{EMagicName::IceTornado, {{EAngle::Down},{EAngle::LeftUp},{EAngle::RightUp}, {EAngle::Down}}},
		{EMagicName::IceTornado, {{EAngle::RightUp},{EAngle::Down},{EAngle::LeftUp}, {EAngle::RightUp}}},
		{EMagicName::IceTornado, {{EAngle::RightUp},{EAngle::LeftUp},{EAngle::Down}, {EAngle::RightUp}}},
		{EMagicName::IceTornado, {{EAngle::LeftUp},{EAngle::Down},{EAngle::RightUp}, {EAngle::LeftUp}}},
		{EMagicName::IceTornado, {{EAngle::LeftUp},{EAngle::RightUp},{EAngle::Down}, {EAngle::LeftUp}}},

		// イナズマ
		{EMagicName::Thunder, {{EAngle::Up},{EAngle::Left},{EAngle::Right}, {EAngle::Down}}},
		{EMagicName::Thunder, {{EAngle::Down},{EAngle::Right},{EAngle::Left}, {EAngle::Up}}},

		// 逆イナズマ

		// 波動拳
		{EMagicName::WaterShot, {{EAngle::Down}, {EAngle::RightDown}, {EAngle::Right}}},

		// 逆波動拳
		{EMagicName::FireShot, {{EAngle::Down}, {EAngle::LeftDown}, {EAngle::Left}}},

		// 円（説明では二重丸）

		// 三重円（説明では四重丸）

		// 直線（8方向）

	};
}

EMagicName MagicDictionary::GetMagic( const TArray<EAngle>& AngleList) {
	// リスト初期化
	for (FMagicElement& Element : MagicDictionary::MagicList)
	{
		Element.Progress = 0;
		Element.Score.Empty();
	}

	// 入力リストを端から調べる

	// 入力を見本一覧と照らし合わせる
	for (EAngle Angle : AngleList)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, (TEXT("Angle:%s"), *StaticEnum<EAngle>()->GetDisplayValueAsText(Angle).ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Angle:%s"), *StaticEnum<EAngle>()->GetDisplayValueAsText(Angle).ToString()));

		// 入力リストを端から調べる
		for (FMagicElement& Element : MagicDictionary::MagicList)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("%s"), *StaticEnum<EMagicName>()->GetDisplayValueAsText(Element.Name).ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("NowProgress:%d"), Element.Progress));

			// 既に失敗している見本を除外
			if (Element.Progress < 0) {
				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Skip")));
				continue;
			}

			// 現在で引っかかっているか確認
			EInputScore result = GetInputScore(Element.AngleList[Element.Progress], Angle);
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Score:%s"), *StaticEnum<EInputScore>()->GetDisplayValueAsText(result).ToString()));
			if (result != EInputScore::Failed) {
				Element.Score.Add((int)result);
				Element.Progress++;

				// 最後まで入力が到達した場合
				// TODO:セーフの時はリストが伸びるから不適切
				if (Element.Progress >= Element.AngleList.Num()) {
					GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Complete")));
					return Element.Name;
				}

				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Progress")));
				continue;
			}

			// 最初の入力の場合、ここで終了
			if (Element.Progress <= 0) {
				Element.Progress = -1;

				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Failed")));
				continue;
			}

			// 一つ手前で引っかかっているか確認
			result = GetInputScore(Element.AngleList[Element.Progress - 1], Angle);
			if (result != EInputScore::Failed) {
				// より少ないスコアだった場合上書き
				if (Element.Score[Element.Progress - 1] > (int)result) {
					Element.Score[Element.Progress - 1] = (int)result;
				}


				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Continue")));
				continue;
			}

			// 入力失敗
			Element.Progress = -1;
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Miss")));
			continue;
		}
	}

	// 含まれていれば魔法名を返す

	return EMagicName::None;
}

/// <summary>
/// 入力スコア取得
/// </summary>
/// <param name="SampleAngle">正しい方向</param>
/// <param name="InputAngle">入力された方向</param>
/// <returns>スコア</returns>
EInputScore MagicDictionary::GetInputScore(const EAngle SampleAngle, const EAngle InputAngle) {
	switch (SampleAngle) {
		// todo:各方向で判定作成

		case EAngle::Right:
		if (InputAngle == EAngle::RightUp || InputAngle == EAngle::RightDown) {
			return EInputScore::OK;
		}
		else if (InputAngle == EAngle::Right) {
			return EInputScore::Great;
		}
		else {
			return EInputScore::Failed;
		}
		break;

		case EAngle::Down:
			if (InputAngle == EAngle::RightDown || InputAngle == EAngle::LeftDown) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::Down) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;

		case EAngle::Left:
			if (InputAngle == EAngle::LeftUp || InputAngle == EAngle::LeftDown) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::Left) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;

		case EAngle::Up:
			if (InputAngle == EAngle::RightUp || InputAngle == EAngle::LeftUp) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::Up) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;

		case EAngle::RightUp:
			if (InputAngle == EAngle::Up || InputAngle == EAngle::Right) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::RightUp) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;

		case EAngle::RightDown:
			if (InputAngle == EAngle::Right || InputAngle == EAngle::Down) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::RightDown) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;

		case EAngle::LeftDown:
			if (InputAngle == EAngle::Down || InputAngle == EAngle::Left) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::LeftDown) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;

		case EAngle::LeftUp:
			if (InputAngle == EAngle::Left || InputAngle == EAngle::Up) {
				return EInputScore::OK;
			}
			else if (InputAngle == EAngle::LeftUp) {
				return EInputScore::Great;
			}
			else {
				return EInputScore::Failed;
			}
			break;
	}

	return EInputScore::None;
}