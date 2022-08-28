// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "MDTypes.h"
#include "MDBoneObject.h"

#include "MDComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METADITTORUNTIME_API UMDComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMDComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UFUNCTION(BlueprintCallable)
	void SetSkeletalMesh(USkeletalMeshComponent* SkeletalMesh);
	UFUNCTION(BlueprintCallable)
	FBoneInfo GetBoneInfoByName(FName BoneName);

public:
	TArray<FMeshBoneInfo> GetCurrentBoneInfoArray();

	UPROPERTY()
	bool bUseSpecificBone = false;

private:
	UPROPERTY()
	USkeletalMeshComponent* CurrentSkelMesh;

	UPROPERTY()
	 FSkeletonInfo SkeletonInfo;

	UPROPERTY(EditAnywhere)
	TArray<FBoneInfo> BoneInfoArray;

	UPROPERTY()
		TArray<UMDBoneObject*> MDBoneObjects;

	UPROPERTY()
		TArray<TSubclassOf<UMDBoneObject>> MDBoneObjectClasses;
		
		
};
