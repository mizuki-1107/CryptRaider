// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightMeasure.h"

// Sets default values
AWeightMeasure::AWeightMeasure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�{�b�N�X�R���W���������[�g�ɃZ�b�g
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetBoxExtent(FVector(30, 30, 30));
}

// Called when the game starts or when spawned
void AWeightMeasure::BeginPlay()
{
	Super::BeginPlay();
	//�{�b�N�X���I�[�o�[���b�v�����Ƃ��̃C�x���g���o�C���h
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AWeightMeasure::OnPutItem);
	//�{�b�N�X���G���h�I�[�o�[���b�v�����Ƃ��̃C�x���g���o�C���h
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AWeightMeasure::OnBoxEndOverlap);

}


// Called every frame
void AWeightMeasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWeightMeasure::GetWeight(TArray<AActor*> Actors)
{
	float Weight = 0;
	for (AActor* Actor : Actors)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent> (Actor->GetRootComponent());
		Weight += Component->GetMass();
	}
	return Weight;
}

void AWeightMeasure::OnPutItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!UpdateDisabled)
	{
		//�X�V�𖳌�
		UpdateDisabled = true;
		//�^�C�}�[�}�l�[�W���[���擾
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		FTimerHandle handle;
		TimerManager.SetTimer(handle, this, &AWeightMeasure::UpdateEnable, 0.5f);

		TArray<AActor*> Actors;
		GetOverlappingActors(Actors);
		OnWeightUpdated.Broadcast(GetWeight(Actors));
	}

}

void AWeightMeasure::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!UpdateDisabled)
	{
		//�X�V�𖳌�
		UpdateDisabled = true;
		//�^�C�}�[�}�l�[�W���[���擾
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		FTimerHandle handle;
		TimerManager.SetTimer(handle, this, &AWeightMeasure::UpdateEnable, 0.5f);

		TArray<AActor*> Actors;
		GetOverlappingActors(Actors);
		OnWeightUpdated.Broadcast(GetWeight(Actors));
	}
}

void AWeightMeasure::UpdateEnable()
{
	UpdateDisabled = false;
}


