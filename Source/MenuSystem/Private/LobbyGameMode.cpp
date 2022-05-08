// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

//重写登录
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		//玩家的数量
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("有%d个玩家"), NumberOfPlayers)
			);

		if (const APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
		{
			const FString PlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Cyan,
				FString::Printf(TEXT("%s 已加入游戏"), *PlayerName)
			);
		}
	}
}

//重写注销
void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (const APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>())
	{
		//玩家的数量
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("有%d个玩家"), NumberOfPlayers - 1)
			);

		const FString PlayerName = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			-1,
			60.f,
			FColor::Cyan,
			FString::Printf(TEXT("%s 已退出游戏"), *PlayerName)
		);
	}
}
