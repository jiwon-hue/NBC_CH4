// Fill out your copyright notice in the Description page of Project Settings.

#include "CXChatInput.h"

#include "Components/EditableTextBox.h"
#include "../Player/CXPlayerController.h"

void UCXChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	// TextCommitted 라는 TextBox의 델리게이트에 바인드 시도
	if (!(EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted)))
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UCXChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	// TextCommitted 바인드 해제
	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted))
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UCXChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		// 컨트롤러 가져오기
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (OwningPlayerController)
		{
			ACXPlayerController* OwningCXPlayerController = Cast<ACXPlayerController>(OwningPlayerController);
			if (OwningCXPlayerController)
			{
				// 출력하기 위해 PlyaerController로 전달
				OwningCXPlayerController->SetChatMessageString(Text.ToString());

				// 텍스트 리셋
				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}
