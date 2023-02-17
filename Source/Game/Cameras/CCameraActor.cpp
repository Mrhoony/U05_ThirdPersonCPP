#include "CCameraActor.h"
#include "Global.h"
#include "CCameraSpline.h"

#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

ACCameraActor::ACCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Camera, "Camera");
}

void ACCameraActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACCameraSpline::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		if (actor->IsA<ACCameraSpline>() && actor->GetName().Contains("BP_CCameraSpline"))
		{
			Spline = Cast<ACCameraSpline>(actor);
		}
	}
}

void ACCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
}

void ACCameraActor::OnBeginOverlap()
{
	FOnTimelineFloatStatic progress;
	progress.BindUFunction(this, "OnPlay");

	FOnTimelineEvent finish;
	finish.BindUFunction(this, "OnFinish");

	Timeline.AddInterpFloat(Spline->GetCurve(), progress);
	Timeline.SetTimelineFinishedFunc(finish);
	Timeline.SetPlayRate(PlayRate);
	Timeline.PlayFromStart();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);

	controller->SetViewTarget(this);
}

void ACCameraActor::OnPlay(float Output)
{
	USplineComponent* spline = Spline->GetSpline();
	float length = spline->GetSplineLength();

	FVector location = spline->GetLocationAtDistanceAlongSpline(length * Output, ESplineCoordinateSpace::World);
	FRotator rotation = spline->GetRotationAtDistanceAlongSpline(length * Output, ESplineCoordinateSpace::World);
	
	SetActorLocation(location);
	SetActorRotation(rotation);
}

void ACCameraActor::OnFinish()
{
	Timeline.Stop();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(player);

	controller->SetViewTarget(player);
}
