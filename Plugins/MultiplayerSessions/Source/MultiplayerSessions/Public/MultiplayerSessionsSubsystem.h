// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"

/** 多人在线会话子系统
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public: //公共部分

	//构造函数
	UMultiplayerSessionsSubsystem();

protected: //受保护的部分

private: //私有部分

	//在线会话接口指针
	IOnlineSessionPtr SessionInterface;
};
