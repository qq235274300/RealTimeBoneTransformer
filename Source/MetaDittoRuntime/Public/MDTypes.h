// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_ModifyBone.h"
#include "MDTypes.generated.h"

/**
 * 
 */



#pragma region SkeletonModifyInfo

// FBoneInfo BoneName BoneIndex Origin
USTRUCT(BlueprintType)
struct METADITTORUNTIME_API FBoneInfo
{
	GENERATED_USTRUCT_BODY()

	FBoneInfo()
		:bIgnoreBone(false)
		, Origin(FVector::ZeroVector)
		, Translation(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, Scale(FVector(1.0f))
		, TranslationMode(BMM_Additive)
		, RotationMode(BMM_Additive)
		, ScaleMode(BMM_Additive)
		, TranslationSpace(BCS_ParentBoneSpace)
		, RotationSpace(BCS_BoneSpace)
		, ScaleSpace(BCS_BoneSpace)
	{
		
	};
	
		FBoneInfo(const FName& InBoneName)
		:BoneRef(FBoneReference())
	    ,BoneName(InBoneName)
	    ,bIgnoreBone(false)
		, Origin(FVector::ZeroVector)
		, Translation(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, Scale(FVector(1.0f))
		, TranslationMode(BMM_Additive)
		, RotationMode(BMM_Additive)
		, ScaleMode(BMM_Additive)
		, TranslationSpace(BCS_ParentBoneSpace)
		, RotationSpace(BCS_BoneSpace)
		, ScaleSpace(BCS_BoneSpace)
	{
		BoneRef.BoneName = InBoneName;
	};

	FBoneInfo(const FName& InBoneName, const int32 InBoneIndex)
		: BoneRef(FBoneReference())
		, BoneName(InBoneName)
		, bIgnoreBone(false)
		, Origin(FVector::ZeroVector)
		, Translation(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, Scale(FVector(1.0f))
		, TranslationMode(BMM_Additive)
		, RotationMode(BMM_Additive)
		, ScaleMode(BMM_Additive)
		, TranslationSpace(BCS_ParentBoneSpace)
		, RotationSpace(BCS_BoneSpace)
		, ScaleSpace(BCS_BoneSpace)
	{
		BoneRef.BoneName = InBoneName;
		BoneRef.BoneIndex = InBoneIndex;
	};

	FBoneInfo(const FName& InBoneName, const int32 InBoneIndex, const FVector InOrigin)
		: BoneRef(FBoneReference())
		, BoneName(InBoneName)
		, bIgnoreBone(false)
		, Origin(InOrigin)
		, Translation(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, Scale(FVector(1.0f))
		, TranslationMode(BMM_Additive)
		, RotationMode(BMM_Additive)
		, ScaleMode(BMM_Additive)
		, TranslationSpace(BCS_ParentBoneSpace)
		, RotationSpace(BCS_BoneSpace)
		, ScaleSpace(BCS_BoneSpace)
	{
		BoneRef.BoneName = InBoneName;
		BoneRef.BoneIndex = InBoneIndex;
	}
	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	FBoneReference BoneRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl)
		FName BoneName;
	UPROPERTY(EditAnywhere, Category = SkeletalControl)
		bool bIgnoreBone;
	
	/***********************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Translation, meta = (PinShownByDefault))
		FVector Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Translation, meta = (PinShownByDefault))
		FVector Translation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta = (PinShownByDefault))
		FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scale, meta = (PinShownByDefault))
		FVector Scale;

	//Add Ignore Replace
	UPROPERTY(EditAnywhere, Category = Translation)
		TEnumAsByte<EBoneModificationMode> TranslationMode;
	UPROPERTY(EditAnywhere, Category = Rotation)
		TEnumAsByte<EBoneModificationMode> RotationMode;
	UPROPERTY(EditAnywhere, Category = Scale)
		TEnumAsByte<EBoneModificationMode> ScaleMode;
	//Bone(Local),Parent,Component,World
	UPROPERTY(EditAnywhere, Category = Translation)
		TEnumAsByte<enum EBoneControlSpace> TranslationSpace;
	UPROPERTY(EditAnywhere, Category = Rotation)
		TEnumAsByte<enum EBoneControlSpace> RotationSpace;
	UPROPERTY(EditAnywhere, Category = Scale)
		TEnumAsByte<enum EBoneControlSpace> ScaleSpace;
};

//存在对应 数组目前看起来 毫无用处
USTRUCT(BlueprintType)
struct METADITTORUNTIME_API FSkeletonInfo
{
	GENERATED_BODY()

		FSkeletonInfo() {}

	FSkeletonInfo(TArray<FBoneInfo> InBoneArray)
	{
		for (int32 i = 0; i < InBoneArray.Num(); ++i)
		{
			BoneInfoArray.Add(InBoneArray[i]);
			BoneIndicesMap.Add(InBoneArray[i].BoneName) = InBoneArray[i].BoneRef.BoneIndex;
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MetaDittoRuntime)
		TArray<FBoneInfo> BoneInfoArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MetaDittoRuntime)
		TMap<FName, int32> BoneIndicesMap;


};


#pragma endregion


UCLASS(Blueprintable)
class METADITTORUNTIME_API UMDPropertyObject : public UObject
{
	GENERATED_BODY()

public:
	UMDPropertyObject();

public:
	
	UFUNCTION(BlueprintPure, Category = MetaDittoRuntime)
		int32 GetBoneIndexByName(const FSkeletonInfo& SkeletonInfo,const FName& Name)const;
	UFUNCTION(BlueprintPure, Category = MetaDittoRuntime)
		void GetBoneInfoByIndex(const FSkeletonInfo& SkeletonInfo, int32 BoneIndex, FBoneInfo& OutBoneInfo)const;
	UFUNCTION(BlueprintPure, Category = MetaDittoRuntime)
		void GetBoneInfoByName(const FSkeletonInfo& SkeletonInfo, FName BoneName, FBoneInfo& OutBoneInfo)const;

	UFUNCTION(BlueprintCallable, Category = MetaDittoRuntime)
		FSkeletonInfo SetBoneInfoByIndex( FSkeletonInfo& SkeletonInfo, int32 BoneIndex, FBoneInfo BoneInfo);
	UFUNCTION(BlueprintCallable, Category = MetaDittoRuntime)
		FSkeletonInfo SetBoneInfoByName(FSkeletonInfo& SkeletonInfo, FBoneInfo BoneInfo);


	void SetPropertyValue(float value);

public:
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = MetaDittoRuntime)
		void GetPropertyName(FName& Name);
	virtual void GetPropertyName_Implementation(FName& Name);

	UFUNCTION(BlueprintNativeEvent, Category = MetaDittoRuntime)
		void PropertyProcess(FSkeletonInfo InSkeletonInfo, FSkeletonInfo& OutSkeletonInfo);
	virtual void PropertyProcess_Implementation(FSkeletonInfo InSkeletonInfo, FSkeletonInfo& OutSkeletonInfo);
	
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		float PropertyValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		FName PropertyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		FSkeletonInfo PropertyInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MetaDittoRuntime)
		int32 PropertyIndex;

};


UCLASS()
class METADITTORUNTIME_API UMDTypes : public UObject
{
	GENERATED_BODY()
	
};
