// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RotateDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API URotateDoorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotateDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �^�C�����C���R���|�[�l���g
	class UTimelineComponent* MyTimelineComponent;

	// �J�[�u
	UPROPERTY(EditAnywhere)
	class UCurveFloat* MyCurve;

	// �^�C�}�[
	float Timer;

	//��O�����ɊJ���邩
	UPROPERTY(EditAnywhere)
	bool bIsFront;

	//�E���̃h�A��
	UPROPERTY(EditAnywhere)
	bool bIsRight;

	//�h�A���J����p�x
	UPROPERTY(EditAnywhere)
	float OpenAngle;

	//�h�A���J����
	UFUNCTION(BlueprintCallable)
	void OpenDoor();	

	// �^�C�����C���X�V���ɌĂ΂�鏈��
	UFUNCTION()
	void TimelineStep(float Value);

	// �^�C�����C���I�����ɌĂ΂�鏈��
	UFUNCTION()
	void TimelineFinished();

	//�h�A�̊p�x��ۑ�
	float angle;
};
