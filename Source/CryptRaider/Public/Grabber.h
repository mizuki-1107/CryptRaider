// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//�f�o�b�O��\��
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawDebug;
	//�I�u�W�F�N�g��͂�
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void Grab();
	//�͂�ł���I�u�W�F�N�g�𗣂�
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void Release();


private:
	//�ő�̒͂߂鋗��
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float MaxGrabDistance = 400;
	//�͂ނƂ��̃J�v�Z���g���[�X�̔��a
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float GrabRadius = 100;
	//�I�u�W�F�N�g��͂�ł���Ƃ��̋���
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float HoldDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
