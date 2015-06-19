//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "ModuleManager.h"

class IAdColony : public IModuleInterface
{

public:

	static inline IAdColony& Get()
	{
		return FModuleManager::LoadModuleChecked< IAdColony >( "AdColony" );
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "AdColony" );
	}
};

