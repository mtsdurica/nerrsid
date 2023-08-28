#pragma once
#include <string>

typedef enum gameEventType
{
	EmptyEvent,
	AmbushEvent,
	VendorEvent,
	GainExperienceEvent,
	UseConsumableEvent,
	ChestEvent
} gameEventType;

class GameEvent
{
private:
	gameEventType typeOfEvent;
	std::string eventMessage;
	/// TODO: vendor inv
public:
	GameEvent(gameEventType typeOfEvent, std::string eventMessage);
	~GameEvent();
	/// <summary>
	/// Get event type
	/// </summary>
	/// <returns>Event type</returns>
	gameEventType GetTypeOfEvent() const;
	/// <summary>
	/// Get event message
	/// </summary>
	/// <returns>Event message</returns>
	std::string GetEventMessage() const;
	/// <summary>
	/// Set the event message
	/// </summary>
	/// <param name="eventMessage">New event message</param>
	void SetEventMessage(std::string eventMessage);
	/// <summary>
	/// Set type of the game event
	/// </summary>
	/// <param name="typeOfEvent">New type of event</param>
	void SetTypeOfEvent(gameEventType typeOfEvent);
};

