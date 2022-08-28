// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "Runtime/Engine/Classes/Animation/AnimNodeBase.h"
#include "Runtime/Engine/Classes/Animation/InputScaleBias.h"
#include "MDComponent.h"

#include "AnimNode_MetaTransformBone.generated.h"


USTRUCT()
struct FBoneReferenceDepth
{
	GENERATED_BODY()

	FBoneReference BoneReference;

	int32 BoneDepth;

	FBoneReferenceDepth()
	{
		BoneReference = FBoneReference();
		BoneDepth = -1;
	}

	FBoneReferenceDepth(const FBoneReference& boneReference, const int32 boneDepth)
	{
		BoneReference = boneReference;
		BoneDepth = boneDepth;
	}
};

USTRUCT()
struct FAxisMask
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool MaskX;

	UPROPERTY(EditAnywhere)
	bool MaskY;

	UPROPERTY(EditAnywhere)
	bool MaskZ;

	FAxisMask()
	{
		MaskX = false;
		MaskY = false;
		MaskZ = false;
	}
};

/**
 * 
 */
//BoneContainer has FBoneReference contain the name of the bone, its absolute (skeleton) index, its CompactPoseIndex

USTRUCT(BlueprintInternalUseOnly)
struct METADITTORUNTIME_API FAnimNode_MetaTransformBone : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MetaDittoNode,meta = (PinShownByDefault))
	TArray<FBoneInfo> BoneInfoArray;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MetaDittoNode, meta = (PinShownByDefault))
	// UMDComponent* MDComponent;
	
private:
	bool bUseCustomBoneData = true;
public:
	//Initialize_AnyThread 各种数值进行Initialize 函数只会在编译时，游戏启动时和LOD改变时被调用
	//CacheBones_AnyThread  缓存输入姿态
	//InitializeBoneReferences  操作目标骨骼
	//IsValidToEvaluate  在Mesh的LOD改变或初始化的时候执行, FBoneReference::Initialize(RequiredBones);后我们的FBoneReference里面就会保存有接下来在进行操作时需要的Index;
	//主要是可以对即将操作的Bone检查有没有拿到它的CompactIndex(使用IsValidToExecute进行检查)，或者检查必要的用户输入是否合法
	
	//Update_AnyThread 
	//EvaluateSkeletalControl_AnyThread FComponentSpacePoseContext& Output提供了可以用于获取当前骨骼的Transform或层级结构的方法
	//Array<FBoneTransform>& OutBoneTransforms则是一个空数组，它的值类型FBoneTransform标注了一个骨骼的Index和新的Transform，
	//在每个动画节点执行结束后，如果这个数组有值，那引擎就会根据Alpha将这个新值与对应index的骨骼进行混合
	//初始化  判断 计算 骨骼修改流程
	
	// FAnimNode_Base interface
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	virtual bool NeedsOnInitializeAnimInstance() const override { return true; }
	// FAnimNode_SkeletalControlBase interface
	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_SkeletalControlBase interface
public:
	FAnimNode_MetaTransformBone()
	{
		WorldIsGame = false;
	}

private:
	// FAnimNode_SkeletalControlBase interface
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	// End of FAnimNode_Base interface

	/* The bone to start the scale at. Everything below this will be scaled by depth. */
       UPROPERTY(EditAnywhere, Category = "Gradual Scale Joints")
       FBoneReference ChainStart;
       
       /* The float curve that will drive the scale of the joints */
       UPROPERTY(EditAnywhere, Category = "Gradual Scale Joints")
       UCurveFloat* ScaleCurve;

protected:
	bool WorldIsGame;
	AActor* OwningActor;

public:
	/* Mask off the scale from each axis individually */
	UPROPERTY(EditAnywhere, Category = "Gradual Scale Joints")
	FAxisMask AxisMasks;
   
	/* The maximum hierarchy depth to which we will do the scale. If set to -1, we will scale to the end of the chain */
	UPROPERTY(EditAnywhere, Category = "Gradual Scale Joints")
	int16 MaximumDepth;

	/* If true, we will set the scale to all joints DEEPER THAN MaximumDepth to the scale of the joint AT MaximumDepth */
	UPROPERTY(EditAnywhere, Category = "Gradual Scale Joints")
	bool ContinuousScale;

	TArray<FBoneReferenceDepth> BoneRefDepthBuckets;
	int16 foundMaxDepth;
	int16 effectiveMaxDepth;
};
