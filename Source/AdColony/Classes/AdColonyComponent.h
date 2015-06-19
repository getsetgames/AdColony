//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "AdColonyComponent.generated.h"

UENUM(BlueprintType)
namespace EAdColonyIAPEngagement {
	enum IAPEngagement
	{
		IAP_ENGAGEMENT_NONE					UMETA(DisplayName="None"),
		IAP_ENGAGEMENT_AUTOMATIC			UMETA(DisplayName="Automatic"),
		IAP_ENGAGEMENT_END_CARD				UMETA(DisplayName="End Card"),
	};
}

USTRUCT(BlueprintType)
struct FAdColonyAdInfo
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category=AdColony)
	bool Shown;
	
	UPROPERTY(BlueprintReadOnly, Category=AdColony)
	FString ZoneId;
	
	UPROPERTY(BlueprintReadOnly, Category=AdColony)
	bool IAPEnabled;
	
	UPROPERTY(BlueprintReadOnly, Category=AdColony)
	FString IAPProductId;

	UPROPERTY(BlueprintReadOnly, Category=AdColony)
	int32 IAPQuantity;

	UPROPERTY(BlueprintReadOnly, Category=AdColony)
	TEnumAsByte<EAdColonyIAPEngagement::IAPEngagement> IAPEngagementType;

	FAdColonyAdInfo()
	{
		
	}
	
	FORCEINLINE FAdColonyAdInfo(bool InShown,
								FString InZoneId,
								bool InIAPEnabled,
								FString InIAPProductId,
								int32 InIAPQuantity,
								EAdColonyIAPEngagement::IAPEngagement InIAPEngagementType
								):
	Shown(InShown),
	ZoneId(InZoneId),
	IAPEnabled(InIAPEnabled),
	IAPProductId(InIAPProductId),
	IAPQuantity(InIAPQuantity),
	IAPEngagementType(InIAPEngagementType)
	{
		
	}
};

UCLASS(ClassGroup=AdColony, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UAdColonyComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	void OnRegister() override;
	void OnUnregister() override;
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FAdColonyAdAvailabilityChangedDelegate,bool,FString);
	DECLARE_MULTICAST_DELEGATE_FourParams(FAdColonyV4VCRewardDelegate,bool,FString,int32,FString);
	DECLARE_MULTICAST_DELEGATE_OneParam(FAdColonyAdStartedDelegate,FString);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FAdColonyAdAttemptFinishedDelegate,bool,FString);
	DECLARE_MULTICAST_DELEGATE_OneParam(FAdColonyAdFinishedDelegate,FAdColonyAdInfo);
	
	static FAdColonyAdAvailabilityChangedDelegate AdAvailabilityChangedDelegate;
	static FAdColonyV4VCRewardDelegate V4VCRewardDelegate;
	static FAdColonyAdStartedDelegate AdStartedDelegate;
	static FAdColonyAdAttemptFinishedDelegate AdAttemptFinishedDelegate;
	static FAdColonyAdFinishedDelegate AdFinishedDelegate;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAdColonyAdAvailabilityChangedDynDelegate,bool,Available,FString,ZoneId);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FAdColonyV4VCRewardDynDelegate,bool,Success,FString,CurrencyName,int32,Amount,FString,ZoneId);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdColonyAdStartedDynDelegate,FString,ZoneId);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAdColonyAdAttemptFinishedDynDelegate,bool,Shown,FString,ZoneId);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdColonyAdFinishedDynDelegate,FAdColonyAdInfo,Info);

	UPROPERTY(BlueprintAssignable)
	FAdColonyAdAvailabilityChangedDynDelegate AdAvailabilityChanged;
	
	UPROPERTY(BlueprintAssignable)
	FAdColonyV4VCRewardDynDelegate V4VCReward;
	
	UPROPERTY(BlueprintAssignable)
	FAdColonyAdStartedDynDelegate AdStarted;
	
	UPROPERTY(BlueprintAssignable)
	FAdColonyAdAttemptFinishedDynDelegate AdAttemptFinished;
	
	UPROPERTY(BlueprintAssignable)
	FAdColonyAdFinishedDynDelegate AdFinished;
	
private:
	void AdAvailabilityChanged_Handler(bool Available, FString ZoneId) { AdAvailabilityChanged.Broadcast(Available,ZoneId); }
	void V4VCReward_Handler(bool Success, FString CurrencyName, int32 Amount, FString ZoneId) { V4VCReward.Broadcast(Success,CurrencyName,Amount,ZoneId); }
	void AdStarted_Handler(FString ZoneId) { AdStarted.Broadcast(ZoneId); }
	void AdAttemptFinished_Handler(bool Shown, FString ZoneId) { AdAttemptFinished.Broadcast(Shown,ZoneId); }
	void AdFinished_Handler(FAdColonyAdInfo AdInfo) { AdFinished.Broadcast(AdInfo); }
};
