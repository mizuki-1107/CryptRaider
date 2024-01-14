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
	//オーナーの初期位置を保存
	InitialLocation = Owner->GetActorLocation();

	//重量が更新されたときのイベントをバインド
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
	//重さに応じて台を下に移動
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

