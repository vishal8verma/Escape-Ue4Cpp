// Copyright©2021 Ahirwar Corporation.
#include "RotateActor.h"
#include"Components/PrimitiveComponent.h"
#include "GameFrameWork/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
URotateActor::URotateActor()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void URotateActor::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComponent();

	//LocSound =GetOwner()->FindComponentByClass<UAudioComponent>();
	//if(LocSound==nullptr)UE_LOG(LogTemp,Error,TEXT("Audio Component not Found in Class %s"),*GetOwner()->GetName());

	FString ActorName = GetOwner()->GetName();
	// UE_LOG(LogTemp, Warning, TEXT("\nActor Name: %s"), *ActorName);
	// UE_LOG(LogTemp, Warning, TEXT("\nTransform: %s"), *GetOwner()->GetActorTransform().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("\nYaw: %f"), GetOwner()->GetActorRotation().Yaw);
	CurrentRotation = GetOwner()->GetActorRotation();
	NewRotation = CurrentRotation;
	BaseYaw = CurrentRotation.Yaw;
	NewYaw = NewYaw+BaseYaw;

	if(!MyVolume)UE_LOG(LogTemp,Error,TEXT("%s Actor Don't Has MyVolume(Trigger Volume) Setuped\nPlease Set this up and Try Again!"),*GetOwner()->GetName());


};
void URotateActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CalculateMass() > MaxMass)
	{
		OpenDoor(DeltaTime);
		LastOpenedDoor = GetWorld()->GetTimeSeconds();
	}else
	{
		if(GetWorld()->GetTimeSeconds()-LastOpenedDoor>DelaysToCloseDoor)CloseDoor(DeltaTime);
	};

}
void URotateActor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, NewYaw, DeltaTime * LerpSpeed * 5.f);
	NewRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(NewRotation);
	if(LocSound==nullptr)return;
	if(bIsSoundPlayed==false)
	{
			LocSound->Play();
			bIsSoundPlayed=true;
	};


};
void URotateActor::CloseDoor(float DeltaTime)
{
	CurrentYaw=FMath::Lerp(CurrentYaw,BaseYaw,DeltaTime*LerpSpeed*6.5f);
	//FRotator NewRotation=GetOwner()->GetActorRotation();
	NewRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(NewRotation);
	if(LocSound==nullptr)return;
	if(bIsSoundPlayed==true)
	{
		LocSound->Play();
		bIsSoundPlayed=false;
	};

	
};

float URotateActor::CalculateMass()const
{
	float Mass  = 0.f;
	TArray<AActor*>OverLapedActors;
	MyVolume->GetOverlappingActors(OverLapedActors);
	for(AActor*Actor:OverLapedActors)
	{
		Mass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp,Warning,TEXT("%s Actor in Bound!"),*Actor->GetName());
	};
	return Mass;

};

void URotateActor::FindAudioComponent()
{
	LocSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(LocSound==nullptr)UE_LOG(LogTemp,Error,TEXT("Audio Component Not Founded in Class = %s"),*GetOwner()->GetName());

};



