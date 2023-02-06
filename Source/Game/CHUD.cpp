#include "CHUD.h"
#include "Global.h"

#include "Engine/Texture2D.h"
#include "Engine/Canvas.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset<UTexture2D>(&Texture, "Texture2D'/Game/Widgets/T_Crosshair.T_Crosshair'");
}

void ACHUD::DrawHUD()
{
	//Super::DrawHUD();
	//CheckNull(Texture);
	//CheckFalse(bVisibleAim);

	////TODO
	//FVector2D center = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	//FCanvasTileItem item(,)
	//Canvas->DrawItem();
}
