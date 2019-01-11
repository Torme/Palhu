// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PALHU_PalhuPawn_generated_h
#error "PalhuPawn.generated.h already included, missing '#pragma once' in PalhuPawn.h"
#endif
#define PALHU_PalhuPawn_generated_h

#define Palhu_Source_Palhu_PalhuPawn_h_17_RPC_WRAPPERS
#define Palhu_Source_Palhu_PalhuPawn_h_17_RPC_WRAPPERS_NO_PURE_DECLS
#define Palhu_Source_Palhu_PalhuPawn_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPalhuPawn(); \
	friend struct Z_Construct_UClass_APalhuPawn_Statics; \
public: \
	DECLARE_CLASS(APalhuPawn, AWheeledVehicle, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Palhu"), NO_API) \
	DECLARE_SERIALIZER(APalhuPawn)


#define Palhu_Source_Palhu_PalhuPawn_h_17_INCLASS \
private: \
	static void StaticRegisterNativesAPalhuPawn(); \
	friend struct Z_Construct_UClass_APalhuPawn_Statics; \
public: \
	DECLARE_CLASS(APalhuPawn, AWheeledVehicle, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Palhu"), NO_API) \
	DECLARE_SERIALIZER(APalhuPawn)


#define Palhu_Source_Palhu_PalhuPawn_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APalhuPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APalhuPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APalhuPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APalhuPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APalhuPawn(APalhuPawn&&); \
	NO_API APalhuPawn(const APalhuPawn&); \
public:


#define Palhu_Source_Palhu_PalhuPawn_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APalhuPawn(APalhuPawn&&); \
	NO_API APalhuPawn(const APalhuPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APalhuPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APalhuPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APalhuPawn)


#define Palhu_Source_Palhu_PalhuPawn_h_17_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SpringArm() { return STRUCT_OFFSET(APalhuPawn, SpringArm); } \
	FORCEINLINE static uint32 __PPO__Camera() { return STRUCT_OFFSET(APalhuPawn, Camera); } \
	FORCEINLINE static uint32 __PPO__InternalCameraBase() { return STRUCT_OFFSET(APalhuPawn, InternalCameraBase); } \
	FORCEINLINE static uint32 __PPO__InternalCamera() { return STRUCT_OFFSET(APalhuPawn, InternalCamera); } \
	FORCEINLINE static uint32 __PPO__InCarSpeed() { return STRUCT_OFFSET(APalhuPawn, InCarSpeed); } \
	FORCEINLINE static uint32 __PPO__InCarGear() { return STRUCT_OFFSET(APalhuPawn, InCarGear); }


#define Palhu_Source_Palhu_PalhuPawn_h_14_PROLOG
#define Palhu_Source_Palhu_PalhuPawn_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Palhu_Source_Palhu_PalhuPawn_h_17_PRIVATE_PROPERTY_OFFSET \
	Palhu_Source_Palhu_PalhuPawn_h_17_RPC_WRAPPERS \
	Palhu_Source_Palhu_PalhuPawn_h_17_INCLASS \
	Palhu_Source_Palhu_PalhuPawn_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Palhu_Source_Palhu_PalhuPawn_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Palhu_Source_Palhu_PalhuPawn_h_17_PRIVATE_PROPERTY_OFFSET \
	Palhu_Source_Palhu_PalhuPawn_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	Palhu_Source_Palhu_PalhuPawn_h_17_INCLASS_NO_PURE_DECLS \
	Palhu_Source_Palhu_PalhuPawn_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Palhu_Source_Palhu_PalhuPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
