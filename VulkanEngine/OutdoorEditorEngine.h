#ifndef OUTDOOR_EDITOR_ENGINE_H
#define OUTDOOR_EDITOR_ENGINE_H

using namespace ve;

namespace oe {
	class OutdoorEditorEngine : public VEEngine {

		const int WORLD_CHUNKS_WIDTH = 10;
		const int WORLD_CHUNKS_HEIGHT = 2;
		const int WORLD_CHUNKS_DEPTH = 10;

	public:
		OutdoorEditorEngine(bool debug = false) : VEEngine(debug) {};
		~OutdoorEditorEngine() {};
		virtual void registerEventListeners() override;
		virtual void loadLevel(uint32_t numLevel = 1) override;
		virtual void end() override;
	};
}
#endif