// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicDictionary.h"
#include "Engine/Engine.h"

MagicDictionary::MagicDictionary()
{
}

// ���X�g������
TArray<FMagicElement> MagicDictionary::MagicList;

void MagicDictionary::Initialize() {
	MagicList = {
		// �O�p�`
		{EMagicName::FireTornado, {{EAngle::Up},{EAngle::RightDown},{EAngle::LeftDown}, {EAngle::Up}}},
		{EMagicName::FireTornado, {{EAngle::Up},{EAngle::LeftDown},{EAngle::RightDown}, {EAngle::Up}}},
		{EMagicName::FireTornado, {{EAngle::RightDown},{EAngle::Up},{EAngle::LeftDown}, {EAngle::RightDown}}},
		{EMagicName::FireTornado, {{EAngle::RightDown},{EAngle::LeftDown},{EAngle::Up}, {EAngle::RightDown}}},
		{EMagicName::FireTornado, {{EAngle::LeftDown},{EAngle::Up},{EAngle::RightDown}, {EAngle::LeftDown}}},
		{EMagicName::FireTornado, {{EAngle::LeftDown},{EAngle::RightDown},{EAngle::Up}, {EAngle::LeftDown}}},

		// �t�O�p�`
		{EMagicName::IceTornado, {{EAngle::Down},{EAngle::RightUp},{EAngle::LeftUp}, {EAngle::Down}}},
		{EMagicName::IceTornado, {{EAngle::Down},{EAngle::LeftUp},{EAngle::RightUp}, {EAngle::Down}}},
		{EMagicName::IceTornado, {{EAngle::RightUp},{EAngle::Down},{EAngle::LeftUp}, {EAngle::RightUp}}},
		{EMagicName::IceTornado, {{EAngle::RightUp},{EAngle::LeftUp},{EAngle::Down}, {EAngle::RightUp}}},
		{EMagicName::IceTornado, {{EAngle::LeftUp},{EAngle::Down},{EAngle::RightUp}, {EAngle::LeftUp}}},
		{EMagicName::IceTornado, {{EAngle::LeftUp},{EAngle::RightUp},{EAngle::Down}, {EAngle::LeftUp}}},

		// �C�i�Y�}
		{EMagicName::Thunder, {{EAngle::Up},{EAngle::Left},{EAngle::Right}, {EAngle::Down}}},
		{EMagicName::Thunder, {{EAngle::Down},{EAngle::Right},{EAngle::Left}, {EAngle::Up}}},

		// �t�C�i�Y�}

		// �g����
		{EMagicName::WaterShot, {{EAngle::Down}, {EAngle::RightDown}, {EAngle::Right}}},

		// �t�g����
		{EMagicName::FireShot, {{EAngle::Down}, {EAngle::LeftDown}, {EAngle::Left}}},

		// �~�i�����ł͓�d�ہj

		// �O�d�~�i�����ł͎l�d�ہj

		// �����i8�����j

	};
}

EMagicName MagicDictionary::GetMagic( const TArray<EAngle>& AngleList) {
	// ���X�g������
	for (FMagicElement& Element : MagicDictionary::MagicList)
	{
		Element.Progress = 0;
		Element.Score.Empty();
	}

	// ���̓��X�g��[���璲�ׂ�

	// ���͂����{�ꗗ�ƏƂ炵���킹��
	for (EAngle Angle : AngleList)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, (TEXT("Angle:%s"), *StaticEnum<EAngle>()->GetDisplayValueAsText(Angle).ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Angle:%s"), *StaticEnum<EAngle>()->GetDisplayValueAsText(Angle).ToString()));

		// ���̓��X�g��[���璲�ׂ�
		for (FMagicElement& Element : MagicDictionary::MagicList)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("%s"), *StaticEnum<EMagicName>()->GetDisplayValueAsText(Element.Name).ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("NowProgress:%d"), Element.Progress));

			// ���Ɏ��s���Ă��錩�{�����O
			if (Element.Progress < 0) {
				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Skip")));
				continue;
			}

			// ���݂ň����������Ă��邩�m�F
			EInputScore result = GetInputScore(Element.AngleList[Element.Progress], Angle);
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Score:%s"), *StaticEnum<EInputScore>()->GetDisplayValueAsText(result).ToString()));
			if (result != EInputScore::Failed) {
				Element.Score.Add((int)result);
				Element.Progress++;

				// �Ō�܂œ��͂����B�����ꍇ
				// TODO:�Z�[�t�̎��̓��X�g���L�т邩��s�K��
				if (Element.Progress >= Element.AngleList.Num()) {
					GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Complete")));
					return Element.Name;
				}

				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Progress")));
				continue;
			}

			// �ŏ��̓��͂̏ꍇ�A�����ŏI��
			if (Element.Progress <= 0) {
				Element.Progress = -1;

				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Failed")));
				continue;
			}

			// ���O�ň����������Ă��邩�m�F
			result = GetInputScore(Element.AngleList[Element.Progress - 1], Angle);
			if (result != EInputScore::Failed) {
				// ��菭�Ȃ��X�R�A�������ꍇ�㏑��
				if (Element.Score[Element.Progress - 1] > (int)result) {
					Element.Score[Element.Progress - 1] = (int)result;
				}


				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Continue")));
				continue;
			}

			// ���͎��s
			Element.Progress = -1;
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Miss")));
			continue;
		}
	}

	// �܂܂�Ă���Ζ��@����Ԃ�

	return EMagicName::None;
}

/// <summary>
/// ���̓X�R�A�擾
/// </summary>
/// <param name="SampleAngle">����������</param>
/// <param name="InputAngle">���͂��ꂽ����</param>
/// <returns>�X�R�A</returns>
EInputScore MagicDictionary::GetInputScore(const EAngle SampleAngle, const EAngle InputAngle) {
	switch (SampleAngle) {
		// todo:�e�����Ŕ���쐬

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