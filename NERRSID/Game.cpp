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

std::tuple<bool, Player> Game::IntroSequence(UI* userInterface, SDL_Texture* tilemapTexture)
{
	SDL_Event eventSDL;
	bool menuIsActive = true, characterCreationFlag = true;
	int positionOfCursor = 0;
	Menu menu(2);
	Player player;
	std::string playerName = "";
	SDL_StartTextInput();
	while (menuIsActive)
	{
		userInterface->RefreshUserInterface();
		userInterface->DrawStartupMenu(tilemapTexture, menu.GetSelectedItem());
		SDL_RenderPresent(userInterface->GetRenderer());

		while (SDL_PollEvent(&eventSDL))
		{
			if (eventSDL.type == SDL_QUIT)
				return { false, player };
			else if (eventSDL.type == SDL_KEYDOWN)
			{
				switch (eventSDL.key.keysym.sym)
				{
				case SDLK_UP:
					menu.ScrollUp();
					break;
				case SDLK_DOWN:
					menu.ScrollDown();
					break;
				case SDLK_RETURN:
					switch (menu.GetSelectedItem())
					{
					case 0:
						while (characterCreationFlag)
						{
							while (SDL_PollEvent(&eventSDL))
							{
								userInterface->RefreshUserInterface();
								userInterface->DrawText(tilemapTexture, 0, 0, "Enter name:");
								userInterface->DrawPlayerCreationName(tilemapTexture, playerName);
								SDL_RenderPresent(userInterface->GetRenderer());

								if (eventSDL.type == SDL_QUIT)
									return { false, player };
								else if (eventSDL.type == SDL_TEXTINPUT)
									playerName += eventSDL.text.text;
								else if (eventSDL.type == SDL_KEYDOWN)
								{
									switch (eventSDL.key.keysym.sym)
									{
									case SDLK_RETURN:
									{
										if (playerName.empty())
											break;
										Menu menuClassSelection(3);
										while (true)
										{
											userInterface->RefreshUserInterface();
											userInterface->DrawPlayerClassSelection(tilemapTexture, menuClassSelection.GetSelectedItem());
											SDL_RenderPresent(userInterface->GetRenderer());
											while (SDL_PollEvent(&eventSDL))
											{
												if (eventSDL.type == SDL_QUIT)
													return { false, player };
												else if (eventSDL.type == SDL_KEYDOWN)
												{
													switch (eventSDL.key.keysym.sym)
													{
													case SDLK_UP:
														menuClassSelection.ScrollUp();
														break;
													case SDLK_DOWN:
														menuClassSelection.ScrollDown();
														break;
													case SDLK_RETURN:
														switch (menuClassSelection.GetSelectedItem())
														{
														case 0:
														{
															Player playerReturning(playerName, Warrior, 1, 1);
															return{ true, playerReturning };
															break;
														}
														case 1:
														{
															Player playerReturning(playerName, Wizard, 1, 1);
															return{ true, playerReturning };
															break;
														}
														case 2:
														{
															Player playerReturning(playerName, Assassin, 1, 1);
															return{ true, playerReturning };
															break;
														}
														}
														break;
													}
												}
											}
										}
										break;
									}
									case SDLK_BACKSPACE:
										if (!playerName.empty())
											playerName.pop_back();
										break;
									default:
										break;
									}
								}
							}
						}
						break;
					case 1:
						return { false, player };
						break;
					}
					break;
				case SDLK_ESCAPE:
					return { false, player };
					break;
				}
			}
		}
	}
	SDL_StopTextInput();
}

void Game::Build(int gameScreenWidth, int gameScreenHeight)
{
	srand(time(nullptr));
	Map map;
	if (!map.GenerateMap())
		exit(EXIT_FAILURE);
	Game game(gameScreenWidth, gameScreenHeight);
	UI userInterface(game.GetRenderer(), game.GetScreenWidth(), game.GetScreenHeight());
	bool gameIsRunning = false;
	Player player;
	std::tie(gameIsRunning, player) = Game::IntroSequence(&userInterface, game.GetTileMap()->GetTileMapTexture());
	GameEvent eventGame;
	std::array<Vendor, 5> mapVendors = map.GetMapVendors();

	while (gameIsRunning)
	{
		SDL_Event eventSDL;

		eventGame = GameEventHandler::CollisionHandler(player, map);

		userInterface.RefreshUserInterface();
		userInterface.DrawMap(&map, game.GetTileMap());
		userInterface.DrawPlayer(game.GetTileMap()->GetTileMapTexture(), &player);
		userInterface.DrawPlayerInfo(game.GetTileMap()->GetTileMapTexture(), &player);
		userInterface.DrawStatusBar(game.GetTileMap()->GetTileMapTexture(), eventGame.GetEventMessage());
		SDL_RenderPresent(game.GetRenderer());

		while (SDL_PollEvent(&eventSDL))
		{
			if (eventSDL.type == SDL_QUIT)
				gameIsRunning = false;
			else if (eventSDL.type == SDL_KEYDOWN)
			{
				switch (GameEventHandler::KeypressHandler(&player, &eventSDL, map.GetMapTiles()))
				{
				case ExitKeypressHandled:
					gameIsRunning = false;
					break;
				case EnterKeypressHandled:
					if (eventGame.GetTypeOfEvent() == VendorEvent)
					{
						Vendor* vendor = nullptr;
						vendor = Map::FindVendor(&mapVendors, map.GetNumberOfVendors(), player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
						bool vendorShoppingFlag = true;
						Menu menu(vendor->GetItemsInInventory());
						std::string message = "";
						bool itemSold = false;

						while (vendorShoppingFlag)
						{
							userInterface.RefreshUserInterface();
							userInterface.DrawMap(&map, game.GetTileMap());
							userInterface.DrawPlayer(game.GetTileMap()->GetTileMapTexture(), &player);
							userInterface.DrawPlayerInfo(game.GetTileMap()->GetTileMapTexture(), &player);
							userInterface.DrawVendorPopup(game.GetTileMap()->GetTileMapTexture(), vendor, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
							userInterface.DrawStatusBar(game.GetTileMap()->GetTileMapTexture(), message);
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
									switch (GameEventHandler::VendorKeypressHandler(&eventSDL))
									{
									case ExitKeypressHandled:
										vendorShoppingFlag = false;
										break;
									case EnterKeypressHandled:
										userInterface.RefreshUserInterface();
										userInterface.DrawMap(&map, game.GetTileMap());
										userInterface.DrawPlayer(game.GetTileMap()->GetTileMapTexture(), &player);
										userInterface.DrawPlayerInfo(game.GetTileMap()->GetTileMapTexture(), &player);
										userInterface.DrawVendorPopup(game.GetTileMap()->GetTileMapTexture(), vendor, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
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
										userInterface.DrawStatusBar(game.GetTileMap()->GetTileMapTexture(), message);
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
						userInterface.DrawMap(&map, game.GetTileMap());
						userInterface.DrawPlayer(game.GetTileMap()->GetTileMapTexture(), &player);
						userInterface.DrawPlayerInfo(game.GetTileMap()->GetTileMapTexture(), &player);
						userInterface.DrawInventoryPopup(game.GetTileMap()->GetTileMapTexture(), &player, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
						userInterface.DrawStatusBar(game.GetTileMap()->GetTileMapTexture(), lastMessage);
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
								switch (GameEventHandler::InventoryKeypressHandler(eventSDL))
								{
								case ExitKeypressHandled:
									inventoryBrowsingFlag = false;
									break;
								case EnterKeypressHandled:
									userInterface.RefreshUserInterface();
									userInterface.DrawMap(&map, game.GetTileMap());
									userInterface.DrawPlayer(game.GetTileMap()->GetTileMapTexture(), &player);
									userInterface.DrawPlayerInfo(game.GetTileMap()->GetTileMapTexture(), &player);
									if (!player.GetInventory()->at(menu.GetSelectedItem()).GetIsEquipped())
									{
										lastMessage = player.EquipItem(&(player.GetInventory()->at(menu.GetSelectedItem())));
										userInterface.DrawStatusBar(game.GetTileMap()->GetTileMapTexture(), lastMessage);
									}
									else
									{
										lastMessage = player.UnequipItem(player.GetInventory()->at(menu.GetSelectedItem()).GetItemClass());
										userInterface.DrawStatusBar(game.GetTileMap()->GetTileMapTexture(), lastMessage);
									}
									userInterface.DrawInventoryPopup(game.GetTileMap()->GetTileMapTexture(), &player, menu.GetSelectedItem(), menu.GetStartingItem(), menu.GetEndingItem());
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