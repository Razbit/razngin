
#include "game.h"

#include "utils/logger.h"
#include "renderer.h"
#include "object3d.h"
#include "entityloader.h"
#include "settingsloader.h"
#include "scene.h"
#include "renderer.h"
#include "settings.h"

Settings* Game::settings;
Logger* Game::log;
SettingsLoader* Game::settingsldr;
EntityLoader* Game::entldr;
Scene* Game::scene;
Renderer* Game::renderer;
