// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProcGen/Public/TerrainMesh.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTerrainMesh() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	PROCEDURALMESHCOMPONENT_API UClass* Z_Construct_UClass_UProceduralMeshComponent_NoRegister();
	PROCGEN_API UClass* Z_Construct_UClass_ATerrainMesh();
	PROCGEN_API UClass* Z_Construct_UClass_ATerrainMesh_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ProcGen();
// End Cross Module References
	void ATerrainMesh::StaticRegisterNativesATerrainMesh()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATerrainMesh);
	UClass* Z_Construct_UClass_ATerrainMesh_NoRegister()
	{
		return ATerrainMesh::StaticClass();
	}
	struct Z_Construct_UClass_ATerrainMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProceduralMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ProceduralMesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATerrainMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ProcGen,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATerrainMesh_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TerrainMesh.h" },
		{ "ModuleRelativePath", "Public/TerrainMesh.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATerrainMesh_Statics::NewProp_ProceduralMesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TerrainMesh.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATerrainMesh_Statics::NewProp_ProceduralMesh = { "ProceduralMesh", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ATerrainMesh, ProceduralMesh), Z_Construct_UClass_UProceduralMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATerrainMesh_Statics::NewProp_ProceduralMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATerrainMesh_Statics::NewProp_ProceduralMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATerrainMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATerrainMesh_Statics::NewProp_ProceduralMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATerrainMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATerrainMesh>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATerrainMesh_Statics::ClassParams = {
		&ATerrainMesh::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ATerrainMesh_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ATerrainMesh_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATerrainMesh_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATerrainMesh_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATerrainMesh()
	{
		if (!Z_Registration_Info_UClass_ATerrainMesh.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATerrainMesh.OuterSingleton, Z_Construct_UClass_ATerrainMesh_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATerrainMesh.OuterSingleton;
	}
	template<> PROCGEN_API UClass* StaticClass<ATerrainMesh>()
	{
		return ATerrainMesh::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATerrainMesh);
	struct Z_CompiledInDeferFile_FID_HostProject_Plugins_ProcGen_Source_ProcGen_Public_TerrainMesh_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_ProcGen_Source_ProcGen_Public_TerrainMesh_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATerrainMesh, ATerrainMesh::StaticClass, TEXT("ATerrainMesh"), &Z_Registration_Info_UClass_ATerrainMesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATerrainMesh), 1486825092U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_ProcGen_Source_ProcGen_Public_TerrainMesh_h_122918416(TEXT("/Script/ProcGen"),
		Z_CompiledInDeferFile_FID_HostProject_Plugins_ProcGen_Source_ProcGen_Public_TerrainMesh_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_HostProject_Plugins_ProcGen_Source_ProcGen_Public_TerrainMesh_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
