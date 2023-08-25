#pragma once
#include <string>

typedef enum eventType_t
{
	EmptyEvent,
	AmbushEvent,
	VendorEvent,
	GainExperienceEvent,
	UseConsumableEvent,
	ChestEvent
} eventType;

class Event
{
private:
	eventType typeOfEvent;
	std::string eventMessage;
	/// vendor inv
public:
	Event(eventType typeOfEvent, std::string eventMessage);
	~Event();
	eventType GetTypeOfEvent() const;
	std::string GetEventMessage() const;
	void SetEventMessage(std::string eventMessage);

};

