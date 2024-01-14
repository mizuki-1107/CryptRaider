// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpactedSoundComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UImpactedSoundComponent::UImpactedSoundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UImpactedSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	//オーナーのヒットイベントに衝撃音を鳴らすイベントをバインド
	AActor* Owner = GetOwner();
	UPrimitiveComponent* Component;
	Component = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
	Component->OnComponentHit.AddDynamic(this, &UImpactedSoundComponent::OnHit);
}

// Called every frame
void UImpactedSoundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UImpactedSoundComponent::PlayImpactedSound(float Strength, FVector Location)
{
	if (Strength >= AllowImpactStrength)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);
	}
}

void UImpactedSoundComponent::EnablePlaySound()
{
	bPlaySoundDisabled = false;
}


void UImpactedSoundComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//再生が有効
	if (!bPlaySoundDisabled) 
	{
		//再生を無効化
		bPlaySoundDisabled = true;
		//一定時間後に再生を有効化
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		FTimerHandle handle;
		timerManager.SetTimer(handle, this, &UImpactedSoundComponent::EnablePlaySound, 1.0f, false);

		float strength;
		FVector location;
		strength = NormalImpulse.Length();
		location = Hit.ImpactPoint;
		PlayImpactedSound(strength, location);
	}
}


