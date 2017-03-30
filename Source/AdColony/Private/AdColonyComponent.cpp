//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "AdColonyComponent.h"
#include "AdColonyPrivatePCH.h"

void UAdColonyComponent::OnRegister()
{
	Super::OnRegister();
	
	UAdColonyComponent::AdAvailabilityChangedDelegate.AddUObject(this, &UAdColonyComponent::AdAvailabilityChanged_Handler);
	UAdColonyComponent::V4VCRewardDelegate.AddUObject(this, &UAdColonyComponent::V4VCReward_Handler);
	UAdColonyComponent::AdStartedDelegate.AddUObject(this, &UAdColonyComponent::AdStarted_Handler);
	UAdColonyComponent::AdAttemptFinishedDelegate.AddUObject(this, &UAdColonyComponent::AdAttemptFinished_Handler);
	UAdColonyComponent::AdFinishedDelegate.AddUObject(this, &UAdColonyComponent::AdFinished_Handler);
}

void UAdColonyComponent::OnUnregister()
{
	Super::OnUnregister();

	UAdColonyComponent::AdAvailabilityChangedDelegate.RemoveAll(this);
	UAdColonyComponent::V4VCRewardDelegate.RemoveAll(this);
	UAdColonyComponent::AdStartedDelegate.RemoveAll(this);
	UAdColonyComponent::AdAttemptFinishedDelegate.RemoveAll(this);
	UAdColonyComponent::AdFinishedDelegate.RemoveAll(this);
}

UAdColonyComponent::FAdColonyAdAvailabilityChangedDelegate UAdColonyComponent::AdAvailabilityChangedDelegate;
UAdColonyComponent::FAdColonyV4VCRewardDelegate UAdColonyComponent::V4VCRewardDelegate;
UAdColonyComponent::FAdColonyAdStartedDelegate UAdColonyComponent::AdStartedDelegate;
UAdColonyComponent::FAdColonyAdAttemptFinishedDelegate UAdColonyComponent::AdAttemptFinishedDelegate;
UAdColonyComponent::FAdColonyAdFinishedDelegate UAdColonyComponent::AdFinishedDelegate;
