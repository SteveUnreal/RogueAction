// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Widget.h"
#include "Components/SizeBox.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor)) {

		RemoveFromParent();

		UE_LOG(LogTemp, Warning, TEXT("AttachedActor is no longer valid, removing HealthWidget."));
		return;
	}

	FVector2D ScreenPosition;
	
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition)) {

		float scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= scale;
		if (ParentSizeBox) {
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}

}
