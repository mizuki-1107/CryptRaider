// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ImpactedSoundComponent.generated.h"


//�Ռ����󂯂��Ƃ��ɉ���炷�R���|�[�l���g
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

	//�Ռ����󂯂��Ƃ��ɖ炷�T�E���h
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = true))
	class USoundBase* Sound;

	//���e����Ռ��̋���
	UPROPERTY(EditAnywhere, Category = "Audio")
	float AllowImpactStrength = 1000.0f;

	//�����̍Đ��𖳌�������
	bool bPlaySoundDisabled;

	//�Ռ������Đ�
	UFUNCTION(Category = "Audio")
	void PlayImpactedSound(float Strength, FVector Location);

	//�I�[�i�[�̃��[�g�R���|�[�l���g���q�b�g�����Ƃ�
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//�����̍Đ��̗L�������Z�b�g
	UFUNCTION()
	void EnablePlaySound();
};
