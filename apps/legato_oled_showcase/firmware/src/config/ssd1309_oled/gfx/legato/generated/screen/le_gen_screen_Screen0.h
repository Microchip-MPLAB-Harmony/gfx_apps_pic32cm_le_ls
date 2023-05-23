#ifndef LE_GEN_SCREEN_SCREEN0_H
#define LE_GEN_SCREEN_SCREEN0_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* Screen0_BackgroundPanel;
extern leWidget* Screen0_TopUIPanel;
extern leWidget* Screen0_BottomUIPanel;
extern leLabelWidget* Screen0_HourLabelWidget;
extern leLineWidget* Screen0_LineWidget0;
extern leLabelWidget* Screen0_AMPMLabelWidget;
extern leLabelWidget* Screen0_ColonLabelWidget;
extern leLabelWidget* Screen0_MinLabelWidget;
extern leLabelWidget* Screen0_TempLabelWidget;
extern leLabelWidget* Screen0_TempUnitLabelWidget;
extern leLabelWidget* Screen0_DateLabelWidget;
extern leLineWidget* Screen0_LineWidget3;
extern leButtonWidget* Screen0_PlayPauseButton;
extern leLineWidget* Screen0_LineWidget1;
extern leWidget* Screen0_PanelWidget0;
extern leLineWidget* Screen0_LineWidget2;
extern leLabelWidget* Screen0_LabelWidget0;
extern leWidget* Screen0_MusicBar0;
extern leWidget* Screen0_MusicBar1;
extern leWidget* Screen0_MusicBar2;
extern leWidget* Screen0_MusicBar3;
extern leWidget* Screen0_MusicBar4;

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_Screen0(void); // called when Legato is initialized
leResult screenShow_Screen0(void); // called when screen is shown
void screenHide_Screen0(void); // called when screen is hidden
void screenDestroy_Screen0(void); // called when Legato is destroyed
void screenUpdate_Screen0(void); // called when Legato is updating

leWidget* screenGetRoot_Screen0(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void Screen0_OnShow(void); // called when this screen is shown
void Screen0_OnHide(void); // called when this screen is hidden
void Screen0_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SCREEN0_H
