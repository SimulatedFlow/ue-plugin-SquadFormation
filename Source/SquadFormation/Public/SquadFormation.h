// Copyright 2026 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

/** SquadFormation — AI group movement & formation steering (runtime module). */
class FSquadFormationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
