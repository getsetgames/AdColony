//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "AdColonyPrivatePCH.h"

#if PLATFORM_IOS
@interface ACDelegate : NSObject <AdColonyDelegate,AdColonyAdDelegate>

@end

static ACDelegate *ACDelegateSingleton = [[ACDelegate alloc] init];

NSArray* GetNSStringArray(TArray<FString> FStringArray)
{
	NSMutableArray* NewArray = [NSMutableArray array];
	
	for (auto Itr(FStringArray.CreateIterator()); Itr; Itr++)
	{
		FString String = (*Itr);
		[NewArray addObject:String.GetNSString()];
	}
	
	return NewArray;
}
#endif

void UAdColonyFunctions::AdColonyConfigure(FString AppId, TArray<FString> ZoneIds, bool Logging, FString CustomUserId)
{
#if PLATFORM_IOS
	if (CustomUserId.IsEmpty() == false)
	{
		dispatch_sync(dispatch_get_main_queue(), ^{
			[AdColony setCustomID:CustomUserId.GetNSString()];
		});
	}
	
	dispatch_sync(dispatch_get_main_queue(), ^{
		[AdColony configureWithAppID:AppId.GetNSString() zoneIDs:GetNSStringArray(ZoneIds) delegate:ACDelegateSingleton logging:Logging];
	});
#endif
}

void UAdColonyFunctions::AdColonyPlayVideo(FString ZoneId)
{
#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		[AdColony playVideoAdForZone:ZoneId.GetNSString() withDelegate:ACDelegateSingleton];
	});
#endif
}

void UAdColonyFunctions::AdColonyPlayV4VCVideo(FString ZoneId, bool PrePopup, bool PostPopup)
{
#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		[AdColony playVideoAdForZone:ZoneId.GetNSString() withDelegate:ACDelegateSingleton withV4VCPrePopup:PrePopup andV4VCPostPopup:PostPopup];
	});
#endif
}

bool UAdColonyFunctions::AdColonyIsVirtualCurrencyRewardAvailable(FString ZoneId)
{
#if PLATFORM_IOS
	__block bool Result = false;
	dispatch_sync(dispatch_get_main_queue(), ^{
		Result = [AdColony isVirtualCurrencyRewardAvailableForZone:ZoneId.GetNSString()];
	});
	return Result;
#endif
	
	return false;
}

#if PLATFORM_IOS
@implementation ACDelegate
- ( void ) onAdColonyAdAvailabilityChange:( BOOL )available inZone:( NSString * )zoneID
{
	UAdColonyComponent::AdAvailabilityChangedDelegate.Broadcast(available,FString(zoneID));
}

- ( void ) onAdColonyV4VCReward:( BOOL )success currencyName:( NSString * )currencyName currencyAmount:( int )amount inZone:( NSString * )zoneID
{
	UAdColonyComponent::V4VCRewardDelegate.Broadcast(success,FString(currencyName),amount,FString(zoneID));
}

- ( void ) onAdColonyAdStartedInZone:( NSString * )zoneID
{
	UAdColonyComponent::AdStartedDelegate.Broadcast(FString(zoneID));
}

- ( void ) onAdColonyAdAttemptFinished:(BOOL)shown inZone:( NSString * )zoneID
{
	UAdColonyComponent::AdAttemptFinishedDelegate.Broadcast(shown,FString(zoneID));
}

- ( void ) onAdColonyAdFinishedWithInfo:( AdColonyAdInfo * )info
{
	UAdColonyComponent::AdFinishedDelegate.Broadcast(FAdColonyAdInfo(info.shown,info.zoneID,info.iapEnabled,info.iapProductID,info.iapQuantity,(EAdColonyIAPEngagement::IAPEngagement)info.iapEngagementType));
}
@end
#endif
