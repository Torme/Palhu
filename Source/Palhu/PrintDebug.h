// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"

#define print(text)                         if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue, TEXT(text))
#define printc(channel, text)               if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Blue, TEXT(text))
#define printf(format, ...)                 if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue, FString::Printf(TEXT(format), ##__VA_ARGS__))
#define printcf(channel, format, ...)       if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Blue, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printwarn(text)                     if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, TEXT(text))
#define printcwarn(channel, text)           if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Yellow, TEXT(text))
#define printfwarn(format, ...)             if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__))
#define printcfwarn(channel, format, ...)   if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printerr(text)                      if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, TEXT(text))
#define printcerr(channel, text)            if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Red, TEXT(text))
#define printferr(format, ...)              if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__))
#define printcferr(channel, format, ...)    if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__))

#define printfloat(variable)                if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable))
#define printcfloat(channel, variable)      if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable))

#define printvector(variable)               if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()))
#define printcvector(channel, variable)     if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 20, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()))

class PALHU_API PrintDebug
{
public:
	PrintDebug();
	~PrintDebug();
};
