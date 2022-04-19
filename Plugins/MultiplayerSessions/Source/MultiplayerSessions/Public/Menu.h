// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	 * 
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords = "菜单设置", DisplayName = "菜单设置"), Category="会话相关")
	void MenuSetup();
};
