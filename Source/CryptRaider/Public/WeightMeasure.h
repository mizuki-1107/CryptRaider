// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"//UBoxComponent
#include "WeightMeasure.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeightUpdated, float, Weight);

UCLASS()
class CRYPTRAIDER_API AWeightMeasure : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeightMeasure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//BoxComponent
	UPROPERTY()
		UBoxComponent* BoxComp;

	//�d�ʂ��X�V���ꂽ�Ƃ�
	UPROPERTY(BlueprintAssignable)
		FOnWeightUpdated OnWeightUpdated;

	//�X�V������
	bool UpdateDisabled;

	//�d�ʂ��擾
	UFUNCTION(BlueprintCallable, Category = "Weight")
		float GetWeight(TArray<AActor*> Actors);

	//�A�C�e�����u���ꂽ�Ƃ�
	UFUNCTION(BlueprintCallable, Category = "Weight")
		void OnPutItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//�{�b�N�X���G���h�I�[�o�[���b�v�����Ƃ�
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//�d�ʂ̍X�V��L����
	void UpdateEnable();
};
