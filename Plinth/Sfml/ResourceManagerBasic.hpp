//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2016 M.J.Silk
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

#ifndef PLINTH_SFML_RESOURCEMANAGERBASIC_HPP
#define PLINTH_SFML_RESOURCEMANAGERBASIC_HPP

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

	unsigned int addFont(const std::string& id, const std::string& filename); // returns index
	unsigned int addFont(const std::string& id); // returns index
	std::string addFont(); // returns generated ID (string of its index)
	void loadFont(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadFont(unsigned int index, const std::string& filename); // throws exception if file loading fails
	std::string loadNewFont(const std::string& filename); // returns generated ID (string of its index)

	unsigned int addImage(const std::string& id, const std::string& filename);
	unsigned int addImage(const std::string& id); // returns index
	std::string addImage(); // returns generated ID (string of its index)
	void loadImage(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadImage(unsigned int index, const std::string& filename); // throws exception if file loading fails
	std::string loadNewImage(const std::string& filename); // returns generated ID (string of its index)

	unsigned int addTexture(const std::string& id, const std::string& filename);
	unsigned int addTexture(const std::string& id); // returns index
	std::string addTexture(); // returns generated ID (string of its index)
	void loadTexture(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadTexture(unsigned int index, const std::string& filename); // throws exception if file loading fails
	void loadTextureFromImage(const std::string& textureId, const std::string& imageId); // loads from image resources. throws exception if it fails
	void loadTextureFromImage(const std::string& textureId, unsigned int imageIndex); // loads from image resources. throws exception if it fails
	void loadTextureFromImage(unsigned int textureIndex, const std::string& imageId); // loads from image resources. throws exception if it fails
	void loadTextureFromImage(unsigned int textureIndex, unsigned int imageIndex); // loads from image resources. throws exception if it fails
	std::string loadNewTexture(const std::string& filename); // returns generated ID (string of its index)

	unsigned int addSoundBuffer(const std::string& id, const std::string& filename);
	unsigned int addSoundBuffer(const std::string& id); // returns index
	std::string addSoundBuffer(); // returns generated ID (string of its index)
	void loadSoundBuffer(const std::string& id, const std::string& filename); // throws exception if file loading fails
	void loadSoundBuffer(unsigned int index, const std::string& filename); // throws exception if file loading fails
	std::string loadNewSoundBuffer(const std::string& filename); // returns generated ID (string of its index)

	sf::Font& getFont(const std::string& fontId);
	sf::Font& getFont(unsigned int fontIndex);
	sf::Image& getImage(const std::string& imageId);
	sf::Image& getImage(unsigned int imageIndex);
	sf::Texture& getTexture(const std::string& textureId);
	sf::Texture& getTexture(unsigned int textureIndex);
	sf::SoundBuffer& getSoundBuffer(const std::string& soundBufferId);
	sf::SoundBuffer& getSoundBuffer(unsigned int soundBufferIndex);

	void removeFont(const std::string& fontId);
	void removeFont(unsigned int fontIndex);
	void removeImage(const std::string& imageId);
	void removeImage(unsigned int imageIndex);
	void removeTexture(const std::string& textureId);
	void removeTexture(unsigned int textureIndex);
	void removeSoundBuffer(const std::string& soundBufferId);
	void removeSoundBuffer(unsigned int soundBufferIndex);
	void removeAllFonts();
	void removeAllImages();
	void removeAllTextures();
	void removeAllSoundBuffers();

private:
	IndexedMap<std::string, sf::Font> m_fonts;
	IndexedMap<std::string, sf::Image> m_images;
	IndexedMap<std::string, sf::Texture> m_textures;
	IndexedMap<std::string, sf::SoundBuffer> m_soundBuffers;
};

} // namespace plinth
#endif // PLINTH_SFML_RESOURCEMANAGERBASIC_HPP
