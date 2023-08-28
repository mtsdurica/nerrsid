#include <cstdlib>
#include <iostream>
#include <tuple>
#include <ctime>

#include "Game.h"
#include "GameEvent.h"
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
	delete tileMap;
	SDL_DestroyRenderer(this->gameRenderer);
	SDL_DestroyWindow(this->gameWindow);
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

	Game game(gameScreenWidth, gameScreenHeight);
	Map map;
	UI userInterface(game.GetRenderer(), game.GetScreenWidth(), game.GetScreenHeight());
	Player player("foo", Warrior, 1, 1);
	GameEvent eventGame(EmptyEvent, "");
	std::array<Vendor, 5> mapVendors = map.GetMapVendors();
	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		SDL_Event eventSDL;

		eventGame = GameEventHandler::CollisionHandler(player, map);

		userInterface.RefreshUserInterface();
		userInterface.DrawMap(game.GetRenderer(), &map, game.GetTileMap());
		userInterface.DrawPlayer(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
		userInterface.DrawPlayerInfo(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
		userInterface.DrawStatusBar(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), eventGame.GetEventMessage());
		SDL_RenderPresent(game.GetRenderer());

		while (SDL_PollEvent(&eventSDL))
		{
			if (eventSDL.type == SDL_QUIT)
				gameIsRunning = false;
			else if (eventSDL.type == SDL_KEYDOWN)
			{
				switch (GameEventHandler::KeyPressHandler(&player, &eventSDL, map.GetMapTiles()))
				{
				case ExitKeypressHandled:
					gameIsRunning = false;
					break;
				case EnterKeypressHandled:
					if (eventGame.GetTypeOfEvent() == VendorEvent)
					{
						Vendor* vendor = Map::FindVendor(&mapVendors, map.GetNumberOfVendors(), player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
						bool vendorShoppingFlag = true;
						Menu menu(vendor->GetItemsInInventory());
						std::string message = "";
						bool itemSold = false;

						while (vendorShoppingFlag)
						{
							userInterface.RefreshUserInterface();
							userInterface.DrawMap(game.GetRenderer(), &map, game.GetTileMap());
							userInterface.DrawPlayer(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
							userInterface.DrawPlayerInfo(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
							userInterface.DrawVendorPopup(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), vendor, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
							userInterface.DrawStatusBar(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), message);
							SDL_RenderPresent(game.GetRenderer());
							while (SDL_PollEvent(&eventSDL))
							{
								if (eventSDL.type == SDL_QUIT)
								{
									vendorShoppingFlag = false;
									gameIsRunning = false;
								}
								else if (eventSDL.type == SDL_KEYDOWN)
								{
									switch (GameEventHandler::VendorKeyPressHandler(&eventSDL))
									{
									case ExitKeypressHandled:
										vendorShoppingFlag = false;
										break;
									case EnterKeypressHandled:
										userInterface.RefreshUserInterface();
										userInterface.DrawMap(game.GetRenderer(), &map, game.GetTileMap());
										userInterface.DrawPlayer(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
										userInterface.DrawPlayerInfo(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
										userInterface.DrawVendorPopup(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), vendor, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
										if (vendor->GetItemsInInventory())
										{
											std::tie(message, itemSold) = player.PurchaseItem(vendor->GetInventory()->at(menu.GetSelectedItem()));
											if (itemSold)
											{

												vendor->RemoveItemFromInventory(menu.GetSelectedItem());
												menu.SetSelectedItem(0);
												menu.SetAllItems();
											}
										}
										userInterface.DrawStatusBar(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), message);
										SDL_RenderPresent(game.GetRenderer());

										break;
									case ScrollDownKeypressHandled:
										menu.ScrollDown();
										break;
									case ScrollUpKeypressHandled:
										menu.ScrollUp();
										break;
									}
								}
							}
						}
					}
					break;
				case InventoryKeypressHandled:
					bool inventoryBrowsingFlag = true;
					Menu menu(player.GetItemsInInventory());

					std::string lastMessage;
					while (inventoryBrowsingFlag)
					{
						userInterface.RefreshUserInterface();
						userInterface.DrawMap(game.GetRenderer(), &map, game.GetTileMap());
						userInterface.DrawPlayer(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
						userInterface.DrawPlayerInfo(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
						userInterface.DrawInventoryPopup(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
						userInterface.DrawStatusBar(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), lastMessage);
						SDL_RenderPresent(game.GetRenderer());
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
									userInterface.RefreshUserInterface();
									userInterface.DrawMap(game.GetRenderer(), &map, game.GetTileMap());
									userInterface.DrawPlayer(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
									userInterface.DrawPlayerInfo(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player);
									if (!player.GetInventory()->at(menu.GetSelectedItem()).GetIsEquipped())
									{

										lastMessage = player.EquipItem(&(player.GetInventory()->at(menu.GetSelectedItem())));
										userInterface.DrawStatusBar(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), lastMessage);
									}
									else
									{
										lastMessage = player.UnequipItem(player.GetInventory()->at(menu.GetSelectedItem()).GetItemClass());
										userInterface.DrawStatusBar(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), lastMessage);
									}
									userInterface.DrawInventoryPopup(game.GetRenderer(), game.GetTileMap()->GetTileMapTexture(), &player, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
									SDL_RenderPresent(game.GetRenderer());
									break;
								case ScrollDownKeypressHandled:
									menu.ScrollDown();
									break;
								case ScrollUpKeypressHandled:
									menu.ScrollUp();
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