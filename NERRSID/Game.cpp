#include <cstdlib>
#include <iostream>
#include <ctime>

#include "Game.h"
#include "Event.h"
#include "Vendor.h"
#include "Handler.h"

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
	auto* player = new Player("foo", Warrior);
	Vendor* vendor = new Vendor("Bar", 2, 1);
	Event* eventGame = new Event(EmptyEvent, "");
	Item* item = new Item("foo", 2, 1, 1);
	Item* item_two = new Item("asdf", 3, 5, 6);

	player->InsertIntoPlayerInventory(*item);
	player->InsertIntoPlayerInventory(*item_two);

	map->InsertVendor(vendor);

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		SDL_Event eventSDL;

		*eventGame = Handler::CollisionHandler(*player, *map);

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
				switch (Handler::KeyPressHandler(player, eventSDL, *eventGame, *map))
				{
				case ExitKeypressHandled:
					gameIsRunning = false;
					break;
				case EnterKeypressHandled:
					if (eventGame->GetTypeOfEvent() == VendorEvent)
					{
						userInterface->RefreshUserInterface();
						userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
						userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
						userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
						userInterface->DrawVendorPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), vendor);
						SDL_RenderPresent(game->GetRenderer());

						bool vendorShoppingFlag = true;

						while (vendorShoppingFlag)
						{
							while (SDL_PollEvent(&eventSDL))
							{
								if (eventSDL.type == SDL_QUIT)
								{
									vendorShoppingFlag = false;
									gameIsRunning = false;
								}
								else if (eventSDL.type == SDL_KEYDOWN)
								{
									switch (Handler::VendorKeyPressHandler(eventSDL, *eventGame))
									{
									case ExitKeypressHandled:
										vendorShoppingFlag = false;
										break;
									case EnterKeypressHandled:
										userInterface->RefreshUserInterface();
										userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
										userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
										userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
										userInterface->DrawVendorPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), vendor);
										userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), "You bought something");
										SDL_RenderPresent(game->GetRenderer());
										break;
									}
								}
							}
						}
					}
					break;
				case InventoryKeypressHandled:
					bool inventoryBrowsingFlag = true;
					int selectedItem = 0;
					std::string lastMessage;
					while (inventoryBrowsingFlag)
					{
						userInterface->RefreshUserInterface();
						userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
						userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
						userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
						userInterface->DrawInventoryPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player, selectedItem);
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
								switch (Handler::InventoryKeyPressHandler(eventSDL))
								{
								case ExitKeypressHandled:
									inventoryBrowsingFlag = false;
									break;
								case EnterKeypressHandled:
									userInterface->RefreshUserInterface();
									userInterface->DrawMap(game->GetRenderer(), map, game->GetTileMap());
									userInterface->DrawPlayer(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
									userInterface->DrawPlayerInfo(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player);
									if (!player->GetPlayerInventory()->at(selectedItem).GetIsEquipped())
									{
										userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), "You equipped " + player->GetPlayerInventory()->at(selectedItem).GetItemName());
										player->GetPlayerInventory()->at(selectedItem).SetIsEquipped(true);
										lastMessage = "You equipped " + player->GetPlayerInventory()->at(selectedItem).GetItemName();
									}
									else
									{
										userInterface->DrawStatusBar(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), "You unequipped " + player->GetPlayerInventory()->at(selectedItem).GetItemName());
										player->GetPlayerInventory()->at(selectedItem).SetIsEquipped(false);
										lastMessage = "You unequipped " + player->GetPlayerInventory()->at(selectedItem).GetItemName();
									}
									userInterface->DrawInventoryPopup(game->GetRenderer(), game->GetTileMap()->GetTileMapTexture(), player, selectedItem);
									SDL_RenderPresent(game->GetRenderer());
									break;
								case ScrollDownKeypressHandled:
									if (selectedItem < player->GetPlayerItemsInInventory() - 1)
										selectedItem++;
									break;
								case ScrollUpKeypressHandled:
									if (selectedItem > 0)
										selectedItem--;
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