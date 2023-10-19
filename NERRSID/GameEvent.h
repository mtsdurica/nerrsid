#pragma once
#include <string>

typedef enum GameEventType
{
	EmptyEvent,
	AmbushEvent,
	VendorEvent,
	GainExperienceEvent,
	UseConsumableEvent,
	ChestEvent,
	InventoryEvent,
	StairsEvent
} GameEventType;

class GameEvent
{
private:
	GameEventType TypeOfEvent;
	std::string EventMessage;
	/// TODO: vendor inv
public:
	GameEvent();
	GameEvent(GameEventType typeOfEvent, std::string eventMessage);
	~GameEvent();
	/// <summary>
	/// Get event type
	/// </summary>
	/// <returns>Event type</returns>
	GameEventType GetTypeOfEvent() const;
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
	void SetTypeOfEvent(GameEventType typeOfEvent);
};