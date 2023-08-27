#include <cstdlib>
#include <iostream>
#include <tuple>
#include <ctime>

#include "Game.h"
#include "Event.h"
#include "Vendor.h"
#include "GameEventHandler.h"
#include "Menu.h"

Game::Game(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(EXIT_FAILURE);

	gameWindow = SDL_CreateWindow("NERRSID",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN);
	if (!gameWindow)
		exit(EXIT_FAILURE);

	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

	this->tileMap = new Tilemap(gameRenderer);
}
Game::~Game()
{
	SDL_DestroyRenderer(gameRenderer);
	tileMap->~Tilemap();
	SDL_Quit();
}
SDL_Renderer* Game::GetRenderer() const
{
	return gameRenderer;
}
Tilemap* Game::GetTileMap() const
{
	return tileMap;
}
int Game::GetScreenWidth() const
{
	return screenWidth;
}
int Game::GetScreenHeight() const
{
	return screenHeight;
}
void Game::Build(int gameScreenWidth, int gameScreenHeight)
{
	srand(time(nullptr));

	Game* game = new Game(gameScreenWidth, gameScreenHeight);
	Map* map = new Map();
	UI* userInterface = new UI(game->GetRenderer(), game->GetScreenWidth(), game->GetScreenHeight());
	auto* player = new Player("foo", Warrior, 1, 1);
	Vendor* vendor = new Vendor("Bar", 2, 1);
	Event* eventGame = new Event(EmptyEvent, "");
	Item* item = new Item("foo", 2, 1, 1);
	Item* item_two = new Item("asdf", 3, 5, 6);
	Item* item_three = new Item("bar", 3, 5, 6);
	Item* item_four = new Item("dsagr", 3, 5, 6);
	Item* item_five = new Item("foofdsbar", 3, 5, 6);
	Item* item_six = new Item("for", 3, 5, 6);
	Item* item_seven = new Item("fo4obar", 3, 5, 6);
	Item* item_eight = new Item("foo21", 3, 5, 6);
	Item* item_nine = new Item("f2obar", 3, 5, 6);

	player->InsertIntoInventory(*item);
	player->InsertIntoInventory(*item_two);
	player->InsertIntoInventory(*item_three);
	player->InsertIntoInventory(*item_four);
	player->InsertIntoInventory(*item_five);

	vendor->InsertIntoInventory(*item_six);
	vendor->InsertIntoInventory(*item_seven);
	vendor->InsertIntoInventory(*item_eight);
	vendor->InsertIntoInventory(*item_nine);

	map->InsertVendor(vendor);

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		SDL_Event eventSDL;

		*eventGame = GameEventHandler::CollisionHandler(*player, *map);

		userInterface->RefreshUserInterface();
		userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
		userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
		userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
		userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), eventGame->GetEventMessage());
		SDL_RenderPresent(game->GetRenderer());

		while (SDL_PollEvent(&eventSDL))
		{
			if (eventSDL.type == SDL_QUIT)
				gameIsRunning = false;
			else if (eventSDL.type == SDL_KEYDOWN)
			{
				switch (GameEventHandler::KeyPressHandler(player, eventSDL, *eventGame, *map))
				{
				case ExitKeypressHandled:
					gameIsRunning = false;
					break;
				case EnterKeypressHandled:
					if (eventGame->GetTypeOfEvent() == VendorEvent)
					{
						bool vendorShoppingFlag = true;
						Menu* menu = new Menu(vendor->GetItemsInInventory());

						while (vendorShoppingFlag)
						{
							userInterface->RefreshUserInterface();
							userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
							userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
							userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
							userInterface->DrawVendorPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), vendor, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
							SDL_RenderPresent(game->GetRenderer());
							while (SDL_PollEvent(&eventSDL))
							{
								if (eventSDL.type == SDL_QUIT)
								{
									vendorShoppingFlag = false;
									gameIsRunning = false;
								}
								else if (eventSDL.type == SDL_KEYDOWN)
								{
									switch (GameEventHandler::VendorKeyPressHandler(eventSDL, *eventGame))
									{
									case ExitKeypressHandled:
										vendorShoppingFlag = false;
										break;
									case EnterKeypressHandled:
										userInterface->RefreshUserInterface();
										userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
										userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
										userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
										userInterface->DrawVendorPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), vendor, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
										userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), "You bought something");
										SDL_RenderPresent(game->GetRenderer());
										break;
									case ScrollDownKeypressHandled:
										menu->ScrollDown();
										break;
									case ScrollUpKeypressHandled:
										menu->ScrollUp();
										break;
									}
								}
							}
						}
					}
					break;
				case InventoryKeypressHandled:
					bool inventoryBrowsingFlag = true;
					Menu* menu = new Menu(player->GetItemsInInventory());

					std::string lastMessage;
					while (inventoryBrowsingFlag)
					{
						userInterface->RefreshUserInterface();
						userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
						userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
						userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
						userInterface->DrawInventoryPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
						userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), lastMessage);
						SDL_RenderPresent(game->GetRenderer());
						while (SDL_PollEvent(&eventSDL))
						{
							if (eventSDL.type == SDL_QUIT)
							{
								inventoryBrowsingFlag = false;
								gameIsRunning = false;
							}
							else if (eventSDL.type == SDL_KEYDOWN)
							{
								switch (GameEventHandler::InventoryKeyPressHandler(eventSDL))
								{
								case ExitKeypressHandled:
									inventoryBrowsingFlag = false;
									break;
								case EnterKeypressHandled:
									userInterface->RefreshUserInterface();
									userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
									userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
									userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
									if (!player->GetInventory()->at(menu->GetSelectedItem()).GetIsEquipped())
									{
										lastMessage = player->GetInventory()->at(menu->GetSelectedItem()).EquipItem(player);
										userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), lastMessage);
									}
									else
									{
										lastMessage = player->GetInventory()->at(menu->GetSelectedItem()).UnequipItem(player);
										userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), lastMessage);
									}
									userInterface->DrawInventoryPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
									SDL_RenderPresent(game->GetRenderer());
									break;
								case ScrollDownKeypressHandled:
									menu->ScrollDown();
									break;
								case ScrollUpKeypressHandled:
									menu->ScrollUp();
									break;
								}
							}
						}
					}
					break;
				}
			}
		}
	}
}