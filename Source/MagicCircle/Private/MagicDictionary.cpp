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
		{EMagicName::FireTornado, {{EAngle::Up},{EAngle::LeftDown},{EAngle::RightDown}, {EAngle::Up}}},
		{EMagicName::FireTornado, {{EAngle::Up},{EAngle::RightDown},{EAngle::LeftDown}, {EAngle::Up}}},
		/*{EMagicName::FireTornado, {{EAngle::RightDown},{EAngle::Up},{EAngle::LeftDown}, {EAngle::RightDown}}},
		{EMagicName::FireTornado, {{EAngle::RightDown},{EAngle::LeftDown},{EAngle::Up}, {EAngle::RightDown}}},
		{EMagicName::FireTornado, {{EAngle::LeftDown},{EAngle::Up},{EAngle::RightDown}, {EAngle::LeftDown}}},
		{EMagicName::FireTornado, {{EAngle::LeftDown},{EAngle::RightDown},{EAngle::Up}, {EAngle::LeftDown}}},*/

		// �t�O�p�`
		{EMagicName::IceTornado, {{EAngle::Down},{EAngle::LeftUp},{EAngle::RightUp}, {EAngle::Down}}},
		{EMagicName::IceTornado, {{EAngle::Down},{EAngle::RightUp},{EAngle::LeftUp}, {EAngle::Down}}},
		/*{EMagicName::IceTornado, {{EAngle::RightUp},{EAngle::Down},{EAngle::LeftUp}, {EAngle::RightUp}}},
		{EMagicName::IceTornado, {{EAngle::RightUp},{EAngle::LeftUp},{EAngle::Down}, {EAngle::RightUp}}},
		{EMagicName::IceTornado, {{EAngle::LeftUp},{EAngle::Down},{EAngle::RightUp}, {EAngle::LeftUp}}},
		{EMagicName::IceTornado, {{EAngle::LeftUp},{EAngle::RightUp},{EAngle::Down}, {EAngle::LeftUp}}},*/

		// �O�p�d��
		{EMagicName::Annihilation, {{EAngle::Up},{EAngle::LeftDown},{EAngle::RightDown},{EAngle::Up},{EAngle::Down},{EAngle::LeftUp},{EAngle::RightUp}, {EAngle::Down}}},
		{EMagicName::Annihilation, {{EAngle::Up},{EAngle::RightDown},{EAngle::LeftDown},{EAngle::Up},{EAngle::Down},{EAngle::LeftUp},{EAngle::RightUp}, {EAngle::Down}}},
		{EMagicName::Annihilation, {{EAngle::Up},{EAngle::LeftDown},{EAngle::RightDown},{EAngle::Up},{EAngle::Down},{EAngle::RightUp},{EAngle::LeftUp}, {EAngle::Down}}},
		{EMagicName::Annihilation, {{EAngle::Up},{EAngle::RightDown},{EAngle::LeftDown},{EAngle::Up},{EAngle::Down},{EAngle::RightUp},{EAngle::LeftUp}, {EAngle::Down}}},

		// �C�i�Y�}
		{EMagicName::Thunder, {{EAngle::Up},{EAngle::Left},{EAngle::Right}, {EAngle::Down}}},

		// �t�C�i�Y�}
		{EMagicName::ThunderTornado, {{EAngle::Down},{EAngle::Right},{EAngle::Left}, {EAngle::Up}}},

		// �g����
		{EMagicName::WaterShot, {{EAngle::Down}, {EAngle::RightDown}, {EAngle::Right}}},

		// �ܔM�g����
		{EMagicName::FireShot, {{EAngle::Left}, {EAngle::LeftDown}, {EAngle::Down}, {EAngle::RightDown}, {EAngle::Right}}},

		// �C�i�Y�}�g����
		{EMagicName::ThunderShot, {{EAngle::Up},{EAngle::Left},{EAngle::Right}, {EAngle::Down}, {EAngle::RightDown}, {EAngle::Right}}},

		// ���������r
		{EMagicName::RushTornado, {{EAngle::Down}, {EAngle::LeftDown}, {EAngle::Left}}},

		//�@������
		{EMagicName::Recovery, {{EAngle::RightUp},{EAngle::Right},{EAngle::Down},{EAngle::Left},{EAngle::LeftUp}}},

		//�@�񕜃G���A
		{EMagicName::HealingArea, {{EAngle::Up},{EAngle::Down},{EAngle::Left},{EAngle::Right}}},

		// �~�i�����ł͓�d�ہj
		//{EMagicName::Barrier, {{EAngle::Circle}}},
		{EMagicName::Barrier, {{EAngle::Down},{EAngle::LeftDown},{EAngle::Left},{EAngle::LeftUp},{EAngle::Up},{EAngle::RightUp},{EAngle::Right},{EAngle::RightDown},{EAngle::Down}}},
		{EMagicName::Barrier, {{EAngle::Down},{EAngle::RightDown},{EAngle::Right},{EAngle::RightUp},{EAngle::Up},{EAngle::LeftUp},{EAngle::Left},{EAngle::LeftDown},{EAngle::Down}}},

		// �O�d�~�i�����ł͎l�d�ہj

		// �����i8�����j
		//{EMagicName::WarpUp, {{EAngle::Up}}},
		//{EMagicName::WarpRightUp, {{EAngle::RightUp}}},
		//{EMagicName::WarpRight, {{EAngle::Right}}},
		//{EMagicName::WarpRightDown, {{EAngle::RightDown}}},
		//{EMagicName::WarpDown, {{EAngle::Down}}},
		//{EMagicName::WarpLeftDown, {{EAngle::LeftDown}}},
		//{EMagicName::WarpLeft, {{EAngle::Left}}},
		//{EMagicName::WarpLeftUp, {{EAngle::LeftUp}}},

		// A~Z(�������Œ�)

	};
}

EMagicName MagicDictionary::GetMagic( const TArray<EAngle>& AngleList) {
	// ���X�g������
	for (FMagicElement& Element : MagicDictionary::MagicList)
	{
		Element.Progress = 0;
		Element.Score.Empty();
	}
	// �������閂�@�X�^�b�N
	FMagicElement MagicStack;

	// ���̓��X�g��[���璲�ׂ�

	// ���͂����{�ꗗ�ƏƂ炵���킹��
	for (EAngle Angle : AngleList)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, (TEXT("Angle:%s"), *StaticEnum<EAngle>()->GetDisplayValueAsText(Angle).ToString()));
		//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Angle:%s"), *StaticEnum<EAngle>()->GetDisplayValueAsText(Angle).ToString()));

		// �������Ă��閂�@���������[����m�F
		for (FMagicElement& Element : MagicDictionary::MagicList)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("%s"), *StaticEnum<EMagicName>()->GetDisplayValueAsText(Element.Name).ToString()));
			//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("NowProgress:%d"), Element.Progress));

			// ���ɐ����E���s���Ă��閂�@���X�L�b�v
			if (Element.Progress < 0 || Element.Progress >= Element.AngleList.Num()) {
				//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Skip")));
				continue;
			}

			// ���̓��͂����e�͈͓����m�F
			EInputScore result = GetInputScore(Element.AngleList[Element.Progress], Angle);
			//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Score:%s"), *StaticEnum<EInputScore>()->GetDisplayValueAsText(result).ToString()));
			if (result != EInputScore::Failed) {
				Element.Score.Add((int)result);
				Element.Progress++;

				// �Ō�܂œ��͂����B�����ꍇ
				// TODO:�Z�[�t�̎��̓��X�g���L�т邩��s�K��
				if (Element.Progress >= Element.AngleList.Num()) {
					//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Complete")));
					
					// �搔���傫����Βu��
					// �搔�������Ȃ��Y��ɕ`���Ă���Βu��
					if (MagicStack.AngleList.IsEmpty()) {
						MagicStack = Element;
					}else if (Element.AngleList.Num() > MagicStack.AngleList.Num()) {
						MagicStack = Element;
					}else if (Element.AngleList.Num() == MagicStack.AngleList.Num()) {
						int ElementScore = 0, StackScore = 0;
						for (int score : Element.Score) {
							ElementScore += score;
						}
						for (int score : MagicStack.Score) {
							StackScore += score;
						}

						if (ElementScore >= StackScore) {
							MagicStack = Element;
						}
					}
				}

				//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Progress")));
				continue;
			}

			//===================================================
			// ���e����

			// �ŏ��̓��͂̏ꍇ�A�����Ŏ��s
			// NOTE: 2��ڈȍ~�Œ��O�̔���ŋ��e�ł���΁A���s
			if(Element.Progress <= 0) {

				Element.Progress = -1;
				//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Failed")));
				continue;
			}

			// ���O�̔���ŋ��e�͈͂Ɏ��܂��Ă��邩�m�F
			result = GetInputScore(Element.AngleList[Element.Progress - 1], Angle);
			if (result != EInputScore::Failed) {
				// ��菭�Ȃ��X�R�A�������ꍇ�㏑��
				if (Element.Score[Element.Progress - 1] > (int)result) {
					Element.Score[Element.Progress - 1] = (int)result;
				}

				//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Continue")));
				continue;
			}

			// ���s����
			Element.Progress = -1;
			//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, *FString::Printf(TEXT("Miss")));
			continue;
		}
	}

	// ���@����Ԃ�
	return MagicStack.Name;
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