// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuSystemCharacter.generated.h"

UCLASS(config=Game)
class AMenuSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMenuSystemCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	//会话接口指针
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	//创建游戏会话
	UFUNCTION(BlueprintCallable, meta=(Keywords = "创建游戏会话", DisplayName = "创建游戏会话"), Category="会话相关")
	void CreateGameSession();

	//加入游戏会话
	UFUNCTION(BlueprintCallable, meta=(Keywords = "加入游戏会话", DisplayName = "加入游戏会话"), Category="会话相关")
	void JoinGameSession();

	//创建会话函数
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	//搜索会话函数
	void OnFindSessionsComplete(bool bWasSuccessful);

	//加入会话
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	//会话委托
	FOnCreateSessionCompleteDelegate CompleteSessionCompleteDelegate;

	//会话搜索委托
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	//搜索结果
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	//会话加入完成委托
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
};
