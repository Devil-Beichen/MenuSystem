// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Menu.generated.h"

/** 菜单
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public: //公共部分

	/** 菜单设置
	 * @param NumberOfPublicConnections		-	玩家数量
	 * @param TypeOfMatch					-	匹配类型
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords = "菜单设置", DisplayName = "菜单设置"), Category="会话相关")
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("对所有人开放")));

protected: //受保护的部分

	//初始化
	virtual bool Initialize() override;

	//从关卡中移除
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	//
	//多人在线会话子系统上自定义委托的回调 
	//
	
	/** 创建会话
	 * @param bWasSuccessful	-	是成功的
	 */
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);


private: //私有部分

	//创建会话按钮
	UPROPERTY(meta=(BindWidget))
	UButton* HostButton;

	//加入会话按钮
	UPROPERTY(meta=(BindWidget))
	UButton* JoinButton;

	//创建会话
	UFUNCTION()
	void HostButtonClicked();

	//加入会话
	UFUNCTION()
	void JoinButtonClicked();

	//菜单移除
	void MenuTearDown();

	//处理所有在线会话功能的子系统
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	//玩家数量
	int32 NumPublicConnections{4};

	//匹配类型
	FString MatchType{TEXT("对所有人开放")};
};
