// Copyright©2021 vAhirwar Corporation.All rights reserved.


#include "GrabberComponent.h"
#include"DrawDebugHelpers.h"
#include "GameFrameWork/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	CheckingPhysicsHandle();
	SetupInputComponent();
	// ...
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PhysicsHandle->GrabbedComponent)PhysicsHandle->SetTargetLocation(GetLineTraceEnd());

}

void UGrabberComponent::Grab()
{
	FHitResult hit=RayCast();	
	UPrimitiveComponent*GrabableComponent=hit.GetComponent();

	if(hit.GetActor())
	{
	PhysicsHandle->GrabComponentAtLocation
	(
		GrabableComponent,
		NAME_None,
		GetLineTraceEnd()
	);
	};

};

void UGrabberComponent::Throw()
{
	UE_LOG(LogTemp,Error,TEXT("Throw Pressed!"));
	PhysicsHandle->ReleaseComponent();
};

void UGrabberComponent::CheckingPhysicsHandle()
{
	UE_LOG(LogTemp, Error, TEXT("!Grabber Component reporting..."));
	PhysicsHandle =GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle==nullptr)UE_LOG(LogTemp,Error,TEXT("Physics Handle Not Founded!"));
	
};

void UGrabberComponent::SetupInputComponent()
{
	InputComp =GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComp)
	{
		UE_LOG(LogTemp,Error,TEXT("UInputComponent by Founded!"));
		InputComp->BindAction("Grab",IE_Pressed,this,&UGrabberComponent::Grab);
		InputComp->BindAction("Grab",IE_Released,this,&UGrabberComponent::Throw);
	}else
	{
		UE_LOG(LogTemp,Error,TEXT("UInpotComponent Not Founded!"));
	};

};

FHitResult UGrabberComponent::RayCast()const
{

	UE_LOG(LogTemp,Error,TEXT("Grab Pressed!"));
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetPlayerViewPointLocation(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	AActor*HitActor = Hit.GetActor();
	if(HitActor)UE_LOG(LogTemp,Error,TEXT("Hitted: %s"),*HitActor->GetName());

	return Hit;
};

FVector UGrabberComponent::GetLineTraceEnd()const
{

	 FVector PlayerViewPointLocation;
	 FRotator PlayerViewPointRotation;

	GetWorld()
		->GetFirstPlayerController()
		->GetPlayerViewPoint(
			PlayerViewPointLocation, PlayerViewPointRotation);

	// UE_LOG(LogTemp, Error, TEXT("Actor Location:%s\nView Rotation: %s"),
	// 	   *PlayerViewPointLocation.ToString(),
	// 	   *PlayerViewPointRotation.ToString());
	return PlayerViewPointLocation+(PlayerViewPointRotation.Vector()*Reach);

};
FVector UGrabberComponent::GetPlayerViewPointLocation()const
{
	FVector ViewLocaition;
	FRotator ViewRotation;

	GetWorld()
	->GetFirstPlayerController()
	->GetPlayerViewPoint(ViewLocaition,ViewRotation);
	return ViewLocaition;
};
