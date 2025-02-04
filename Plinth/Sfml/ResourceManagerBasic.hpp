//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2025 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Common.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../IndexedMap.hpp"

namespace plinth
{

class ResourceManagerBasic
{
public:

	std::vector<std::string> fontIds;
	std::vector<std::string> imageIds;
	std::vector<std::string> textureIds;
	std::vector<std::string> soundBufferIds;

	ResourceManagerBasic();

	std::size_t addFont(const std::string& id, const std::string& filename); // returns index
	std::size_t addFont(const std::string& id); // returns index
	std::string addFont(); // returns generated ID (string of its index)
	void openFont(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void openFont(std::size_t index, const std::string& filename); // throws exception if file loading fails
	std::string openNewFont(const std::string& filename); // returns generated ID (string of its index)

	std::size_t addImage(const std::string& id, const std::string& filename);
	std::size_t addImage(const std::string& id); // returns index
	std::string addImage(); // returns generated ID (string of its index)
	void loadImage(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadImage(std::size_t index, const std::string& filename); // throws exception if file loading fails
	std::string loadNewImage(const std::string& filename); // returns generated ID (string of its index)

	std::size_t addTexture(const std::string& id, const std::string& filename);
	std::size_t addTexture(const std::string& id); // returns index
	std::string addTexture(); // returns generated ID (string of its index)
	void loadTexture(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadTexture(std::size_t index, const std::string& filename); // throws exception if file loading fails
	void loadTextureFromImage(const std::string& textureId, const std::string& imageId); // loads from image resources. throws exception if it fails
	void loadTextureFromImage(const std::string& textureId, std::size_t imageIndex); // loads from image resources. throws exception if it fails
	void loadTextureFromImage(std::size_t textureIndex, const std::string& imageId); // loads from image resources. throws exception if it fails
	void loadTextureFromImage(std::size_t textureIndex, std::size_t imageIndex); // loads from image resources. throws exception if it fails
	std::string loadNewTexture(const std::string& filename); // returns generated ID (string of its index)

	std::size_t addSoundBuffer(const std::string& id, const std::string& filename);
	std::size_t addSoundBuffer(const std::string& id); // returns index
	std::string addSoundBuffer(); // returns generated ID (string of its index)
	void loadSoundBuffer(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadSoundBuffer(std::size_t index, const std::string& filename); // throws exception if file loading fails
	std::string loadNewSoundBuffer(const std::string& filename); // returns generated ID (string of its index)

	sf::Font& getFont(const std::string& fontId);
	sf::Font& getFont(std::size_t fontIndex);
	sf::Image& getImage(const std::string& imageId);
	sf::Image& getImage(std::size_t imageIndex);
	sf::Texture& getTexture(const std::string& textureId);
	sf::Texture& getTexture(std::size_t textureIndex);
	sf::SoundBuffer& getSoundBuffer(const std::string& soundBufferId);
	sf::SoundBuffer& getSoundBuffer(std::size_t soundBufferIndex);

	void removeFont(const std::string& fontId);
	void removeFont(std::size_t fontIndex);
	void removeImage(const std::string& imageId);
	void removeImage(std::size_t imageIndex);
	void removeTexture(const std::string& textureId);
	void removeTexture(std::size_t textureIndex);
	void removeSoundBuffer(const std::string& soundBufferId);
	void removeSoundBuffer(std::size_t soundBufferIndex);
	void removeAllFonts();
	void removeAllImages();
	void removeAllTextures();
	void removeAllSoundBuffers();

private:
	const std::string m_resourceManagerExceptionPrefix;

	IndexedMap<std::string, sf::Font> m_fonts;
	IndexedMap<std::string, sf::Image> m_images;
	IndexedMap<std::string, sf::Texture> m_textures;
	IndexedMap<std::string, sf::SoundBuffer> m_soundBuffers;
};

} // namespace plinth
#include "ResourceManagerBasic.inl"
