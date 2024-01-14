// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/StaticMeshComponent.h"






UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);

}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		//�u���Ă���A�C�e���ɃZ�b�g
		PutItem = Actor;
		//�A�C�e���̃��[�g�R���|�[�l���g���v���~�e�B�u�R���|�[�l���g�ɃL���X�g���ۑ�
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		//�R���|�[�l���g�����݂���
		if (Component != nullptr)
		{
			//UE_LOG(LogTemp, Display, TEXT("Unapproved item has been placed"));
			//�A�C�e�������g�ɃA�^�b�`
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Component->SetSimulatePhysics(false);
			//���[�o�[�����݂���ꍇ�̓��[�o�[�𓮂���
			if (Mover) 
			{
				Mover->SetShouldMove(true);
			}
			//�u�����Ƃ��̃f���Q�[�g�����s
			OnPut.Broadcast();
			//�⊮
			InterpToSnapTransfrom(DeltaTime);
		}
	}
	else
	{
		//�A�C�e���̎Q�Ƃ��폜
		PutItem = nullptr;
		//UE_LOG(LogTemp, Display, TEXT("AcceptableItem has been placed"));
		if (Mover)
		{
			Mover->SetShouldMove(false);
		}
	}
	
}

void UTriggerComponent::SetMover(UMover* NewMover) 
//Mover���Z�b�g
{
	Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActor() const
//�J���A�N�^�[���擾
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbed)
		{
			return Actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::UpdatePreviewMesh()
//�v���r���[���b�V�����X�V����
{
	UStaticMeshComponent* MeshComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	MeshComponent->SetupAttachment(GetOwner()->GetRootComponent());
	MeshComponent->SetStaticMesh(SnapMesh);
	//MeshComponent->SetRelativeTransform(SnapTransform);
	UE_LOG(LogTemp, Display, TEXT("UpdatePreviewMesh"));
}

FTransform UTriggerComponent::GetSnapTransform()
{
	FTransform WorldTransform;
	FTransform RelativeTransform = SnapTransform;
	FTransform TriggerTransform = GetComponentTransform();
	FVector WorldLocation = UKismetMathLibrary::TransformLocation(TriggerTransform, RelativeTransform.GetLocation());
	FRotator WorldRotation = UKismetMathLibrary::TransformRotation(TriggerTransform, RelativeTransform.Rotator());

	WorldTransform = UKismetMathLibrary::MakeTransform
	(
	FVector(WorldLocation),FRotator(WorldRotation),FVector(TriggerTransform.GetScale3D())
	);
	

	return WorldTransform;
}

//�X�i�b�v�g�����X�t�H�[���֕⊮
void UTriggerComponent::InterpToSnapTransfrom(float DeltaTime)
{
	if (PutItem) 
	{
		//�u���Ă���A�C�e���̐e�R���|�[�l���g�����݂��Ȃ�
		if (!PutItem->GetParentComponent())
		{
			//�u���Ă���A�C�e�������g�ɃA�^�b�`
			PutItem->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		}
		//�A�C�e�����X�i�b�v�g�����X�t�H�[���֕⊮
		FVector location;
		FRotator rotation;
		FVector startLocation = PutItem->GetRootComponent()->GetRelativeLocation();
		FRotator startRotation = PutItem->GetRootComponent()->GetRelativeRotation();
		FVector targetLocation = SnapTransform.GetLocation();
		FRotator targetRotation = SnapTransform.Rotator();
		const float speed = 3.0f;
	
		//�ʒu��⊮
		location = FMath::VInterpTo(startLocation, targetLocation, DeltaTime, speed);
		//��]��⊮
		rotation = FMath::RInterpTo(startRotation, targetRotation, DeltaTime, speed);
		PutItem->SetActorRelativeLocation(location);
		PutItem->SetActorRelativeRotation(rotation);
	}
}