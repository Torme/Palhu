// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Palhu/PalhuWheelRear.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePalhuWheelRear() {}
// Cross Module References
	PALHU_API UClass* Z_Construct_UClass_UPalhuWheelRear_NoRegister();
	PALHU_API UClass* Z_Construct_UClass_UPalhuWheelRear();
	PHYSXVEHICLES_API UClass* Z_Construct_UClass_UVehicleWheel();
	UPackage* Z_Construct_UPackage__Script_Palhu();
// End Cross Module References
	void UPalhuWheelRear::StaticRegisterNativesUPalhuWheelRear()
	{
	}
	UClass* Z_Construct_UClass_UPalhuWheelRear_NoRegister()
	{
		return UPalhuWheelRear::StaticClass();
	}
	struct Z_Construct_UClass_UPalhuWheelRear_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPalhuWheelRear_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UVehicleWheel,
		(UObject* (*)())Z_Construct_UPackage__Script_Palhu,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPalhuWheelRear_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "PalhuWheelRear.h" },
		{ "ModuleRelativePath", "PalhuWheelRear.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPalhuWheelRear_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPalhuWheelRear>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UPalhuWheelRear_Statics::ClassParams = {
		&UPalhuWheelRear::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x008000A0u,
		nullptr, 0,
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_UPalhuWheelRear_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UPalhuWheelRear_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPalhuWheelRear()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UPalhuWheelRear_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UPalhuWheelRear, 2378110427);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UPalhuWheelRear(Z_Construct_UClass_UPalhuWheelRear, &UPalhuWheelRear::StaticClass, TEXT("/Script/Palhu"), TEXT("UPalhuWheelRear"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPalhuWheelRear);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
