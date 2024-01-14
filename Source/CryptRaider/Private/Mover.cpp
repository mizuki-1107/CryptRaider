// Fill out your copyright notice in the Description page of Project Settings.



#include "Mover.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"




// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("OriginalLocation: %s : %s"), *GetOwner()->GetActorNameOrLabel(), *OriginalLocation.ToString());
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;

	if (ShouldMove) 
	{	
		TargetLocation = OriginalLocation + MoveOffset;
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	//ShouldMove���ʂ̒l�̂Ƃ�ShouldMove���Z�b�g
	if (ShouldMove != NewShouldMove)
	{
		ShouldMove = NewShouldMove;
		//���ʉ����Đ�
		class USoundBase* SoundClass;
		if (ShouldMove)
		{
			//�J����
			SoundClass = OpenSound;
		}
		else
		{
			//�܂鉹
			SoundClass = CloseSound;
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundClass, GetOwner()->GetActorLocation());
	}
}
