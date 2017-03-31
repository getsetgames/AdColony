//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "AdColonyFunctions.generated.h"

UCLASS(NotBlueprintable)
class UAdColonyFunctions : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "adcolony ad advertising"), Category = "AdColony")
	static void AdColonyConfigure(FString AppId, TArray<FString> ZoneIds, bool Logging, FString CustomUserId);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "adcolony ad advertising"), Category = "AdColony")
	static void AdColonyPlayVideo(FString ZoneId);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "adcolony ad advertising"), Category = "AdColony")
	static void AdColonyPlayV4VCVideo(FString ZoneId, bool PrePopup, bool PostPopup);

	UFUNCTION(BlueprintPure, meta = (Keywords = "adcolony ad advertising"), Category = "AdColony")
	static bool AdColonyIsVirtualCurrencyRewardAvailable(FString ZoneId);
};
