// Copyright 2026 Simulated Flow All Rights Reserved.

#include "SquadFormation.h"
#include "SquadFormationLog.h"

DEFINE_LOG_CATEGORY(LogSquadFormation);

#define LOCTEXT_NAMESPACE "FSquadFormationModule"

void FSquadFormationModule::StartupModule()
{
	UE_LOG(LogSquadFormation, Log, TEXT("SquadFormation started."));
}

void FSquadFormationModule::ShutdownModule()
{
	UE_LOG(LogSquadFormation, Log, TEXT("SquadFormation shut down."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSquadFormationModule, SquadFormation)
