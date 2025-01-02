// abyrax - 2d project


#include "EnemySimple.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character2D.h"

AEnemySimple::AEnemySimple()
{
}

void AEnemySimple::BeginPlay()
{
	Super::BeginPlay();

	bEnemyMoveRight = FMath::RandBool();
	AEnemyBase::ToggleFacingDirection();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,&AEnemySimple::OnHit);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySimple::OnSphereOverlapped);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemySimple::OnSphereEndOverlap);
}

void AEnemySimple::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
	if(!bAlreadyHit)
	{
		bAlreadyHit = true;
		AEnemySimple::OnCapsuleComponentHit(OtherActor,Hit.Normal);
	}
}

void AEnemySimple::OnCapsuleComponentHit(AActor* OtherActor, FVector HitNormal)
{
	Super::OnCapsuleComponentHit(OtherActor, HitNormal);
	if(OtherActor != UGameplayStatics::GetPlayerPawn(this,0))
	{
		if(HitNormal.X != 0.0f)
		{
			bEnemyMoveRight = !bEnemyMoveRight;

			AEnemyBase::ToggleFacingDirection();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AEnemySimple::ResetHit,0.2f,false);
		}
	}
}

void AEnemySimple::OnSphereOverlapped(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlapped(OverlapedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);
	if(bCanFollow && OtherActor == PlayerCharacter)
	{
		bFollowing = true;
	}
}

void AEnemySimple::OnSphereEndOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlapedComponent, OtherActor, OtherComponent, OtherBodyIndex);
	if(bCanFollow && OtherActor == PlayerCharacter)
	{
		bFollowing = true;
		Move();
	}
}

void AEnemySimple::ResetHit()
{
	bAlreadyHit=false;
}

void AEnemySimple::Tick(float DeltaSeconds)
{
	
	Super::Tick(DeltaSeconds);
	Move();
	if(bCanFollow && bFollowing)
	{
		FollowCharacter();
	}
}
