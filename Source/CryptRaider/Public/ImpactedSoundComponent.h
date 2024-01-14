// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ImpactedSoundComponent.generated.h"


//衝撃を受けたときに音を鳴らすコンポーネント
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UImpactedSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UImpactedSoundComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//衝撃を受けたときに鳴らすサウンド
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = true))
	class USoundBase* Sound;

	//許容する衝撃の強さ
	UPROPERTY(EditAnywhere, Category = "Audio")
	float AllowImpactStrength = 1000.0f;

	//音声の再生を無効化中か
	bool bPlaySoundDisabled;

	//衝撃音を再生
	UFUNCTION(Category = "Audio")
	void PlayImpactedSound(float Strength, FVector Location);

	//オーナーのルートコンポーネントがヒットしたとき
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//音声の再生の有効性をセット
	UFUNCTION()
	void EnablePlaySound();
};
