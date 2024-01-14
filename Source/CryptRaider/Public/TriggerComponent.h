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
	//スナップさせるトランスフォームを取得

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
	//スナップさせるトランスフォーム

	UPROPERTY(EditAnywhere, Category = "Snap")
	UStaticMesh* SnapMesh;
	//スナップ時のプレビューをするスタティックメッシュ

	UPROPERTY(EditAnywhere, Category = "Snap")
	bool bIsPreviewMesh = false;
	//プレビューするか

	//トリガーに置いてあるオブジェクト
	AActor* PutItem;

	void UpdatePreviewMesh();
	//プレビューメッシュを更新する

	//スナップトランスフォームへ補完
	void InterpToSnapTransfrom(float DeltaTime);
};

