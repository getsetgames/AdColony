//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#include "AdColonyPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogAdColony);

#define LOCTEXT_NAMESPACE "AdColony"

class FAdColony : public IAdColony
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FAdColony, AdColony )

void FAdColony::StartupModule()
{

}


void FAdColony::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
