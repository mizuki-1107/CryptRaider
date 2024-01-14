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

	// タイムラインコンポーネント
	class UTimelineComponent* MyTimelineComponent;

	// カーブ
	UPROPERTY(EditAnywhere)
	class UCurveFloat* MyCurve;

	// タイマー
	float Timer;

	//手前方向に開けるか
	UPROPERTY(EditAnywhere)
	bool bIsFront;

	//右側のドアか
	UPROPERTY(EditAnywhere)
	bool bIsRight;

	//ドアを開ける角度
	UPROPERTY(EditAnywhere)
	float OpenAngle;

	//ドアを開ける
	UFUNCTION(BlueprintCallable)
	void OpenDoor();	

	// タイムライン更新時に呼ばれる処理
	UFUNCTION()
	void TimelineStep(float Value);

	// タイムライン終了時に呼ばれる処理
	UFUNCTION()
	void TimelineFinished();

	//ドアの角度を保存
	float angle;
};
