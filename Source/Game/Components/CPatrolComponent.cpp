#include "CPatrolComponent.h"
#include "Global.h"
#include "Characters/CPatrolPath.h"
#include "Components/SplineComponent.h"

UCPatrolComponent::UCPatrolComponent()
{
}

void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UCPatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius)
{
	OutLocation = FVector::ZeroVector;
	OutAcceptanceRadius = AcceptanceRadius;	
	CheckNullResult(Path, false);

	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

	return true;
}

void UCPatrolComponent::UpdateNext()
{
	CheckNull(Path);

	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();

	if (bReverse) // Reverse
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (Path->GetSpline()->IsClosedLoop())
		{
			Index = count - 1;
			return;
		}

		Index = 1;
		bReverse = false;

		return;
	}

	if (Index < count - 1) // Forward
	{
		Index++;
		return;
	}

	if (Path->GetSpline()->IsClosedLoop() == true)
	{
		Index = 0;
		return;
	}

	Index = count - 2;
	bReverse = true;
}