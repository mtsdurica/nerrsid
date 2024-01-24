#include <cstdlib>
#include <iostream>
#include <tuple>
#include <ctime>

#include "Game.h"
#include "GameEvent.h"
#include "Vendor.h"
#include "Enemy.h"
#include "Corpse.h"
#include "GameEventHandler.h"
#include "Menu.h"

Game::Game(const int screenWidth, const int screenHeight) : ScreenWidth(screenWidth), ScreenHeight(screenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::quick_exit(EXIT_FAILURE);

	GameWindow = SDL_CreateWindow("NERRSID",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN);
	if (!GameWindow)
		std::quick_exit(EXIT_FAILURE);

	GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);

	this->TileMap = new Tilemap(GameRenderer);
}

Game::~Game()
{
	delete TileMap;
	SDL_DestroyRenderer(this->GameRenderer);
	SDL_DestroyWindow(this->GameWindow);
	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() const
{
	return GameRenderer;
}

Tilemap* Game::GetTilemap() const
{
	return this->TileMap;
}

int Game::GetScreenWidth() const
{
	return this->ScreenWidth;
}

int Game::GetScreenHeight() const
{
	return this->ScreenHeight;
}

std::tuple<bool, Player> Game::IntroSequence(UserInterface* userInterface, SDL_Texture* tilemapTexture)
{
	SDL_Event eventSDL;
	bool menuIsActive = true;
	int positionOfCursor = 0;
	Menu menu(2);
	Player player;
	std::string playerName;
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
			if (eventSDL.type == SDL_KEYDOWN)
			{
				bool characterCreationFlag = true;
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
								userInterface->DrawPlayerCreationName(tilemapTexture, playerName);
								SDL_RenderPresent(userInterface->GetRenderer());

								if (eventSDL.type == SDL_QUIT)
									return { false, player };
								if (eventSDL.type == SDL_TEXTINPUT)
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
												if (eventSDL.type == SDL_KEYDOWN)
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
														}
														case 1:
														{
															Player playerReturning(playerName, Wizard, 1, 1);
															return{ true, playerReturning };
														}
														case 2:
														{
															Player playerReturning(playerName, Assassin, 1, 1);
															return{ true, playerReturning };
														}
														default:
															break;
														}
														break;
													default:
														break;
													}
												}
											}
										}
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
					default:
						break;
					}
					break;
				case SDLK_ESCAPE:
					return { false, player };
				default:
					break;
				}
			}
		}
	}
	SDL_StopTextInput();
}

void Game::Build(int gameScreenWidth, int gameScreenHeight)
{
	// Game initialization
	Player player;
	Game game(gameScreenWidth, gameScreenHeight);
	UserInterface userInterface(game.GetRenderer(), game.GetScreenWidth(), game.GetScreenHeight());
	bool gameIsRunning = false, helpDisplayedFlag = false, debugMode = false; // TODO: REMOVE DEBUGMODE BEFORE SHIPPING
	std::tie(gameIsRunning, player) = IntroSequence(&userInterface, game.GetTilemap()->GetTileMapTexture());
	Map map;
	if (!map.GenerateMap())
		std::quick_exit(EXIT_FAILURE);

	// Main game loop
	while (gameIsRunning)
	{
		SDL_Event eventSDL;
		GameEvent eventPopup;
		std::string lastMessage;
		bool popupFlag = false;
		GameEvent eventGame = GameEventHandler::CollisionHandler(player, map);
		player.SetIdleStatus(true);

		while (SDL_PollEvent(&eventSDL))
		{
			if (eventSDL.type == SDL_QUIT)
				gameIsRunning = false;
			else if (eventSDL.type == SDL_KEYDOWN)
			{
				switch (GameEventHandler::KeypressHandler(&player, eventGame, &eventSDL, map.GetMapTiles()))
				{
				case ExitKeypressHandled:
					gameIsRunning = false;
					break;
				case EnterKeypressHandled:
					switch (eventGame.GetTypeOfEvent())
					{
					case VendorEvent:
						eventPopup.SetTypeOfEvent(VendorEvent);
						player.SetIdleStatus(false);
						break;
					case ChestEvent:
						eventPopup.SetTypeOfEvent(ChestEvent);
						player.SetIdleStatus(false);
						break;
					case CorpseEvent:
						eventPopup.SetTypeOfEvent(CorpseEvent);
						player.SetIdleStatus(false);
						break;
					case EnemyEvent:
					{
						Enemy* enemy = nullptr;
						enemy = map.FindEnemy(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
						Corpse corpse(enemy->GetPositionXCoordinate(), enemy->GetPositionYCoordinate(), enemy->GetStandingOnTile());
						map.RemoveEnemy(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
						corpse.CreateInventory();
						map.InsertCorpse(&corpse);
						map.AddCorpse(&corpse);
						break;
					}
					case StairsEvent:
						player.SetPositionXCoordinate(1);
						player.SetPositionYCoordinate(1);
						Map nextMap;
						map = nextMap;
						if (!map.GenerateMap())
							std::quick_exit(EXIT_FAILURE);
						break;
					}
					break;
				case InventoryKeypressHandled:
					eventPopup.SetTypeOfEvent(InventoryEvent);
					player.SetIdleStatus(false);
					break;
				case NextTurnKeypressHandled:
					//if (player.GetPlayerMovesLeft() == 0)
					//{
					map.MoveEnemies(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
					player.SetPlayerTurn(player.GetPlayerTurn() + 1);
					player.SetPlayerMovesLeft(1);
					//}
					//else
					//{
					//	// TODO: Add popup for confirmation of skipping move
					//}
					break;
				case HelpKeypressHandled:
					helpDisplayedFlag = !helpDisplayedFlag;
					break;
				case DebugKeypressHandled:
					debugMode = !debugMode;
					break;
				case UnusedKeypressHandled:
				case PlayerNavigationKeypressHandled:
				case ScrollDownKeypressHandled:
				case ScrollUpKeypressHandled:
					break;
				}
			}
		}

		lastMessage = eventGame.GetEventMessage();

		switch (eventPopup.GetTypeOfEvent())
		{
		case VendorEvent:
		{
			Vendor* vendor = nullptr;
			vendor = map.FindVendor(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
			Menu menu(vendor->GetItemsInInventory());
			std::string message;
			bool itemSold = false;
			popupFlag = true;
			while (popupFlag)
			{
				while (SDL_PollEvent(&eventSDL))
				{
					if (eventSDL.type == SDL_QUIT)
					{
						popupFlag = false;
						gameIsRunning = false;
					}
					else if (eventSDL.type == SDL_KEYDOWN)
					{
						switch (GameEventHandler::EntityInventoryKeypressHandler(&eventSDL))
						{
						case ExitKeypressHandled:
							popupFlag = false;
							break;
						case EnterKeypressHandled:
							if (vendor->GetItemsInInventory())
							{
								std::tie(lastMessage, itemSold) = player.PurchaseItem(vendor->GetInventory()->at(menu.GetSelectedItem()));
								if (itemSold)
								{
									vendor->RemoveItemFromInventory(menu.GetSelectedItem());
									menu.SetSelectedItem(0);
									menu.SetAllItems();
								}
							}
							break;
						case ScrollDownKeypressHandled:
							menu.ScrollDown();
							break;
						case ScrollUpKeypressHandled:
							menu.ScrollUp();
							break;
						case HelpKeypressHandled:
							helpDisplayedFlag = !helpDisplayedFlag;
							break;
						case UnusedKeypressHandled:
						case PlayerNavigationKeypressHandled:
						case InventoryKeypressHandled:
							break;
						}
					}
				}
				userInterface.UpdateUserInterface(game.GetTilemap()->GetTileMapTexture(), &map, &player, vendor, &menu, lastMessage, helpDisplayedFlag);
			}
			break;
		}
		case ChestEvent:
		{
			Chest* chest = nullptr;
			chest = map.FindChest(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
			Menu menu(chest->GetItemsInInventory());
			std::string message;
			popupFlag = true;
			while (popupFlag)
			{
				while (SDL_PollEvent(&eventSDL))
				{
					if (eventSDL.type == SDL_QUIT)
					{
						popupFlag = false;
						gameIsRunning = false;
					}
					else if (eventSDL.type == SDL_KEYDOWN)
					{
						switch (GameEventHandler::EntityInventoryKeypressHandler(&eventSDL))
						{
						case ExitKeypressHandled:
							popupFlag = false;
							if (chest->GetItemsInInventory() == 0)
								map.RemoveChest(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
							break;
						case EnterKeypressHandled:
							if (chest->GetItemsInInventory())
							{
								lastMessage = player.LootItem(chest->GetInventory()->at(menu.GetSelectedItem()));
								chest->RemoveItemFromInventory(menu.GetSelectedItem());
								menu.SetSelectedItem(0);
								menu.SetAllItems();
							}
							break;
						case ScrollDownKeypressHandled:
							menu.ScrollDown();
							break;
						case ScrollUpKeypressHandled:
							menu.ScrollUp();
							break;
						case HelpKeypressHandled:
							helpDisplayedFlag = !helpDisplayedFlag;
							break;
						case UnusedKeypressHandled:
						case PlayerNavigationKeypressHandled:
						case InventoryKeypressHandled:
							break;
						}
					}
				}
				userInterface.UpdateUserInterface(game.GetTilemap()->GetTileMapTexture(), &map, &player, chest, &menu, lastMessage, false, helpDisplayedFlag);
			}
			break;
		}
		case CorpseEvent:
		{
			Corpse* corpse = nullptr;
			corpse = map.FindCorpse(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
			Menu menu(corpse->GetItemsInInventory());
			std::string message;
			popupFlag = true;
			while (popupFlag)
			{
				while (SDL_PollEvent(&eventSDL))
				{
					if (eventSDL.type == SDL_QUIT)
					{
						popupFlag = false;
						gameIsRunning = false;
					}
					else if (eventSDL.type == SDL_KEYDOWN)
					{
						switch (GameEventHandler::EntityInventoryKeypressHandler(&eventSDL))
						{
						case ExitKeypressHandled:
							popupFlag = false;
							if (corpse->GetItemsInInventory() == 0)
								map.RemoveCorpse(player.GetPositionXCoordinate(), player.GetPositionYCoordinate());
							break;
						case EnterKeypressHandled:
							if (corpse->GetItemsInInventory())
							{
								lastMessage = player.LootItem(corpse->GetInventory()->at(menu.GetSelectedItem()));
								corpse->RemoveItemFromInventory(menu.GetSelectedItem());
								menu.SetSelectedItem(0);
								menu.SetAllItems();
							}
							break;
						case ScrollDownKeypressHandled:
							menu.ScrollDown();
							break;
						case ScrollUpKeypressHandled:
							menu.ScrollUp();
							break;
						case HelpKeypressHandled:
							helpDisplayedFlag = !helpDisplayedFlag;
							break;
						case UnusedKeypressHandled:
						case PlayerNavigationKeypressHandled:
						case InventoryKeypressHandled:
							break;
						}
					}
				}
				userInterface.UpdateUserInterface(game.GetTilemap()->GetTileMapTexture(), &map, &player, corpse, &menu, lastMessage, true, helpDisplayedFlag);
			}
			break;
		}
		case InventoryEvent:
		{
			Menu menu(player.GetItemsInInventory());
			popupFlag = true;
			while (popupFlag)
			{
				while (SDL_PollEvent(&eventSDL))
				{
					if (eventSDL.type == SDL_QUIT)
					{
						popupFlag = false;
						gameIsRunning = false;
					}
					else if (eventSDL.type == SDL_KEYDOWN)
					{
						switch (GameEventHandler::EntityInventoryKeypressHandler(&eventSDL))
						{
						case ExitKeypressHandled:
							popupFlag = false;
							break;
						case EnterKeypressHandled:
							if (!player.GetInventory()->at(menu.GetSelectedItem()).GetIsEquipped())
								lastMessage = player.EquipItem(&(player.GetInventory()->at(menu.GetSelectedItem())));
							else
								lastMessage = player.UnequipItem(player.GetInventory()->at(menu.GetSelectedItem()).GetItemClass());
							break;
						case ScrollDownKeypressHandled:
							menu.ScrollDown();
							break;
						case ScrollUpKeypressHandled:
							menu.ScrollUp();
							break;
						case HelpKeypressHandled:
							helpDisplayedFlag = !helpDisplayedFlag;
							break;
						case UnusedKeypressHandled:
						case PlayerNavigationKeypressHandled:
						case InventoryKeypressHandled:
							break;
						}
					}
				}
				userInterface.UpdateUserInterface(game.GetTilemap()->GetTileMapTexture(), &map, &player, &menu, lastMessage, helpDisplayedFlag);
			}
			break;
		}
		default: break;
		}
		userInterface.UpdateUserInterface(game.GetTilemap()->GetTileMapTexture(), &map, &player, lastMessage, helpDisplayedFlag, debugMode);
	}
}
