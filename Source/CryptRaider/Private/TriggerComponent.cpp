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
		//置いてあるアイテムにセット
		PutItem = Actor;
		//アイテムのルートコンポーネントをプリミティブコンポーネントにキャストし保存
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		//コンポーネントが存在する
		if (Component != nullptr)
		{
			//UE_LOG(LogTemp, Display, TEXT("Unapproved item has been placed"));
			//アイテムを自身にアタッチ
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Component->SetSimulatePhysics(false);
			//ムーバーが存在する場合はムーバーを動かす
			if (Mover) 
			{
				Mover->SetShouldMove(true);
			}
			//置いたときのデリゲートを実行
			OnPut.Broadcast();
			//補完
			InterpToSnapTransfrom(DeltaTime);
		}
	}
	else
	{
		//アイテムの参照を削除
		PutItem = nullptr;
		//UE_LOG(LogTemp, Display, TEXT("AcceptableItem has been placed"));
		if (Mover)
		{
			Mover->SetShouldMove(false);
		}
	}
	
}

void UTriggerComponent::SetMover(UMover* NewMover) 
//Moverをセット
{
	Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActor() const
//開錠アクターを取得
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
//プレビューメッシュを更新する
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

//スナップトランスフォームへ補完
void UTriggerComponent::InterpToSnapTransfrom(float DeltaTime)
{
	if (PutItem) 
	{
		//置いてあるアイテムの親コンポーネントが存在しない
		if (!PutItem->GetParentComponent())
		{
			//置いてあるアイテムを自身にアタッチ
			PutItem->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		}
		//アイテムをスナップトランスフォームへ補完
		FVector location;
		FRotator rotation;
		FVector startLocation = PutItem->GetRootComponent()->GetRelativeLocation();
		FRotator startRotation = PutItem->GetRootComponent()->GetRelativeRotation();
		FVector targetLocation = SnapTransform.GetLocation();
		FRotator targetRotation = SnapTransform.Rotator();
		const float speed = 3.0f;
	
		//位置を補完
		location = FMath::VInterpTo(startLocation, targetLocation, DeltaTime, speed);
		//回転を補完
		rotation = FMath::RInterpTo(startRotation, targetRotation, DeltaTime, speed);
		PutItem->SetActorRelativeLocation(location);
		PutItem->SetActorRelativeRotation(rotation);
	}
}