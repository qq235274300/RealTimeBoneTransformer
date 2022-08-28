// Fill out your copyright notice in the Description page of Project Settings.


#include "MDTypes.h"

UMDPropertyObject::UMDPropertyObject():
	PropertyValue(0.5f),
	PropertyName(NAME_None),
	PropertyIndex(INDEX_NONE)
{
}

int32 UMDPropertyObject::GetBoneIndexByName(const FSkeletonInfo& SkeletonInfo, const FName& Name)const
{
	if (Name != NAME_None)
	{
		const int32* IndexPtr = SkeletonInfo.BoneIndicesMap.Find(Name);
		if (IndexPtr) {

			return *IndexPtr;
		} 
	}

	return INDEX_NONE;
}

void UMDPropertyObject::GetBoneInfoByIndex(const FSkeletonInfo& SkeletonInfo, int32 BoneIndex, FBoneInfo& OutBoneInfo)const
{
	if (SkeletonInfo.BoneInfoArray.IsValidIndex(BoneIndex))
	{
		OutBoneInfo = SkeletonInfo.BoneInfoArray[BoneIndex];
	}
}

void UMDPropertyObject::GetBoneInfoByName(const FSkeletonInfo& SkeletonInfo, FName BoneName, FBoneInfo& OutBoneInfo) const
{
	GetBoneInfoByIndex(SkeletonInfo, GetBoneIndexByName(SkeletonInfo, BoneName), OutBoneInfo);
}

FSkeletonInfo UMDPropertyObject::SetBoneInfoByIndex(FSkeletonInfo& SkeletonInfo, int32 BoneIndex, FBoneInfo BoneInfo)
{
	if (SkeletonInfo.BoneInfoArray.IsValidIndex(BoneIndex))
	{
		SkeletonInfo.BoneInfoArray[BoneIndex] = BoneInfo;
	}

	return SkeletonInfo;
}

FSkeletonInfo UMDPropertyObject::SetBoneInfoByName(FSkeletonInfo& SkeletonInfo, FBoneInfo BoneInfo)
{
	return SetBoneInfoByIndex(SkeletonInfo, GetBoneIndexByName(SkeletonInfo, BoneInfo.BoneName), BoneInfo);
}

void UMDPropertyObject::SetPropertyValue(float value)
{
	PropertyValue = value;
}

void UMDPropertyObject::GetPropertyName_Implementation(FName& Name)
{
	Name = FName(TEXT("DefaultName"));
}

void UMDPropertyObject::PropertyProcess_Implementation(FSkeletonInfo InSkeletonInfo, FSkeletonInfo& OutSkeletonInfo)
{
}
