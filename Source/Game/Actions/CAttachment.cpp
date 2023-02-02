#include "CAttachment.h"
#include "Global.h"

#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		shape->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);		
	}

	OffCollisions(); //shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Super::BeginPlay(); // 터지기 때문에 내림
}

void ACAttachment::AttachTo(FName InSocketName)
{
	this->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == OwnerCharacter);
	CheckTrue(OtherActor->GetClass() == OwnerCharacter->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
		CheckNull(otherCharacter);
		
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnAttachmentEndOverlap.IsBound())
	{
		ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
		CheckNull(otherCharacter);

		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void ACAttachment::OnCollisions(FString InCollisionName)
{
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACAttachment::OffCollisions()
{
	for (UShapeComponent* shape : ShapeComponents)
	{
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}