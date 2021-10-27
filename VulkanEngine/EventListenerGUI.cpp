#include "OEInclude.h"
namespace oe {

	void EventListenerGUI::onDrawOverlay(veEvent event) {
		/*
		VESubrenderFW_Nuklear* pSubrender = (VESubrenderFW_Nuklear*)getRendererPointer()->getOverlay();
		if (pSubrender == nullptr) return;

		struct nk_context* ctx = pSubrender->getContext();

		if (!OutdoorEditorInfo::g_gameLost) {
			if (nk_begin(ctx, "", nk_rect(0, 0, 200, 170), NK_WINDOW_BORDER)) {
				char outbuffer[100];
				nk_layout_row_dynamic(ctx, 45, 1);
				sprintf(outbuffer, "Score: %03d", OutdoorEditorInfo::g_score);
				nk_label(ctx, outbuffer, NK_TEXT_LEFT);

				nk_layout_row_dynamic(ctx, 45, 1);
				sprintf(outbuffer, "Time: %004.1lf", OutdoorEditorInfo::g_time);
				nk_label(ctx, outbuffer, NK_TEXT_LEFT);
			}
		}
		else {
			if (nk_begin(ctx, "", nk_rect(500, 500, 200, 170), NK_WINDOW_BORDER)) {
				nk_layout_row_dynamic(ctx, 45, 1);
				nk_label(ctx, "Game Over", NK_TEXT_LEFT);
				if (nk_button_label(ctx, "Restart")) {
					OutdoorEditorInfo::g_restart = true;
				}
			}

		};

		nk_end(ctx);
		*/
	}

	EventListenerGUI::EventListenerGUI(std::string name) : VEEventListener(name) {}

	EventListenerGUI::~EventListenerGUI(){}
}