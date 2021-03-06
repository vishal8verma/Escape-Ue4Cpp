// Copyright©2021 Ahirwar Corporation.All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include"Components/InputComponent.h"
#include"GameFrameWork/Controller.h"
#include"GameFrameWork/CharacterMovementComponent.h"
#include"Camera/CameraComponent.h"
#include"GrabberComponent.h"
//#include"GameFrameWork/SpringArmComponent.h"
#include "vPlayer.generated.h"

UCLASS()
class HENG__API AvPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AvPlayer();
	UPROPERTY(EditAnyWhere)
	UCameraComponent* vCamera;

	void MoveForwordBackword(float Value);
	void MoveLeftRight(float Value);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
