// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Palhu/PalhuGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePalhuGameMode() {}
// Cross Module References
	PALHU_API UClass* Z_Construct_UClass_APalhuGameMode_NoRegister();
	PALHU_API UClass* Z_Construct_UClass_APalhuGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Palhu();
// End Cross Module References
	void APalhuGameMode::StaticRegisterNativesAPalhuGameMode()
	{
	}
	UClass* Z_Construct_UClass_APalhuGameMode_NoRegister()
	{
		return APalhuGameMode::StaticClass();
	}
	struct Z_Construct_UClass_APalhuGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APalhuGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Palhu,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APalhuGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "PalhuGameMode.h" },
		{ "ModuleRelativePath", "PalhuGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APalhuGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APalhuGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APalhuGameMode_Statics::ClassParams = {
		&APalhuGameMode::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x008802A8u,
		nullptr, 0,
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_APalhuGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_APalhuGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APalhuGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APalhuGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APalhuGameMode, 2891579989);
	static FCompiledInDefer Z_CompiledInDefer_UClass_APalhuGameMode(Z_Construct_UClass_APalhuGameMode, &APalhuGameMode::StaticClass, TEXT("/Script/Palhu"), TEXT("APalhuGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APalhuGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
