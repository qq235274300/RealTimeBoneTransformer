// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNode_MetaTransformBone.h"
#include "Runtime/Engine/Public/AnimationRuntime.h"
#include "Runtime/Engine/Public/Animation/AnimInstanceProxy.h"



void FAnimNode_MetaTransformBone::GatherDebugData(FNodeDebugData& DebugData)
{
    //Commd ShowDebug Animation
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(GatherDebugData)
    FString DebugLine = DebugData.GetNodeName(this);
    DebugLine += "(";
    AddDebugNodeData(DebugLine);
    //DebugLine += FString::Printf(TEXT(" Target: %s)"), *SkeletonData.BoneToModify.BoneName.ToString());
    ComponentPose.GatherDebugData(DebugData);
}
//operates in ComponentSpace
void FAnimNode_MetaTransformBone::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(EvaluateSkeletalControl_AnyThread)
    //SCOPE_CYCLE_COUNTER(STAT_MetaTransformBone_Eval);
    
    check(OutBoneTransforms.Num() == 0);
   const FBoneContainer& BoneContainer =  Output.Pose.GetPose().GetBoneContainer();
    
    if(bUseCustomBoneData)
    {
        for(int32 i = 0; i< BoneInfoArray.Num(); ++i)
        {
            BoneInfoArray[i].BoneRef.BoneName = BoneInfoArray[i].BoneName;
            BoneInfoArray[i].BoneRef.Initialize(BoneContainer);
            int32 CurBoneIndex = BoneInfoArray[i].BoneRef.BoneIndex;
           // FBoneInfo CurBoneInfo = FBoneInfo{BoneInfoArray[i].BoneName,CurBoneIndex};
            FCompactPoseBoneIndex CompactPoseBoneToModify = FCompactPoseBoneIndex(CurBoneIndex);
            if(CompactPoseBoneToModify == INDEX_NONE)
            {
                continue;
            }
            FTransform NewBoneTM = Output.Pose.GetComponentSpaceTransform(CompactPoseBoneToModify);
            FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

            if (BoneInfoArray[i].ScaleMode != BMM_Ignore)
            {
                FVector Scale = BoneInfoArray[i].Scale;
                FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, BoneInfoArray[i].ScaleSpace);
                BoneInfoArray[i].ScaleMode == BMM_Additive ? NewBoneTM.SetScale3D(NewBoneTM.GetScale3D() * Scale) : NewBoneTM.SetScale3D(Scale);
                FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, BoneInfoArray[i].ScaleSpace);
            }

            if (BoneInfoArray[i].RotationMode != BMM_Ignore)
            {
                FRotator Rotation =  BoneInfoArray[i].Rotation;
                const FQuat BoneQuat(Rotation);
                FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, BoneInfoArray[i].RotationSpace);
                BoneInfoArray[i].RotationMode == BMM_Additive ? NewBoneTM.SetRotation(BoneQuat * NewBoneTM.GetRotation()) : NewBoneTM.SetRotation(BoneQuat);
                FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, BoneInfoArray[i].RotationSpace);
            }
            
            if (BoneInfoArray[i].TranslationMode != BMM_Ignore)
            {
                FVector Translation =  BoneInfoArray[i].Translation;
                FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, BoneInfoArray[i].TranslationSpace);
                BoneInfoArray[i].TranslationMode == BMM_Additive ? NewBoneTM.AddToTranslation(Translation) : NewBoneTM.SetTranslation(Translation);
                FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, NewBoneTM, CompactPoseBoneToModify, BoneInfoArray[i].TranslationSpace);
            }
            
            Output.Pose.SetComponentSpaceTransform(CompactPoseBoneToModify, NewBoneTM);
            OutBoneTransforms.Add(FBoneTransform(CompactPoseBoneToModify, NewBoneTM));

            OutBoneTransforms.Sort(FCompareBoneTransformIndex());
        }
        
        
    }


    //We Can Do
  
    
}

bool FAnimNode_MetaTransformBone::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
    //runs every single frame  ,don’t do any calculation or anything here,imple check that everything on the node is correct, valid, and can be evaluated
    return true;

    if (ChainStart.IsValidToEvaluate() && ScaleCurve != nullptr && ScaleCurve->FloatCurve.GetNumKeys() > 0)
    {
        return true;
    }
    return false;
}

void FAnimNode_MetaTransformBone::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
    //only runs once when a mesh LOD is initialized
    DECLARE_SCOPE_HIERARCHICAL_COUNTER_ANIMNODE(InitializeBoneReferences)
    for(int32 i = 0; i< BoneInfoArray.Num(); ++i)
    {
        BoneInfoArray[i].BoneRef.Initialize(RequiredBones);
    }
    //初始化
    ChainStart.Initialize(RequiredBones);

    if (ChainStart.IsValidToEvaluate())
    {
        const FReferenceSkeleton ReferenceSkeleton = RequiredBones.GetReferenceSkeleton();
        for (int16 boneInd = 0 ; boneInd < ReferenceSkeleton.GetNum() ; boneInd++)
        {
            FBoneReference childBoneRef = FBoneReference(ReferenceSkeleton.GetBoneName(boneInd));
            if(childBoneRef.Initialize(RequiredBones))
            {
                const int32 boneDepth = ReferenceSkeleton.GetDepthBetweenBones(childBoneRef.BoneIndex, ChainStart.BoneIndex);
                if (boneDepth >= 0)
                {
                    foundMaxDepth = boneDepth > foundMaxDepth ? boneDepth : foundMaxDepth;
                    BoneRefDepthBuckets.Add(FBoneReferenceDepth(childBoneRef, boneDepth));
                }
            }
        }

        effectiveMaxDepth = MaximumDepth == -1 ? foundMaxDepth : FMath::Min(MaximumDepth, foundMaxDepth);
    }
    
}
