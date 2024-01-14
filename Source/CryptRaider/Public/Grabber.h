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
	//デバッグを表示
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawDebug;
	//オブジェクトを掴む
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void Grab();
	//掴んでいるオブジェクトを離す
	UFUNCTION(BlueprintCallable, Category = "Grabber")
	void Release();


private:
	//最大の掴める距離
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float MaxGrabDistance = 400;
	//掴むときのカプセルトレースの半径
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float GrabRadius = 100;
	//オブジェクトを掴んでいるときの距離
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float HoldDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
