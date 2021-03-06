// Copyright©2021 Ahirwar Corporation. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"Components/AudioComponent.h"
#include"Engine/TriggerVolume.h"
#include "RotateActor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HENG__API URotateActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotateActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
void OpenDoor(float DeltaTime);
void CloseDoor(float DeltaTime);
float CalculateMass()const;
void FindAudioComponent();

FRotator NewRotation;
FRotator CurrentRotation;
float CurrentYaw;
bool bIsSoundPlayed=false;


UPROPERTY()
UAudioComponent*LocSound=nullptr;

UPROPERTY(EditAnyWhere)
float BaseYaw;

UPROPERTY(EditAnyWhere)
float NewYaw{90.0f};


UPROPERTY(EditAnyWhere)
float LerpSpeed{1.4f};

float LastOpenedDoor=0.f;

UPROPERTY(EditAnyWhere)
float DelaysToCloseDoor=2.f;


UPROPERTY(EditAnyWhere)
ATriggerVolume* MyVolume =nullptr;

UPROPERTY(EditAnyWhere)
float MaxMass=50.f;
		
};
