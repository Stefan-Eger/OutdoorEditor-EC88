#ifndef EVENT_LISTENER_GUI_H
#define EVENT_LISTENER_GUI_H

using namespace ve;
namespace oe {

	class EventListenerGUI : public VEEventListener
	{
	protected:
		virtual void onDrawOverlay(veEvent event) override;

	public:
		EventListenerGUI(std::string name);
		virtual ~EventListenerGUI();

	};
}
#endif // !EVENTLISTENER_GUI

