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

	//�I�[�i�[
	AActor* Owner;

	//�����̃I�[�i�[�̈ʒu
	FVector InitialLocation;

	//�䂪���ދ���(cm)
	UPROPERTY(EditAnywhere, Category = "Weight")
	float SingLength = 5;

	//�ő�d��
	UPROPERTY(EditAnywhere, Category = "Weight")
	float MaxWeight = 1000;

	//WeightMeasure
	UPROPERTY(EditAnywhere, Category = "Weight")
	AWeightMeasure* WeightMeasure;

	//Function//

	//��̍������X�V
	void UpdateStageHeight(float DeltaTime);

	//�d�ʂ�0~1�Ŏ擾
	float GetWeightPercent(float Weight);

	//�d�ʑ�̏d�ʂ��X�V���ꂽ�Ƃ�
	UFUNCTION()
	void OnWeightUpdated(float Weight);
};
