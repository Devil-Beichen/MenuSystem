// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "MultiplayerSessionsSubsystem.h"


//菜单设置
void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport(); //添加到窗口
	SetVisibility(ESlateVisibility::Visible); //设置默认可见
	bIsFocusable = true; //将此标志设置为true，允许此小部件在单击或导航到时接受焦点

	//获取世界并判度
	if (const UWorld* World = GetWorld())
	{
		//获取第一个玩家控制器
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			// 用于设置只允许UI响应用户输入的输入模式的数据结构  
			FInputModeUIOnly InputModeUIOnly;
			//聚焦于小部件
			InputModeUIOnly.SetWidgetToFocus(TakeWidget());
			//不锁定鼠标光标到视口
			InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			//设置输入模式
			PlayerController->SetInputMode(InputModeUIOnly);
			//设置显示鼠标光标
			PlayerController->SetShowMouseCursor(true);
		}
	}

	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		//设置指定的子系统
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		//在线会话子系统 动态绑定 创建会话
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

//初始化
bool UMenu::Initialize()
{
	if (!Super::Initialize())
		return false;
	//主机按钮有效，绑定点击函数
	if (HostButton)
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	//加入按钮有效，绑定加入函数
	if (JoinButton)
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);

	return true;
}

//从关卡中移除
void UMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	MenuTearDown();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

//创建会话
void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString::Printf(TEXT("会话创建成功"))
			);
		}
		if (UWorld* World = GetWorld())
		{
			//服务器的旅行
			World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("会话创建失败！！！"))
			);
		}
	}
}

//主机按钮点击
void UMenu::HostButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		//通过子系统创建会话
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

//加入按钮点击
void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Yellow,
			FString::Printf(TEXT("加入会话"))
		);
	}
}

//菜单移除
void UMenu::MenuTearDown()
{
	//移除视口
	RemoveFromParent();
	//获取世界并判度
	if (const UWorld* World = GetWorld())
	{
		//获取第一个玩家控制器
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			//用于设置只允许玩家输入/玩家控制器响应用户输入的输入模式的数据结构  
			FInputModeGameOnly InputModeGameData;
			//设置输入模式
			PlayerController->SetInputMode(InputModeGameData);
			//设置隐藏鼠标光标
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
