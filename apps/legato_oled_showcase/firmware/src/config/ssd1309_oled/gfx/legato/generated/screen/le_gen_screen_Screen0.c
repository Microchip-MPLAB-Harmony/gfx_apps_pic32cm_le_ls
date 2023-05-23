#include "gfx/legato/generated/screen/le_gen_screen_Screen0.h"

// screen member widget declarations
static leWidget* root0;

leWidget* Screen0_BackgroundPanel;
leWidget* Screen0_TopUIPanel;
leWidget* Screen0_BottomUIPanel;
leLabelWidget* Screen0_HourLabelWidget;
leLineWidget* Screen0_LineWidget0;
leLabelWidget* Screen0_AMPMLabelWidget;
leLabelWidget* Screen0_ColonLabelWidget;
leLabelWidget* Screen0_MinLabelWidget;
leLabelWidget* Screen0_TempLabelWidget;
leLabelWidget* Screen0_TempUnitLabelWidget;
leLabelWidget* Screen0_DateLabelWidget;
leLineWidget* Screen0_LineWidget3;
leButtonWidget* Screen0_PlayPauseButton;
leLineWidget* Screen0_LineWidget1;
leWidget* Screen0_PanelWidget0;
leLineWidget* Screen0_LineWidget2;
leLabelWidget* Screen0_LabelWidget0;
leWidget* Screen0_MusicBar0;
leWidget* Screen0_MusicBar1;
leWidget* Screen0_MusicBar2;
leWidget* Screen0_MusicBar3;
leWidget* Screen0_MusicBar4;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_Screen0(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_Screen0(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 128, 64);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    Screen0_BackgroundPanel = leWidget_New();
    Screen0_BackgroundPanel->fn->setPosition(Screen0_BackgroundPanel, 0, 0);
    Screen0_BackgroundPanel->fn->setSize(Screen0_BackgroundPanel, 128, 64);
    Screen0_BackgroundPanel->fn->setScheme(Screen0_BackgroundPanel, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)Screen0_BackgroundPanel);

    Screen0_TopUIPanel = leWidget_New();
    Screen0_TopUIPanel->fn->setPosition(Screen0_TopUIPanel, 0, 0);
    Screen0_TopUIPanel->fn->setSize(Screen0_TopUIPanel, 128, 32);
    Screen0_TopUIPanel->fn->setBackgroundType(Screen0_TopUIPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen0_TopUIPanel);

    Screen0_HourLabelWidget = leLabelWidget_New();
    Screen0_HourLabelWidget->fn->setPosition(Screen0_HourLabelWidget, 41, 4);
    Screen0_HourLabelWidget->fn->setSize(Screen0_HourLabelWidget, 32, 25);
    Screen0_HourLabelWidget->fn->setScheme(Screen0_HourLabelWidget, &WhitePixelScheme);
    Screen0_HourLabelWidget->fn->setBackgroundType(Screen0_HourLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_HourLabelWidget->fn->setHAlignment(Screen0_HourLabelWidget, LE_HALIGN_RIGHT);
    Screen0_HourLabelWidget->fn->setMargins(Screen0_HourLabelWidget, 2, 4, 2, 4);
    Screen0_HourLabelWidget->fn->setString(Screen0_HourLabelWidget, (leString*)&string_TimeDefault);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_HourLabelWidget);

    Screen0_LineWidget0 = leLineWidget_New();
    Screen0_LineWidget0->fn->setPosition(Screen0_LineWidget0, 38, 1);
    Screen0_LineWidget0->fn->setSize(Screen0_LineWidget0, 1, 30);
    Screen0_LineWidget0->fn->setScheme(Screen0_LineWidget0, &WhitePixelScheme);
    Screen0_LineWidget0->fn->setBackgroundType(Screen0_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LineWidget0->fn->setStartPoint(Screen0_LineWidget0, 0, 5);
    Screen0_LineWidget0->fn->setEndPoint(Screen0_LineWidget0, 0, 25);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_LineWidget0);

    Screen0_AMPMLabelWidget = leLabelWidget_New();
    Screen0_AMPMLabelWidget->fn->setPosition(Screen0_AMPMLabelWidget, 108, 10);
    Screen0_AMPMLabelWidget->fn->setSize(Screen0_AMPMLabelWidget, 20, 19);
    Screen0_AMPMLabelWidget->fn->setScheme(Screen0_AMPMLabelWidget, &WhitePixelScheme);
    Screen0_AMPMLabelWidget->fn->setBackgroundType(Screen0_AMPMLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_AMPMLabelWidget->fn->setMargins(Screen0_AMPMLabelWidget, 2, 4, 4, 4);
    Screen0_AMPMLabelWidget->fn->setString(Screen0_AMPMLabelWidget, (leString*)&string_PMLabel);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_AMPMLabelWidget);

    Screen0_ColonLabelWidget = leLabelWidget_New();
    Screen0_ColonLabelWidget->fn->setPosition(Screen0_ColonLabelWidget, 72, 5);
    Screen0_ColonLabelWidget->fn->setSize(Screen0_ColonLabelWidget, 6, 20);
    Screen0_ColonLabelWidget->fn->setScheme(Screen0_ColonLabelWidget, &WhitePixelScheme);
    Screen0_ColonLabelWidget->fn->setBackgroundType(Screen0_ColonLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_ColonLabelWidget->fn->setHAlignment(Screen0_ColonLabelWidget, LE_HALIGN_CENTER);
    Screen0_ColonLabelWidget->fn->setMargins(Screen0_ColonLabelWidget, 0, 0, 0, 0);
    Screen0_ColonLabelWidget->fn->setString(Screen0_ColonLabelWidget, (leString*)&string_ColonLabel);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_ColonLabelWidget);

    Screen0_MinLabelWidget = leLabelWidget_New();
    Screen0_MinLabelWidget->fn->setPosition(Screen0_MinLabelWidget, 78, 4);
    Screen0_MinLabelWidget->fn->setSize(Screen0_MinLabelWidget, 32, 25);
    Screen0_MinLabelWidget->fn->setScheme(Screen0_MinLabelWidget, &WhitePixelScheme);
    Screen0_MinLabelWidget->fn->setBackgroundType(Screen0_MinLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_MinLabelWidget->fn->setMargins(Screen0_MinLabelWidget, 2, 4, 2, 4);
    Screen0_MinLabelWidget->fn->setString(Screen0_MinLabelWidget, (leString*)&string_TimeDefault);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_MinLabelWidget);

    Screen0_TempLabelWidget = leLabelWidget_New();
    Screen0_TempLabelWidget->fn->setPosition(Screen0_TempLabelWidget, 0, 14);
    Screen0_TempLabelWidget->fn->setSize(Screen0_TempLabelWidget, 24, 19);
    Screen0_TempLabelWidget->fn->setScheme(Screen0_TempLabelWidget, &WhitePixelScheme);
    Screen0_TempLabelWidget->fn->setBackgroundType(Screen0_TempLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_TempLabelWidget->fn->setHAlignment(Screen0_TempLabelWidget, LE_HALIGN_RIGHT);
    Screen0_TempLabelWidget->fn->setMargins(Screen0_TempLabelWidget, 0, 0, 0, 0);
    Screen0_TempLabelWidget->fn->setString(Screen0_TempLabelWidget, (leString*)&string_TempLabel);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_TempLabelWidget);

    Screen0_TempUnitLabelWidget = leLabelWidget_New();
    Screen0_TempUnitLabelWidget->fn->setPosition(Screen0_TempUnitLabelWidget, 27, 16);
    Screen0_TempUnitLabelWidget->fn->setSize(Screen0_TempUnitLabelWidget, 9, 15);
    Screen0_TempUnitLabelWidget->fn->setScheme(Screen0_TempUnitLabelWidget, &WhitePixelScheme);
    Screen0_TempUnitLabelWidget->fn->setBackgroundType(Screen0_TempUnitLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_TempUnitLabelWidget->fn->setMargins(Screen0_TempUnitLabelWidget, 0, 0, 0, 0);
    Screen0_TempUnitLabelWidget->fn->setString(Screen0_TempUnitLabelWidget, (leString*)&string_TempUnitF);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_TempUnitLabelWidget);

    Screen0_DateLabelWidget = leLabelWidget_New();
    Screen0_DateLabelWidget->fn->setPosition(Screen0_DateLabelWidget, 2, 0);
    Screen0_DateLabelWidget->fn->setSize(Screen0_DateLabelWidget, 36, 15);
    Screen0_DateLabelWidget->fn->setScheme(Screen0_DateLabelWidget, &WhitePixelScheme);
    Screen0_DateLabelWidget->fn->setBackgroundType(Screen0_DateLabelWidget, LE_WIDGET_BACKGROUND_NONE);
    Screen0_DateLabelWidget->fn->setHAlignment(Screen0_DateLabelWidget, LE_HALIGN_RIGHT);
    Screen0_DateLabelWidget->fn->setString(Screen0_DateLabelWidget, (leString*)&string_DateLabel);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_DateLabelWidget);

    Screen0_LineWidget3 = leLineWidget_New();
    Screen0_LineWidget3->fn->setPosition(Screen0_LineWidget3, 3, 0);
    Screen0_LineWidget3->fn->setSize(Screen0_LineWidget3, 128, 1);
    Screen0_LineWidget3->fn->setScheme(Screen0_LineWidget3, &WhitePixelScheme);
    Screen0_LineWidget3->fn->setBackgroundType(Screen0_LineWidget3, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LineWidget3->fn->setEndPoint(Screen0_LineWidget3, 120, 0);
    Screen0_TopUIPanel->fn->addChild(Screen0_TopUIPanel, (leWidget*)Screen0_LineWidget3);

    Screen0_BottomUIPanel = leWidget_New();
    Screen0_BottomUIPanel->fn->setPosition(Screen0_BottomUIPanel, 0, 32);
    Screen0_BottomUIPanel->fn->setSize(Screen0_BottomUIPanel, 128, 32);
    Screen0_BottomUIPanel->fn->setBackgroundType(Screen0_BottomUIPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)Screen0_BottomUIPanel);

    Screen0_PlayPauseButton = leButtonWidget_New();
    Screen0_PlayPauseButton->fn->setPosition(Screen0_PlayPauseButton, 0, 2);
    Screen0_PlayPauseButton->fn->setSize(Screen0_PlayPauseButton, 30, 30);
    Screen0_PlayPauseButton->fn->setBackgroundType(Screen0_PlayPauseButton, LE_WIDGET_BACKGROUND_NONE);
    Screen0_PlayPauseButton->fn->setBorderType(Screen0_PlayPauseButton, LE_WIDGET_BORDER_NONE);
    Screen0_PlayPauseButton->fn->setToggleable(Screen0_PlayPauseButton, LE_TRUE);
    Screen0_PlayPauseButton->fn->setPressedImage(Screen0_PlayPauseButton, (leImage*)&PauseButton20);
    Screen0_PlayPauseButton->fn->setReleasedImage(Screen0_PlayPauseButton, (leImage*)&PlayButton20);
    Screen0_PlayPauseButton->fn->setPressedOffset(Screen0_PlayPauseButton, 0);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_PlayPauseButton);

    Screen0_LineWidget1 = leLineWidget_New();
    Screen0_LineWidget1->fn->setPosition(Screen0_LineWidget1, 35, 26);
    Screen0_LineWidget1->fn->setSize(Screen0_LineWidget1, 60, 1);
    Screen0_LineWidget1->fn->setScheme(Screen0_LineWidget1, &WhitePixelScheme);
    Screen0_LineWidget1->fn->setBackgroundType(Screen0_LineWidget1, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LineWidget1->fn->setEndPoint(Screen0_LineWidget1, 60, 0);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_LineWidget1);

    Screen0_PanelWidget0 = leWidget_New();
    Screen0_PanelWidget0->fn->setPosition(Screen0_PanelWidget0, 38, 24);
    Screen0_PanelWidget0->fn->setSize(Screen0_PanelWidget0, 10, 5);
    Screen0_PanelWidget0->fn->setScheme(Screen0_PanelWidget0, &WhiteBackgroundScheme);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_PanelWidget0);

    Screen0_LineWidget2 = leLineWidget_New();
    Screen0_LineWidget2->fn->setPosition(Screen0_LineWidget2, 3, 0);
    Screen0_LineWidget2->fn->setSize(Screen0_LineWidget2, 128, 1);
    Screen0_LineWidget2->fn->setScheme(Screen0_LineWidget2, &WhitePixelScheme);
    Screen0_LineWidget2->fn->setBackgroundType(Screen0_LineWidget2, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LineWidget2->fn->setEndPoint(Screen0_LineWidget2, 120, 0);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_LineWidget2);

    Screen0_LabelWidget0 = leLabelWidget_New();
    Screen0_LabelWidget0->fn->setPosition(Screen0_LabelWidget0, 31, 2);
    Screen0_LabelWidget0->fn->setSize(Screen0_LabelWidget0, 72, 20);
    Screen0_LabelWidget0->fn->setScheme(Screen0_LabelWidget0, &WhitePixelScheme);
    Screen0_LabelWidget0->fn->setBackgroundType(Screen0_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    Screen0_LabelWidget0->fn->setString(Screen0_LabelWidget0, (leString*)&string_SongLabel);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_LabelWidget0);

    Screen0_MusicBar0 = leWidget_New();
    Screen0_MusicBar0->fn->setPosition(Screen0_MusicBar0, 102, 7);
    Screen0_MusicBar0->fn->setSize(Screen0_MusicBar0, 3, 20);
    Screen0_MusicBar0->fn->setScheme(Screen0_MusicBar0, &WhiteBackgroundScheme);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_MusicBar0);

    Screen0_MusicBar1 = leWidget_New();
    Screen0_MusicBar1->fn->setPosition(Screen0_MusicBar1, 107, 7);
    Screen0_MusicBar1->fn->setSize(Screen0_MusicBar1, 3, 20);
    Screen0_MusicBar1->fn->setScheme(Screen0_MusicBar1, &WhiteBackgroundScheme);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_MusicBar1);

    Screen0_MusicBar2 = leWidget_New();
    Screen0_MusicBar2->fn->setPosition(Screen0_MusicBar2, 112, 7);
    Screen0_MusicBar2->fn->setSize(Screen0_MusicBar2, 3, 20);
    Screen0_MusicBar2->fn->setScheme(Screen0_MusicBar2, &WhiteBackgroundScheme);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_MusicBar2);

    Screen0_MusicBar3 = leWidget_New();
    Screen0_MusicBar3->fn->setPosition(Screen0_MusicBar3, 117, 7);
    Screen0_MusicBar3->fn->setSize(Screen0_MusicBar3, 3, 20);
    Screen0_MusicBar3->fn->setScheme(Screen0_MusicBar3, &WhiteBackgroundScheme);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_MusicBar3);

    Screen0_MusicBar4 = leWidget_New();
    Screen0_MusicBar4->fn->setPosition(Screen0_MusicBar4, 122, 7);
    Screen0_MusicBar4->fn->setSize(Screen0_MusicBar4, 3, 20);
    Screen0_MusicBar4->fn->setScheme(Screen0_MusicBar4, &WhiteBackgroundScheme);
    Screen0_BottomUIPanel->fn->addChild(Screen0_BottomUIPanel, (leWidget*)Screen0_MusicBar4);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_MONOCHROME);

    Screen0_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_Screen0(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    Screen0_OnUpdate(); // raise event
}

void screenHide_Screen0(void)
{
    Screen0_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    Screen0_BackgroundPanel = NULL;
    Screen0_TopUIPanel = NULL;
    Screen0_BottomUIPanel = NULL;
    Screen0_HourLabelWidget = NULL;
    Screen0_LineWidget0 = NULL;
    Screen0_AMPMLabelWidget = NULL;
    Screen0_ColonLabelWidget = NULL;
    Screen0_MinLabelWidget = NULL;
    Screen0_TempLabelWidget = NULL;
    Screen0_TempUnitLabelWidget = NULL;
    Screen0_DateLabelWidget = NULL;
    Screen0_LineWidget3 = NULL;
    Screen0_PlayPauseButton = NULL;
    Screen0_LineWidget1 = NULL;
    Screen0_PanelWidget0 = NULL;
    Screen0_LineWidget2 = NULL;
    Screen0_LabelWidget0 = NULL;
    Screen0_MusicBar0 = NULL;
    Screen0_MusicBar1 = NULL;
    Screen0_MusicBar2 = NULL;
    Screen0_MusicBar3 = NULL;
    Screen0_MusicBar4 = NULL;


    showing = LE_FALSE;
}

void screenDestroy_Screen0(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_Screen0(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}

