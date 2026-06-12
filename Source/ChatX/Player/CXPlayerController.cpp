// Fill out your copyright notice in the Description page of Project Settings.


#include "CXPlayerController.h"

#include "../UI/CXChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../ChatX.h"

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// UI 모드로 설정
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	// UI 생성 및 보여주기
	if (IsValid(ChatInputWidgetClass))
	{
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

// 전달 받은 메세지를 출력함수로 전달
void ACXPlayerController::SetChatMessageString(const FString& InChatMesaageString)
{
	ChatMessageString = InChatMesaageString;

	PrintChatMessageString(ChatMessageString);
}

// 메세지 출력
void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.0f);
}
// 출력은 PlayerController에서?
