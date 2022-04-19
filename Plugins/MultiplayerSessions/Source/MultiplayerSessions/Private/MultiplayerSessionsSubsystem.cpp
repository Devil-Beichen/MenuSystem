// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSubsystem.h"

//构造函数
UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	//联机子系统获取
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
		SessionInterface = Subsystem->GetSessionInterface(); //设置会话接口指针
}
