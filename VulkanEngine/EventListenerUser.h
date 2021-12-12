#ifndef EVENT_LISTENER_USER_H
#define EVENT_LISTENER_USER_H

using namespace ve;
namespace oe {
	//Copy Pasted most of it but modified to suit my needs can not be bypassed 
	//with events since the events will be consumed by default
	class EventListenerUser : public VEEventListenerGLFW
	{

		Ray createRayThroughPixel(const float& cursorX, const float& cursorY ) const;


		bool mouseMoveBrush(const float& x, const float& y) const;
		bool mouseMoveCameraMovement(const float& x, const float& y, const float& dt);
		
	protected:

		virtual bool onMouseScroll(veEvent event) override;
		virtual bool onMouseMove(veEvent event) override;
		virtual bool onMouseButton(veEvent event) override;
		virtual bool onKeyboard(veEvent event) override;

	public:
		EventListenerUser(std::string name);
		virtual ~EventListenerUser();

	};
}
#endif //!EVENT_LISTENER_MOUSE_H		
