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
		UE_LOG(LogBlueprintUserMessages, Error, TEXT("Texture 2D is set as nullptr"));
	}
}

void USmartTexturesNodesBPLibrary::GetTexturePixelsAtPoint(UTexture2D* Texture2D, int32 StartX, int32 StartY,
	int32 PixelsOnXAxis, int32 PixelsOnYAxis, TArray<FColor>& Pixels, int32& TextureWidth, int32& TextureHeight)
{

	//Set Default values
	TextureHeight = 0;
	TextureWidth = 0;
	Pixels = TArray<FColor>();

	//Check for texture = null
	if (Texture2D == nullptr)
	{
		UE_LOG(LogBlueprintUserMessages, Error, TEXT("Texture 2D is set as nullptr"));
		return;
	}

	//Get X and Y of the texture size
	FTexture2DMipMap& Mip0 = Texture2D->PlatformData->Mips[0];

	TextureWidth = Mip0.SizeX;
	TextureHeight = Mip0.SizeY;

	//Get Bulk data of the texture 
	auto Mip0Data = &Mip0.BulkData;
	if(Mip0Data == nullptr)
	{
		return;
	}

	//Get pixels from the texture and lock the texture in the thread that other things cant access it
	void* Mip0Pixels_ = Mip0Data->Lock(LOCK_READ_ONLY);
	FColor* Mip0Pixels = static_cast<FColor*>(Mip0Pixels_);
	if(Mip0Pixels == nullptr)
	{
		Mip0Data->Unlock();
		return;
	}

	//Set output pixel array size
	int32 TotalPixelsArrayLenght;
	TotalPixelsArrayLenght = PixelsOnXAxis * PixelsOnYAxis;
	Pixels.SetNum(TotalPixelsArrayLenght);

	//Main loop for getting correct pixels from the bulk data
	for(int32 i = 0; i < TotalPixelsArrayLenght; i++)
	{
		int32 PixelToRead = 0;
		Pixels[i] = Mip0Pixels[PixelToRead];
	}
	Mip0Data->Unlock();
}
