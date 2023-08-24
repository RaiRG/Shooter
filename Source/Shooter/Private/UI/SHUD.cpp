// Shooter Game, All Rights Reserved.


#include "UI/SHUD.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Canvas.h"

void ASHUD::BeginPlay()
{
	Super::BeginPlay();
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
}

void ASHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}

void ASHUD::DrawCrosshair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LinearColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LinearColor, LineThickness);
}
