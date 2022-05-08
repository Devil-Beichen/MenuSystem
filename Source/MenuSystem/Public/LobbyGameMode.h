// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEM_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	//重写登录
	virtual void PostLogin(APlayerController* NewPlayer) override;

	//重写注销
	virtual void Logout(AController* Exiting) override;
};
