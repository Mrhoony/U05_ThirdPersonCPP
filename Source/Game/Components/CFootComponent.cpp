#include "CFootComponent.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Engine/TriggerVolume.h"

UCFootComponent::UCFootComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCFootComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerVolume::StaticClass(), actors);
	CheckTrue(actors.Num() < 1);

	for (AActor* actor : actors)
	{
		actor->OnActorBeginOverlap.AddDynamic(this, &UCFootComponent::OnActorBeginOverlap);
		actor->OnActorEndOverlap.AddDynamic(this, &UCFootComponent::OnActorEndOverlap);
	}
}

void UCFootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance;
	FRotator leftRotation;
	Trace(LeftFootSocket, leftDistance, leftRotation);

	float rightDistance;
	FRotator rightRotation;
	Trace(RightFootSocket, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance);
	// pelvis를 월드공간에서 조정
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);
	// foot을 로컬공간에서 조정
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, (leftDistance - offset), DeltaTime, InterpSpeed);
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(rightDistance - offset), DeltaTime, InterpSpeed);
	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
}

void UCFootComponent::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CheckNull(Cast<ACharacter>(OtherActor));
	bActive = true;
}

void UCFootComponent::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CheckNull(Cast<ACharacter>(OtherActor));
	bActive = false;
}

void UCFootComponent::Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.f;
	OutRotation = FRotator::ZeroRotator;

	FVector socketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InSocketName);
	FVector start = FVector(socketLocation.X,socketLocation.Y , OwnerCharacter->GetActorLocation().Z);

	float traceZ = start.Z - CapsuleHalfHeight - AdditionalDistance;
	FVector end = FVector(socketLocation.X, socketLocation.Y, traceZ);

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		ignores,
		DrawDebugType,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	);

	CheckFalse(hitResult.IsValidBlockingHit());

	float underGround = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	OutDistance = OffsetDistance + underGround - AdditionalDistance;

	UKismetSystemLibrary::DrawDebugArrow
	(
		GetWorld(),
		hitResult.ImpactPoint,
		hitResult.ImpactPoint + hitResult.ImpactNormal * 100.f,
		3,
		FLinearColor::Blue
	);

	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);

	roll = FMath::Clamp(roll, -15.f, 15.f);
	pitch = FMath::Clamp(pitch, -30.f, 30.f);

	OutRotation = FRotator(pitch, 0, roll);
}

