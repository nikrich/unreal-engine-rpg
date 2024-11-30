// Copyright Hungry Ghost


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* inWidgetController)
{
	WidgetController = inWidgetController;
	WidgetControllerSet();
}
