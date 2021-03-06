// Copyright©2021 Ahirwar Corporation. 


#include "WorldPosition.h"
#include"GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}
// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	// FString Log =TEXT("Hello");
	// FString* PtrLog = &Log;
	// Log.Len();//we can do that easily here by dot operator
	// PtrLog.Len();//Nope this is not gonna to work
	// *PtrLog.Len();//Nope this is also not gonna to work here cause of operator precidence
	// //here * has precidence compare to .
	// //so we can use () for more precodence
	// (*PtrLog).Len();//yup this is prefect here
	//int32 Len_ = PtrLog->Len();//this is perfect here 
	FString ObjName = GetOwner()->GetName();
	UE_LOG(LogTemp,Error,TEXT("|Obj Name: %s|"),*ObjName);
		// UE_LOG(LogTemp,Error,TEXT("%s and The len is:%i"),**PtrLog,Len_);
	// UE_LOG(LogTemp,Warning,TEXT("Your First & Last Warning...\nBy Ahirwar Corp."))
	// UE_LOG(LogTemp,Warning,TEXT("Warning Level: \"High\""))
	// UE_LOG(LogTemp,Error,TEXT("Error Level: \"Ultra High\""))
	// UE_LOG(LogTemp,Error,TEXT("Compiling Takes Toolong."))
	FString Loc=GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp,Error,TEXT("Actor Location: %s"),*Loc);
	UE_LOG(LogTemp,Error,TEXT("Transform:\n%s"),*GetOwner()->GetActorTransform().ToString());
	// ...	
}
// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

