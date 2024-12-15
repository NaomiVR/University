#include "FileHandler.h"
#include "VarContainer.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"

/* #include <shlobj_core.h>

#if PLATFORM_WINDOWS
	#include "Windows/AllowWindowsPlatformTypes.h"
#endif*/


// Dialogue context finders

void FFileHandler::DialogueContextCTM() const
{
	/*FString DownloadsFolder;

	#if PLATFORM_WINDOWS
		TCHAR Path[MAX_PATH];
		SHGetFolderPath(nullptr, CSIDL_MYDOCUMENTS, nullptr, SHGFP_TYPE_CURRENT, Path);
		DownloadsFolder = FPaths::Combine(Path, TEXT("Downloads"));
	#elif PLATFORM_MAC || PLATFORM_LINUX
		FString HomeDir = FPlatformMisc::GetEnvironmentVariable(TEXT("HOME"));
		DownloadsFolder = FPaths::Combine(*HomeDir, TEXT("Downloads"));
	#endif

	const FString FileName = TEXT("CustomMesh.ctm");
	FString FullPath = FPaths::Combine(*DownloadsFolder, *FileName);*/

	FString FileName = TEXT("CustomMesh.ctm");
	FString FullPath = FPaths::Combine(FPaths::ProjectDir(), FileName);
	UE_LOG(LogTemp, Log, TEXT("File saved at %s"), *FullPath);
	CTMSave(FullPath);
}

void FFileHandler::DialogueContextFBX() const
{
	
}

void FFileHandler::DialogueContextOBJ() const
{
	
}


// Savers

void FFileHandler::CTMSave(const FString& FileName) const
{
	FBufferArchive ToBinary;

	FString FileIdentifier = TEXT("CTM");
	ToBinary << FileIdentifier;

	int32 NumVertices = FVarContainer::GetInstance()->GetTerrainMeshInstance()->Vertices.Num();
	int32 NumTriangles = FVarContainer::GetInstance()->GetTerrainMeshInstance()->Triangles.Num();
	ToBinary << NumVertices;
	ToBinary << NumTriangles;

	FString VerticesDescriptor = TEXT("Vertices");
	ToBinary << VerticesDescriptor;
	ToBinary << FVarContainer::GetInstance()->GetTerrainMeshInstance()->Vertices;

	FString TrianglesDescriptor = TEXT("Triangles");
	ToBinary << TrianglesDescriptor;
	ToBinary << FVarContainer::GetInstance()->GetTerrainMeshInstance()-> Triangles;

	FString ColoursDescriptor = TEXT("Colours");
	ToBinary << ColoursDescriptor;
	ToBinary << FVarContainer::GetInstance()->GetTerrainMeshInstance()->Colours;

	FFileHelper::SaveArrayToFile(ToBinary, *FileName);

	ToBinary.FlushCache();
	ToBinary.Empty();
}

void FFileHandler::FBXSave() const
{
	// https://code.blender.org/2013/08/fbx-binary-file-format-specification/
}

void FFileHandler::OBJSave() const
{
	// https://paulbourke.net/dataformats/obj/
}


// Loaders

void FFileHandler::CTMLoad() const
{
	TArray<uint8> BinaryArray;
	FMemoryReader FromBinary = FMemoryReader(BinaryArray, true);
	FromBinary.Seek(0);

	FString FileIdentifier;
	FromBinary << FileIdentifier;

	if (FileIdentifier != TEXT("CTM"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid file format"));
		return;
	}

	/*int32 NumVertices;
	int32 NumTriangles;
	FromBinary << NumVertices;
	FromBinary << NumTriangles;

	FString VerticesDescriptor;
	FromBinary << VerticesDescriptor;
	Vertices.SetNumUninitialized(NumVertices);
	FromBinary.Serialize(Vertices.GetData(), NumVertices * sizeof(FVector));

	FString TrianglesDescriptor;
	FromBinary << TrianglesDescriptor;
	Triangles.SetNumUninitialized(NumTriangles);
	FromBinary.Serialize(Triangles.GetData(), NumTriangles * sizeof(int32));

	FString ColoursDescriptor;
	FromBinary << ColoursDescriptor;
	Colours.SetNumUninitialized(NumVertices);
	FromBinary.Serialize(Colours.GetData(), NumVertices * sizeof(FLinearColor));

	FromBinary.FlushCache();
	BinaryArray.Empty();
	FromBinary.Close();*/
}

void FFileHandler::FBXLoad() const
{
	
}

void FFileHandler::OBJLoad() const
{
	
}

