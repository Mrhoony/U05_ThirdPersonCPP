#include "CSetViewTarget.h"
#include "Global.h"

#include "Camera/CameraActor.h"

ACSetViewTarget::ACSetViewTarget()
{
}

void ACSetViewTarget::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::K2_SetTimer(this, "Change", 2.f, true);
}

void ACSetViewTarget::Change()
{
	CheckFalse(bActivation);

	/*APlayerCameraManager* cameraManage = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CheckNull(cameraManage);
	CheckTrue(Cameras.Num() < 1);

	cameraManage->SetViewTarget(Cameras[Index]);*/

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	CheckTrue(Cameras.Num() < 1);

	controller->SetViewTargetWithBlend(Cameras[Index], 2.f, EViewTargetBlendFunction::VTBlend_EaseInOut, 2.f);

		Index++;
	Index %= Cameras.Num();
}
