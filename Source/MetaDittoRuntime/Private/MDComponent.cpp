// Fill out your copyright notice in the Description page of Project Settings.


#include "MDComponent.h"
#include "MetaTypes.h"
#include "GameFramework/Character.h"


PRAGMA_DISABLE_OPTIMIZATION
// Sets default values for this component's properties
UMDComponent::UMDComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMDComponent::BeginPlay()
{
	Super::BeginPlay();
	GetCurrentBoneInfoArray();
	// ...
	
}


// Called every frame
void UMDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMDComponent::SetSkeletalMesh(USkeletalMeshComponent* SkeletalMesh)
{
	if (SkeletalMesh == nullptr)
	{
		return;
	}
	CurrentSkelMesh = SkeletalMesh;
	MDBoneObjects.Empty();
	for (auto& BoneObjectClass : MDBoneObjectClasses)
	{
		if (BoneObjectClass != nullptr)
		{
			MDBoneObjects.Add(NewObject<UMDBoneObject>(this, BoneObjectClass));
		}
	}
	SSCHelper::Debug()<<"Add->"<<MDBoneObjectClasses.Num()<<"->MDObjects"<<SSCHelper::Endl();
	
	int32 BoneNums = CurrentSkelMesh->GetNumBones();
	SSCHelper::Debug()<<"Bone Nums ->"<<BoneNums<<SSCHelper::Endl();
	
	for (int32 i = 0; i < BoneNums; ++i)
	{
		FName CurrentBoneName = CurrentSkelMesh->GetBoneName(i);
		FVector Origin = FVector::ZeroVector;

		//Not Root
		if(CurrentSkelMesh->GetBoneIndex(CurrentBoneName) >= 0)
		{
			FName ParentName = CurrentSkelMesh->GetParentBone(CurrentBoneName);
			 Origin = 
			CurrentSkelMesh->GetBoneQuaternion(CurrentBoneName,EBoneSpaces::ComponentSpace).UnrotateVector(
			CurrentSkelMesh->GetBoneLocation(CurrentBoneName,EBoneSpaces::ComponentSpace) - CurrentSkelMesh->GetBoneLocation(ParentName,EBoneSpaces::ComponentSpace)
			);
		}

		int32 CurrentBoneIndex = CurrentSkelMesh->GetBoneIndex(CurrentBoneName);

		BoneInfoArray.Add(FBoneInfo(CurrentBoneName,CurrentBoneIndex,Origin));
		
		//if(CurrentSkelMesh->GetParentBone)
		
	}
	
}

FBoneInfo UMDComponent::GetBoneInfoByName(FName BoneName)
{
	if(BoneInfoArray.Num() > 0)
	{
		for(int32 i = 0;i< BoneInfoArray.Num(); ++i)
		{
			if(BoneInfoArray[i].BoneName == BoneName)
			{
				return BoneInfoArray[i];
			}
		}
	}
	return  FBoneInfo();
}

TArray<FMeshBoneInfo> UMDComponent::GetCurrentBoneInfoArray()
{
	//可能这是固定pose 的骨骼信息
	CurrentSkelMesh = Cast<ACharacter>(GetOwner())->GetMesh();
	
	TArray<FMeshBoneInfo> BoneInfoArray1;
	if(CurrentSkelMesh)
	{
		USkeletalMesh* SkeletonMesh = CurrentSkelMesh->SkeletalMesh;
		USkeleton* Skeleton = SkeletonMesh->GetSkeleton();
		BoneInfoArray1 = Skeleton->GetReferenceSkeleton().GetRefBoneInfo();
	}

	return BoneInfoArray1;
}

PRAGMA_ENABLE_OPTIMIZATION