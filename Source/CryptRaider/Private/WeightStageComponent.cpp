// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightStageComponent.h"

// Sets default values for this component's properties
UWeightStageComponent::UWeightStageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeightStageComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	//�I�[�i�[�̏����ʒu��ۑ�
	InitialLocation = Owner->GetActorLocation();

	//�d�ʂ��X�V���ꂽ�Ƃ��̃C�x���g���o�C���h
	WeightMeasure->OnWeightUpdated.AddDynamic(this, &UWeightStageComponent::OnWeightUpdated);
}


// Called every frame
void UWeightStageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UWeightStageComponent::UpdateStageHeight(float Weight)
{
	//�d���ɉ����đ�����Ɉړ�
	FVector Location = InitialLocation - FVector(0, 0,SingLength * GetWeightPercent(Weight));
	Owner->SetActorLocation(Location);
}

float UWeightStageComponent::GetWeightPercent(float Weight)
{
	float OutWeight = Weight / MaxWeight;
	UE_LOG(LogTemp, Display, TEXT("%f"), OutWeight);
	return OutWeight;
}

void UWeightStageComponent::OnWeightUpdated(float Weight)
{
	UpdateStageHeight(Weight);
}

