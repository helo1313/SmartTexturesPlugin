// Copyright Epic Games, Inc. All Rights Reserved.

#include "SmartTexturesNodesBPLibrary.h"
#include "SmartTexturesNodes.h"

USmartTexturesNodesBPLibrary::USmartTexturesNodesBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float USmartTexturesNodesBPLibrary::SmartTexturesNodesSampleFunction(float Param)
{
	return -1;
}

void USmartTexturesNodesBPLibrary::GetTextureSize(UTexture2D* Texture2D, int32& TextureWidth, int32& TextureHeight)
{
	TextureHeight = 0;
	TextureWidth = 0;
	
	if (Texture2D != nullptr)
	{
		FTexture2DMipMap& Mip0 = Texture2D->PlatformData->Mips[0];

		int32 Width = Mip0.SizeX;
		int32 Height = Mip0.SizeY;

		TextureHeight = Height;
		TextureWidth = Width;
	}
	else
	{
		UE_LOG(LogBlueprintUserMessages, Error, TEXT("Texture 2D is set as null"));
	}
}

