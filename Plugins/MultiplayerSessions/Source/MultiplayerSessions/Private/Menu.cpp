// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

void UMenu::MenuSetup()
{
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
}
