// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(AKP, Log, All);
#define AKPLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define AKPLOG_S(Verbose) UE_LOG(AKP, Verbose, TEXT("%s"), *AKPLOG_CALLINFO)
#define AKPLOG(Verbose, Format , ...) UE_LOG(AKP, Verbose , TEXT("%s%s"), *AKPLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define AKPCHECK(Expr, ...) { if(!(Expr)) {AKPLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }}