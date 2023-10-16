#include "GameEvent.h"

GameEvent::GameEvent() : TypeOfEvent(EmptyEvent)
{
}

GameEvent::GameEvent(const GameEventType typeOfEvent, std::string eventMessage) : TypeOfEvent(typeOfEvent), EventMessage(std::move(eventMessage))
{
}

GameEvent::~GameEvent() = default;

std::string GameEvent::GetEventMessage() const
{
	return this->EventMessage;
}

GameEventType GameEvent::GetTypeOfEvent() const
{
	return this->TypeOfEvent;
}

void GameEvent::SetEventMessage(std::string eventMessage)
{
	this->EventMessage = std::move(eventMessage);
}

void GameEvent::SetTypeOfEvent(const GameEventType typeOfEvent)
{
	this->TypeOfEvent = typeOfEvent;
}