// Copyright (C) 2024 owoDra

#pragma once

#include "Logging/LogMacros.h"

GESADDON_API DECLARE_LOG_CATEGORY_EXTERN(LogGESA, Log, All);

#if !UE_BUILD_SHIPPING

#define GESALOG(FormattedText, ...) UE_LOG(LogGESA, Log, FormattedText, __VA_ARGS__)

#define GESAENSURE(InExpression) ensure(InExpression)
#define GESAENSURE_MSG(InExpression, InFormat, ...) ensureMsgf(InExpression, InFormat, __VA_ARGS__)
#define GESAENSURE_ALWAYS_MSG(InExpression, InFormat, ...) ensureAlwaysMsgf(InExpression, InFormat, __VA_ARGS__)

#define GESACHECK(InExpression) check(InExpression)
#define GESACHECK_MSG(InExpression, InFormat, ...) checkf(InExpression, InFormat, __VA_ARGS__)

#else

#define GESALOG(FormattedText, ...)

#define GESAENSURE(InExpression) InExpression
#define GESAENSURE_MSG(InExpression, InFormat, ...) InExpression
#define GESAENSURE_ALWAYS_MSG(InExpression, InFormat, ...) InExpression

#define GESACHECK(InExpression) InExpression
#define GESACHECK_MSG(InExpression, InFormat, ...) InExpression

#endif