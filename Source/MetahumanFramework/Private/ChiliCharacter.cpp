// Fill out your copyright notice in the Description page of Project Settings.


#include "ChiliCharacter.h"
#include <Components/SkeletalMeshComponent.h>

// Sets default values
AChiliCharacter::AChiliCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SkeletalMeshCom = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshCom->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AChiliCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChiliCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChiliCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

