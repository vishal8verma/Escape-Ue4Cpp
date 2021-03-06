// Copyright©2021 Ahirwar Corporation.All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include"PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
//#include"Components/InputComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HENG__API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
UPROPERTY(EditAnyWhere)
float Reach=450.f;
UPhysicsHandleComponent* PhysicsHandle=nullptr;
UInputComponent* InputComp=nullptr;
void Grab();
void Throw();
void CheckingPhysicsHandle();
void SetupInputComponent();	
FHitResult RayCast()const;
FVector GetLineTraceEnd()const;
FVector GetPlayerViewPointLocation()const;
};
