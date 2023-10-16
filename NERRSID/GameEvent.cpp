#include "GameEvent.h"

GameEvent::GameEvent() : typeOfEvent(EmptyEvent), eventMessage("")
{
}


GameEvent::GameEvent(gameEventType typeOfEvent, std::string eventMessage) : typeOfEvent(typeOfEvent), eventMessage(std::move(eventMessage))
{
}

GameEvent::~GameEvent() = default;

std::string GameEvent::GetEventMessage() const
{
	return this->eventMessage;
}

gameEventType GameEvent::GetTypeOfEvent() const
{
	return this->typeOfEvent;
}

void GameEvent::SetEventMessage(std::string eventMessage)
{
	this->eventMessage = std::move(eventMessage);
}

void GameEvent::SetTypeOfEvent(gameEventType typeOfEvent)
{
	this->typeOfEvent = typeOfEvent;
}
