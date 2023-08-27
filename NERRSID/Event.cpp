#include "Event.h"

Event::Event(eventType typeOfEvent, std::string eventMessage) : typeOfEvent(typeOfEvent), eventMessage(std::move(eventMessage))
{
}

Event::~Event() = default;

std::string Event::GetEventMessage() const
{
	return this->eventMessage;
}

eventType Event::GetTypeOfEvent() const
{
	return this->typeOfEvent;
}

void Event::SetEventMessage(std::string eventMessage)
{
	this->eventMessage = std::move(eventMessage);
}

void Event::SetTypeOfEvent(eventType typeOfEvent)
{
	this->typeOfEvent = typeOfEvent;
}
