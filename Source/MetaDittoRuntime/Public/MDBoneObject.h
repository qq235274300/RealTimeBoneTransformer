// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MDBoneObject.generated.h"

/**
 * 
 */
UCLASS()
class METADITTORUNTIME_API UMDBoneObject : public UObject
{
	GENERATED_BODY()

public: 
	UMDBoneObject();
public:
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		FName BoneName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		int32 BoneIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		float BoneScaleValue = 0.5f;


};
