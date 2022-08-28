// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EdGraph/EdGraphNodeUtils.h"
#include "Editor/AnimGraph/Public/AnimGraphNode_SkeletalControlBase.h"

#include "AnimNode_MetaTransformBone.h"

#include "AnimGraphNode_MetaTransformBone.generated.h"


UCLASS(MinimalAPI)
class  UAnimGraphNode_MetaTransformBone : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_UCLASS_BODY()
private:
	UPROPERTY(EditAnywhere, Category = MetaDittoNode)
		FAnimNode_MetaTransformBone Node;
public:

	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	virtual const FAnimNode_SkeletalControlBase* GetNode() const;
	virtual FText GetTooltipText() const override;

	virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent * previewSkelMeshComp) const override;
	// End of UEdGraphNode interface
protected:
	virtual FText GetControllerDescription() const;
};

