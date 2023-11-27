 // Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
	// UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: none "));
	// UE_LOG(LogTemp, Warning, TEXT("Configured Moved Distance: none "));
	// UE_LOG(LogTemp, Error, TEXT("Configured Moved Distance: none "));
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"),*Name);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	ShouldPlatformReturn();

		
}
void AMovingPlatform::MovePlatform(float D_T)
{
	if ( ShouldPlatformReturn())
	{
		FVector MoveDirction = PlatformVelocity.GetSafeNormal();
		PlatformVelocity *= -1;
		StartLocation += MoveDirction * MoveDistance;
		SetActorLocation(StartLocation);
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlatformVelocity * D_T;
		SetActorLocation(CurrentLocation);
	}

}

void AMovingPlatform::RotatePlatform(float D_T)
{
	// FRotator CurrentRotation = GetActorRotation();
	// CurrentRotation += RotationVelocity * D_T;
	// SetActorRotation(CurrentRotation);
	AddActorLocalRotation(RotationVelocity * D_T);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{

	return  GetDistanceMoved() > MoveDistance ;
}

float AMovingPlatform::GetDistanceMoved() const
{

	return FVector::Dist(StartLocation,GetActorLocation());

}


