// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

//构造函数
UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem():
	CreateSessionCompleteDelegate(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)), //创建基于UObject的函数委托
	FindSessionsCompleteDelegate(
		FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(
		FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	DestroySessionCompleteDelegate(
		FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(
		FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))

{
	//联机子系统获取
	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
		SessionInterface = Subsystem ->GetSessionInterface(); //设置会话接口指针
}

//创建会话
void UMultiplayerSessionsSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	//获得指定会话名称
	auto ExistingSession = SessionInterface ->GetNamedSession(NAME_GameSession);
	//如果指定的会话不为空指针就删除
	if (ExistingSession != nullptr)
		SessionInterface ->DestroySession(NAME_GameSession);

	//将创建会话委托句柄存储起来，这样我们就可以从委托列表中删除它  （会话请求完成时，将触发委托函数）
	CreateSessionCompleteDelegateHandle = SessionInterface ->AddOnCreateSessionCompleteDelegate_Handle(
		CreateSessionCompleteDelegate);
	//设置单个会话的所有设置
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings ->bIsLANMatch = IOnlineSubsystem::Get() ->GetSubsystemName() == "NULL" ? true : false; //设置游戏是联网模式
	LastSessionSettings ->NumPublicConnections = NumPublicConnections; //设置玩家数量
	LastSessionSettings ->bAllowJoinInProgress = true; //允许加入正在运行的游戏
	LastSessionSettings ->bAllowJoinViaPresence = true; //允许通过玩家的身份加入
	LastSessionSettings ->bShouldAdvertise = true; // 该匹配在服务上公开
	LastSessionSettings ->bUsesPresence = true; //显示用户信息状态
	//LastSessionSettings ->bUseLobbiesIfAvailable = true; //如果平台支持可以搜索 Lobby API
	LastSessionSettings ->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	//通过控制器获取本地第一个有效的玩家
	const ULocalPlayer* LocalPlayer = GetWorld() ->GetFirstLocalPlayerFromController();
	//根据指定设置创建在线会话
	if (!SessionInterface ->CreateSession(*LocalPlayer ->GetPreferredUniqueNetId(), NAME_GameSession,
	                                     *LastSessionSettings))
	{
		//创建会话失败清除委托
		SessionInterface ->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		//广播自定义的委托
		MultiplayerOnCreateSessionComplete.Broadcast(false);
	}
}

//查找会话
void UMultiplayerSessionsSubsystem::FindSessions(int32 MaxSearchResults)
{
}

//加入会话
void UMultiplayerSessionsSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

//销毁会话
void UMultiplayerSessionsSubsystem::DestroySession()
{
}

//开始会话
void UMultiplayerSessionsSubsystem::StartSession()
{
}

//创建会话完成
void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface)
	{
		//创建会话完成清除委托
		SessionInterface ->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
	//广播自定义的委托
	MultiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);
}

//找到会话完成
void UMultiplayerSessionsSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
}

//加入会话完成
void UMultiplayerSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

//销毁会话完成
void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

//开始会话完成
void UMultiplayerSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}
