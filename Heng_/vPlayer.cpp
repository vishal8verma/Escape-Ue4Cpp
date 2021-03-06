// Copyright©2021 Ahirwar Corporation.All rights reserved. 
#include "vPlayer.h"

// Sets default values
AvPlayer::AvPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch =false;
	bUseControllerRotationYaw =false;
	bUseControllerRotationRoll =false;

	GetCharacterMovement()->bOrientRotationToMovement =true;
	GetCharacterMovement()->RotationRate =FRotator(0.f,540.f,0.f);
	GetCharacterMovement()->JumpZVelocity =600.f;
	GetCharacterMovement()->AirControl =2.f;

	vCamera =CreateDefaultSubobject<UCameraComponent>(TEXT("vCamera"));
	vCamera->SetupAttachment(RootComponent);
	vCamera->bUsePawnControlRotation = true;
}
void AvPlayer::BeginPlay()
{
	Super::BeginPlay();	
}
void AvPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AvPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForwordBackword",this,&AvPlayer::MoveForwordBackword);
	PlayerInputComponent->BindAxis("MoveLeftRight",this,&AvPlayer::MoveLeftRight);
	
}
void AvPlayer::MoveForwordBackword(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator Yaw{0.f,Rotation.Yaw,0.f};
	FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction,Value);
};
void AvPlayer::MoveLeftRight(float Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator Yaw{0.f,Rotation.Yaw,0.f};
	FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction,Value);
};


