// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateDoorComponent.h"
#include "Components/TimelineComponent.h"




// Sets default values for this component's properties
URotateDoorComponent::URotateDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// �J�[�u�A�Z�b�g�̎擾
// �J�[�u�̎�ނɂ���ăN���X��I��(UCurveFloat / UCurveLinearColor / UCurveVector)
	const ConstructorHelpers::FObjectFinder<UCurveFloat>    _Find(TEXT("CurveFloat'/Game/CryptRider/RotateDoorComponent/Curve/CA_OpenDoor'"));
	if (_Find.Succeeded()) 
	{
		MyCurve = _Find.Object;
	}

	MyTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent0"));
}


// Called when the game starts
void URotateDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	Timer = 0.0f;	

	if (MyTimelineComponent)
	{
		// �^�C�����C���X�V���ɌĂяo����郁�\�b�h�̒�`
		FOnTimelineFloat    _MyTimelineStepFunc;
		_MyTimelineStepFunc.BindUFunction(this, TEXT("TimelineStep"));
		MyTimelineComponent->AddInterpFloat(MyCurve, _MyTimelineStepFunc);

		// �^�C�����C���I�����ɌĂяo����郁�\�b�h�̒�`
		FOnTimelineEvent    _MyTimelineFinishedFunc;
		_MyTimelineFinishedFunc.BindUFunction(this, TEXT("TimelineFinished"));
		MyTimelineComponent->SetTimelineFinishedFunc(_MyTimelineFinishedFunc);
	}
}


// Called every frame
void URotateDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void URotateDoorComponent::OpenDoor()
{
	// �^�C�����C���J�n
	if (MyTimelineComponent)
	{
		MyTimelineComponent->PlayFromStart();	
	}
}

// �^�C�����C���X�V���ɌĂ΂�鏈��
void URotateDoorComponent::TimelineStep(float Value)
{
	angle = Value * OpenAngle;
	if (bIsRight)
	{
		angle *= -1;
	}
	SetRelativeRotation(FRotator(0, angle, 0));
}

// �^�C�����C���I�����ɌĂ΂�鏈��
void URotateDoorComponent::TimelineFinished()
{
}