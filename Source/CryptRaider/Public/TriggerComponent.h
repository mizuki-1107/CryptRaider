// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Engine/StaticMesh.h"
#include "TriggerComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPut);
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UTriggerComponent();


protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);


	UPROPERTY(EditAnywhere)
	AActor* EventActor;

	FTransform GetSnapTransform();
	//�X�i�b�v������g�����X�t�H�[�����擾

	AActor* GetAcceptableActor() const;

	//Event Dispather(Multicast Delegate)
	UPROPERTY(BlueprintAssignable)
	FOnPut OnPut;

private:
	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;

	UMover* Mover;

	UPROPERTY(EditAnywhere, Category = "Snap", Meta = (MakeEditWidget = true))
	FTransform SnapTransform;
	//�X�i�b�v������g�����X�t�H�[��

	UPROPERTY(EditAnywhere, Category = "Snap")
	UStaticMesh* SnapMesh;
	//�X�i�b�v���̃v���r���[������X�^�e�B�b�N���b�V��

	UPROPERTY(EditAnywhere, Category = "Snap")
	bool bIsPreviewMesh = false;
	//�v���r���[���邩

	//�g���K�[�ɒu���Ă���I�u�W�F�N�g
	AActor* PutItem;

	void UpdatePreviewMesh();
	//�v���r���[���b�V�����X�V����

	//�X�i�b�v�g�����X�t�H�[���֕⊮
	void InterpToSnapTransfrom(float DeltaTime);
};

