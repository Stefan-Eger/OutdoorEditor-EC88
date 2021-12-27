#ifndef EVENT_LISTENER_GUI_H
#define EVENT_LISTENER_GUI_H

using namespace ve;
namespace oe {

	class EventListenerGUI : public VEEventListener
	{
		OutdoorEditor::oeEditingModes m_editingmode = OutdoorEditor::oeEditingModes::TERRAIN_EDITING_TEXTURE;
		OutdoorEditor::oeBrushModes m_brushMode = OutdoorEditor::oeBrushModes::BRUSH_DRILL;
		oeTerrainMaterial m_activeMaterial = oeTerrainMaterial::OE_TEXTURE_GRASS;

		const float OPTION_LABEL_SIZE = 30.0f;

		void drawBrushModes(nk_context* ctx);
		void drawEditModes(nk_context* ctx);
		void drawTerrainMaterials(nk_context* ctx);

	protected:
		virtual void onDrawOverlay(veEvent event) override;

	public:
		EventListenerGUI(std::string name);
		virtual ~EventListenerGUI();

	};
}
#endif // !EVENTLISTENER_GUI

