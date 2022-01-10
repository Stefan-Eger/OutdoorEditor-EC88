#include "OEInclude.h"
namespace oe {

	void EventListenerGUI::onDrawOverlay(veEvent event) {
		if (OutdoorEditorInfo::editor == nullptr) return;
		VESubrenderFW_Nuklear* pSubrender = (VESubrenderFW_Nuklear*)getRendererPointer()->getOverlay();
		if (pSubrender == nullptr) return;
		struct nk_context* ctx = pSubrender->getContext();

		VkExtent2D window = getWindowPointer()->getExtent();

		//Window Left Side
		float windowHeight = window.height * (4.0f / 5.0f);
		float windowWidth = window.width * (2.0f / 5.0f);

		if (nk_begin(ctx, "Outdoor Editor", nk_rect(0, 0, windowWidth, windowHeight), NK_WINDOW_TITLE | NK_WINDOW_SCALABLE | NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_SCROLL_AUTO_HIDE)) {
			
			//EDIT OPTIONS
			drawEditModes(ctx);

			if (m_editingmode == OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME) 
				drawBrushModes(ctx);
			
			if (m_editingmode == OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME || m_editingmode == OutdoorEditor::oeEditingModes::TERRAIN_EDITING_TEXTURE)
				drawTerrainMaterials(ctx);

			if (m_editingmode == OutdoorEditor::oeEditingModes::TREE_PLACEMENT) {
				drawAvailableTrees(ctx);

			}
			if (m_editingmode == OutdoorEditor::oeEditingModes::BILLBOARD_PLACEMENT) {
				drawAvailableBillboards(ctx);
			}
			if (m_editingmode == OutdoorEditor::oeEditingModes::OBJECT_PLACEMENT) {
				drawAvailableStones(ctx);
			}

			auto brush = OutdoorEditorInfo::editor->getActiveBrush();
			VESubrenderFW_Trilinear::brushCircle.isActive = brush == nullptr ? VK_FALSE : VK_TRUE;

			if (brush != nullptr) {
				VESubrenderFW_Trilinear::brushCircle.radius = brush->getRadius();
			}

			//SAVE AND LOAD
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 2);
			if (nk_button_label(ctx, "Save")) {
				OutdoorEditorInfo::editor->save(".", "TEST_SAVE");
			}
			if (nk_button_label(ctx, "Load")) {
				OutdoorEditorInfo::editor->load(".", "TEST_SAVE");
			}
		}
		
		nk_end(ctx);
	}

	void EventListenerGUI::drawBrushModes(nk_context* ctx) {
		if (nk_tree_push(ctx, NK_TREE_TAB, "Brushes", NK_MINIMIZED)) {

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Drill", m_brushMode == OutdoorEditor::oeBrushModes::BRUSH_DRILL)) {
				m_brushMode = OutdoorEditor::oeBrushModes::BRUSH_DRILL;
			}

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Sphere Full", m_brushMode == OutdoorEditor::oeBrushModes::BRUSH_SPHERE_FULL)) {
				m_brushMode = OutdoorEditor::oeBrushModes::BRUSH_SPHERE_FULL;
			}

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Sphere Smooth", m_brushMode == OutdoorEditor::oeBrushModes::BRUSH_SPHERE_SMOOTH)) {
				m_brushMode = OutdoorEditor::oeBrushModes::BRUSH_SPHERE_SMOOTH;
			}
			OutdoorEditorInfo::editor->setBrushMode(m_brushMode);
			nk_tree_pop(ctx);
		}
	}
	void EventListenerGUI::drawEditModes(nk_context* ctx)
	{

		if (nk_tree_push(ctx, NK_TREE_TAB, "Editing Modes",  NK_MINIMIZED)) {

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Volume", m_editingmode == OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME)) {
				m_editingmode = OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Texture", m_editingmode == OutdoorEditor::oeEditingModes::TERRAIN_EDITING_TEXTURE)) {
				m_editingmode = OutdoorEditor::oeEditingModes::TERRAIN_EDITING_TEXTURE;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Trees", m_editingmode == OutdoorEditor::oeEditingModes::TREE_PLACEMENT)) {
				m_editingmode = OutdoorEditor::oeEditingModes::TREE_PLACEMENT;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Billboards", m_editingmode == OutdoorEditor::oeEditingModes::BILLBOARD_PLACEMENT)) {
				m_editingmode = OutdoorEditor::oeEditingModes::BILLBOARD_PLACEMENT;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Objects", m_editingmode == OutdoorEditor::oeEditingModes::OBJECT_PLACEMENT)) {
				m_editingmode = OutdoorEditor::oeEditingModes::OBJECT_PLACEMENT;
			}

			OutdoorEditorInfo::editor->setEditingMode(m_editingmode);

			nk_tree_pop(ctx);
		}
	}

	void EventListenerGUI::drawTerrainMaterials(nk_context* ctx)
	{
		if (nk_tree_push(ctx, NK_TREE_TAB, "Materials", NK_MINIMIZED)) {

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Dirt", m_activeMaterial == oeTerrainMaterial::OE_TEXTURE_DIRT)) {
				m_activeMaterial = oeTerrainMaterial::OE_TEXTURE_DIRT;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Grass", m_activeMaterial == oeTerrainMaterial::OE_TEXTURE_GRASS)) {
				m_activeMaterial = oeTerrainMaterial::OE_TEXTURE_GRASS;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Mud", m_activeMaterial == oeTerrainMaterial::OE_TEXTURE_MUD)) {
				m_activeMaterial = oeTerrainMaterial::OE_TEXTURE_MUD;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Wet Dirt", m_activeMaterial == oeTerrainMaterial::OE_TEXTURE_WET_DIRT)) {
				m_activeMaterial = oeTerrainMaterial::OE_TEXTURE_WET_DIRT;
			}
		
			OutdoorEditorInfo::editor->setActiveMaterial(m_activeMaterial);

			nk_tree_pop(ctx);
		}
	}

	void EventListenerGUI::drawAvailableTrees(nk_context* ctx)
	{
		if (nk_tree_push(ctx, NK_TREE_TAB, "Trees", NK_MINIMIZED)) {

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Pine Tree 01", m_activeModel == oeEntityModel::PINE_TREE_01)) {
				m_activeModel = oeEntityModel::PINE_TREE_01;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Pine Tree 02", m_activeModel == oeEntityModel::PINE_TREE_02)) {
				m_activeModel = oeEntityModel::PINE_TREE_02;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Oak Tree 01", m_activeModel == oeEntityModel::OAK_TREE_01)) {
				m_activeModel = oeEntityModel::OAK_TREE_01;
			}
			OutdoorEditorInfo::editor->setActiveModel(m_activeModel);
			nk_tree_pop(ctx);
		}
	}

	void EventListenerGUI::drawAvailableStones(nk_context* ctx)
	{
		if (nk_tree_push(ctx, NK_TREE_TAB, "Stones", NK_MINIMIZED)) {

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Stone 01", m_activeModel == oeEntityModel::STONE_01)) {
				m_activeModel = oeEntityModel::STONE_01;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Stone 02", m_activeModel == oeEntityModel::STONE_02)) {
				m_activeModel = oeEntityModel::STONE_02;
			}
			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Stone 03", m_activeModel == oeEntityModel::STONE_03)) {
				m_activeModel = oeEntityModel::STONE_03;
			}
			OutdoorEditorInfo::editor->setActiveModel(m_activeModel);
			nk_tree_pop(ctx);
		}
	}

	void EventListenerGUI::drawAvailableBillboards(nk_context* ctx)
	{
		if (nk_tree_push(ctx, NK_TREE_TAB, "Billboards", NK_MINIMIZED)) {

			nk_layout_row_dynamic(ctx, OPTION_LABEL_SIZE, 1);
			if (nk_option_label(ctx, "Grass 01", m_activeModel == oeEntityModel::BILLBOARD_GRASS_01)) {
				m_activeModel = oeEntityModel::BILLBOARD_GRASS_01;
			}

			OutdoorEditorInfo::editor->setActiveModel(m_activeModel);
			nk_tree_pop(ctx);
		}
	}


	EventListenerGUI::EventListenerGUI(std::string name) : VEEventListener(name) {}

	EventListenerGUI::~EventListenerGUI(){}
}