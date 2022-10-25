//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2022 M.J.Silk
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

#ifndef PLINTH_SFML_RESOURCEMANAGERBASIC_INL
#define PLINTH_SFML_RESOURCEMANAGERBASIC_INL

#include "ResourceManagerBasic.hpp"

namespace
{

const std::string resourceManagerExceptionPrefix = "Resource Manager Basic: ";

} // namespace

namespace plinth
{

inline ResourceManagerBasic::ResourceManagerBasic()
{
}

inline unsigned int ResourceManagerBasic::addFont(const std::string& id, const std::string& filename)
{
	unsigned int index{ addFont(id) };
	loadFont(id, filename);
	return index;
}

inline unsigned int ResourceManagerBasic::addFont(const std::string& id)
{
	m_fonts.add(id, sf::Font());
	fontIds.push_back(id);
	return m_fonts.getSize() - 1;
}

inline std::string ResourceManagerBasic::addFont()
{
	std::string id{ std::to_string(m_fonts.getSize()) };
	addFont(id);
	return id;
}

inline void ResourceManagerBasic::loadFont(const std::string& id, const std::string& filename)
{
	if (!m_fonts.valid(id))
		throw Exception(resourceManagerExceptionPrefix + "Invalid font ID.");
	else if (!m_fonts.access(id).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load font.");
}

inline void ResourceManagerBasic::loadFont(const unsigned int index, const std::string& filename)
{
	if (!m_fonts.valid(index))
		throw Exception(resourceManagerExceptionPrefix + "Invalid font index.");
	else if (!m_fonts.access(index).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load font.");
}

inline std::string ResourceManagerBasic::loadNewFont(const std::string& filename)
{
	std::string id{ std::to_string(m_fonts.getSize()) };
	addFont(id, filename);
	return id;
}

inline unsigned int ResourceManagerBasic::addImage(const std::string& id, const std::string& filename)
{
	unsigned int index{ addImage(id) };
	loadImage(id, filename);
	return index;
}

inline unsigned int ResourceManagerBasic::addImage(const std::string& id)
{
	m_images.add(id, sf::Image());
	imageIds.push_back(id);
	return m_images.getSize() - 1;
}

inline std::string ResourceManagerBasic::addImage()
{
	std::string id{ std::to_string(m_images.getSize()) };
	addImage(id);
	return id;
}

inline void ResourceManagerBasic::loadImage(const std::string& id, const std::string& filename)
{
	if (!m_images.valid(id))
		throw Exception(resourceManagerExceptionPrefix + "Invalid image ID.");
	else if (!m_images.access(id).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load image.");
}

inline void ResourceManagerBasic::loadImage(const unsigned int index, const std::string& filename)
{
	if (!m_images.valid(index))
		throw Exception(resourceManagerExceptionPrefix + "Invalid image index.");
	else if (!m_images.access(index).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load image.");
}

inline std::string ResourceManagerBasic::loadNewImage(const std::string& filename)
{
	std::string id{ std::to_string(m_images.getSize()) };
	addImage(id, filename);
	return id;
}

inline unsigned int ResourceManagerBasic::addTexture(const std::string& id, const std::string& filename)
{
	unsigned int index{ addTexture(id) };
	loadTexture(id, filename);
	return index;
}

inline unsigned int ResourceManagerBasic::addTexture(const std::string& id)
{
	m_textures.add(id, sf::Texture());
	textureIds.push_back(id);
	return m_textures.getSize() - 1;
}

inline std::string ResourceManagerBasic::addTexture()
{
	std::string id{ std::to_string(m_textures.getSize()) };
	addTexture(id);
	return id;
}

inline void ResourceManagerBasic::loadTexture(const std::string& id, const std::string& filename)
{
	if (!m_textures.valid(id))
		throw Exception(resourceManagerExceptionPrefix + "Invalid texture ID.");
	else if (!m_textures.access(id).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load texture.");
}

inline void ResourceManagerBasic::loadTexture(unsigned int index, const std::string& filename)
{
	if (!m_textures.valid(index))
		throw Exception(resourceManagerExceptionPrefix + "Invalid texture index.");
	else if (!m_textures.access(index).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load texture.");
}

inline void ResourceManagerBasic::loadTextureFromImage(const std::string& textureId, const std::string& imageId)
{
	if (!m_images.valid(imageId))
		throw Exception(resourceManagerExceptionPrefix + "Invalid image ID.");
	else if (!m_textures.valid(textureId))
		throw Exception(resourceManagerExceptionPrefix + "Invalid texture ID.");
	else if (!m_textures.access(textureId).loadFromImage(m_images.access(imageId)))
		throw Exception(resourceManagerExceptionPrefix + "Failed to load texture from image.");
}

inline void ResourceManagerBasic::loadTextureFromImage(const std::string& textureId, unsigned int imageIndex)
{
	if (!m_images.valid(imageIndex))
		throw Exception(resourceManagerExceptionPrefix + "Invalid image idnex.");
	else if (!m_textures.valid(textureId))
		throw Exception(resourceManagerExceptionPrefix + "Invalid texture ID.");
	else if (!m_textures.access(textureId).loadFromImage(m_images.access(imageIndex)))
		throw Exception(resourceManagerExceptionPrefix + "Failed to load texture from image.");
}

inline void ResourceManagerBasic::loadTextureFromImage(const unsigned int textureIndex, const std::string& imageId)
{
	if (!m_images.valid(imageId))
		throw Exception(resourceManagerExceptionPrefix + "Invalid image ID.");
	else if (!m_textures.valid(textureIndex))
		throw Exception(resourceManagerExceptionPrefix + "Invalid texture index.");
	else if (!m_textures.access(textureIndex).loadFromImage(m_images.access(imageId)))
		throw Exception(resourceManagerExceptionPrefix + "Failed to load texture from image.");
}

inline void ResourceManagerBasic::loadTextureFromImage(const unsigned int textureIndex, const unsigned int imageIndex)
{
	if (!m_images.valid(imageIndex))
		throw Exception(resourceManagerExceptionPrefix + "Invalid image index.");
	else if (!m_textures.valid(textureIndex))
		throw Exception(resourceManagerExceptionPrefix + "Invalid texture index.");
	else if (!m_textures.access(textureIndex).loadFromImage(m_images.access(imageIndex)))
		throw Exception(resourceManagerExceptionPrefix + "Failed to load texture from image.");
}

inline std::string ResourceManagerBasic::loadNewTexture(const std::string& filename)
{
	std::string id{ std::to_string(m_textures.getSize()) };
	addTexture(id, filename);
	return id;
}

inline unsigned int ResourceManagerBasic::addSoundBuffer(const std::string& id, const std::string& filename)
{
	unsigned int index{ addSoundBuffer(id) };
	loadSoundBuffer(id, filename);
	return index;
}

inline unsigned int ResourceManagerBasic::addSoundBuffer(const std::string& id)
{
	m_soundBuffers.add(id, sf::SoundBuffer());
	soundBufferIds.push_back(id);
	return m_soundBuffers.getSize() - 1;
}

inline std::string ResourceManagerBasic::addSoundBuffer()
{
	std::string id{ std::to_string(m_soundBuffers.getSize()) };
	addSoundBuffer(id);
	return id;
}

inline void ResourceManagerBasic::loadSoundBuffer(const std::string& id, const std::string& filename)
{
	if (!m_soundBuffers.valid(id))
		throw Exception(resourceManagerExceptionPrefix + "Invalid sound buffer ID.");
	else if (!m_soundBuffers.access(id).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load sound buffer.");
}

inline void ResourceManagerBasic::loadSoundBuffer(const unsigned int index, const std::string& filename)
{
	if (!m_soundBuffers.valid(index))
		throw Exception(resourceManagerExceptionPrefix + "Invalid sound buffer index.");
	else if (!m_soundBuffers.access(index).loadFromFile(filename))
		throw Exception(resourceManagerExceptionPrefix + "Cannot load sound buffer.");
}

inline std::string ResourceManagerBasic::loadNewSoundBuffer(const std::string& filename)
{
	std::string id{ std::to_string(m_soundBuffers.getSize()) };
	addSoundBuffer(id, filename);
	return id;
}

inline sf::Font& ResourceManagerBasic::getFont(const std::string& fontId)
{
	if (m_fonts.valid(fontId))
		return m_fonts.access(fontId);
	else
		throw Exception(resourceManagerExceptionPrefix + "Font not available.");
}

inline sf::Font& ResourceManagerBasic::getFont(const unsigned int fontIndex)
{
	if (m_fonts.valid(fontIndex))
		return m_fonts.access(fontIndex);
	else
		throw Exception(resourceManagerExceptionPrefix + "Font not available.");
}

inline sf::Image& ResourceManagerBasic::getImage(const std::string& imageId)
{
	if (m_images.valid(imageId))
		return m_images.access(imageId);
	else
		throw Exception(resourceManagerExceptionPrefix + "Image not available.");
}

inline sf::Image& ResourceManagerBasic::getImage(const unsigned int imageIndex)
{
	if (m_images.valid(imageIndex))
		return m_images.access(imageIndex);
	else
		throw Exception(resourceManagerExceptionPrefix + "Image not available.");
}

inline sf::Texture& ResourceManagerBasic::getTexture(const std::string& textureId)
{
	if (m_textures.valid(textureId))
		return m_textures.access(textureId);
	else
		throw Exception(resourceManagerExceptionPrefix + "Texture not available.");
}

inline sf::Texture& ResourceManagerBasic::getTexture(const unsigned int textureIndex)
{
	if (m_textures.valid(textureIndex))
		return m_textures.access(textureIndex);
	else
		throw Exception(resourceManagerExceptionPrefix + "Texture not available.");
}

inline sf::SoundBuffer& ResourceManagerBasic::getSoundBuffer(const std::string& soundBufferId)
{
	if (m_soundBuffers.valid(soundBufferId))
		return m_soundBuffers.access(soundBufferId);
	else
		throw Exception(resourceManagerExceptionPrefix + "SoundBuffer not available.");
}

inline sf::SoundBuffer& ResourceManagerBasic::getSoundBuffer(const unsigned int soundBufferIndex)
{
	if (m_soundBuffers.valid(soundBufferIndex))
		return m_soundBuffers.access(soundBufferIndex);
	else
		throw Exception(resourceManagerExceptionPrefix + "SoundBuffer not available.");
}

inline void ResourceManagerBasic::removeFont(const std::string& fontId)
{
	m_fonts.remove(fontId);
}

inline void ResourceManagerBasic::removeFont(const unsigned int fontIndex)
{
	m_fonts.remove(fontIndex);
}

inline void ResourceManagerBasic::removeImage(const std::string& imageId)
{
	m_images.remove(imageId);
}

inline void ResourceManagerBasic::removeImage(const unsigned int imageIndex)
{
	m_images.remove(imageIndex);
}

inline void ResourceManagerBasic::removeTexture(const std::string& textureId)
{
	m_textures.remove(textureId);
}

inline void ResourceManagerBasic::removeTexture(const unsigned int textureIndex)
{
	m_textures.remove(textureIndex);
}

inline void ResourceManagerBasic::removeSoundBuffer(const std::string& soundBufferId)
{
	m_soundBuffers.remove(soundBufferId);
}

inline void ResourceManagerBasic::removeSoundBuffer(const unsigned int soundBufferIndex)
{
	m_soundBuffers.remove(soundBufferIndex);
}

inline void ResourceManagerBasic::removeAllFonts()
{
	m_fonts.clear();
}

inline void ResourceManagerBasic::removeAllImages()
{
	m_images.clear();
}

inline void ResourceManagerBasic::removeAllTextures()
{
	m_textures.clear();
}

inline void ResourceManagerBasic::removeAllSoundBuffers()
{
	m_soundBuffers.clear();
}

} // namespace plinth

#endif // PLINTH_SFML_RESOURCEMANAGERBASIC_INL
