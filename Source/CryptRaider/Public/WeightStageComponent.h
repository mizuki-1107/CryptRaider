// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeightMeasure.h"
#include "WeightStageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UWeightStageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeightStageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//オーナー
	AActor* Owner;

	//初期のオーナーの位置
	FVector InitialLocation;

	//台が沈む距離(cm)
	UPROPERTY(EditAnywhere, Category = "Weight")
	float SingLength = 5;

	//最大重量
	UPROPERTY(EditAnywhere, Category = "Weight")
	float MaxWeight = 1000;

	//WeightMeasure
	UPROPERTY(EditAnywhere, Category = "Weight")
	AWeightMeasure* WeightMeasure;

	//Function//

	//台の高さを更新
	void UpdateStageHeight(float DeltaTime);

	//重量を0~1で取得
	float GetWeightPercent(float Weight);

	//重量台の重量が更新されたとき
	UFUNCTION()
	void OnWeightUpdated(float Weight);
};
