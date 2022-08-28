// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimGraphNode_MetaTransformBone.h"
#include "Runtime/Engine/Public/AnimationRuntime.h"

UAnimGraphNode_MetaTransformBone::UAnimGraphNode_MetaTransformBone(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 
}

 FText UAnimGraphNode_MetaTransformBone::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
 FString Result = GetControllerDescription().ToString();
 Result += (TitleType == ENodeTitleType::ListView) ? TEXT("") : TEXT("\n");
 return FText::FromString(Result);
}

 FLinearColor UAnimGraphNode_MetaTransformBone::GetNodeTitleColor() const
{
 return FLinearColor(12, 0, 12, 1);
}

 FString UAnimGraphNode_MetaTransformBone::GetNodeCategory() const
{
 return FString(TEXT("MetaDitto"));
}

 const FAnimNode_SkeletalControlBase* UAnimGraphNode_MetaTransformBone::GetNode() const
{
	return &Node;
}

 FText UAnimGraphNode_MetaTransformBone::GetTooltipText() const
{
 return FText::FromString(FString(TEXT(" RealTime  Modified All Bones Transforms in Referenced SkeletalMesh ")));
}

void UAnimGraphNode_MetaTransformBone::Draw(FPrimitiveDrawInterface* PDI,
 USkeletalMeshComponent* previewSkelMeshComp) const
{
 Super::Draw(PDI, previewSkelMeshComp);
}

FText UAnimGraphNode_MetaTransformBone::GetControllerDescription() const
{
 return FText::FromString(FString(TEXT("MetaDitto")));
}
