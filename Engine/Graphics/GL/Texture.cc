#include "Engine/Graphics/Gl/Texture.h"

#include "SOIL/SOIL.h"

namespace Engine {
namespace Graphics {
namespace GL {
bool Texture::Load(const char * _path) {
  GLuint id = 0;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char * image = SOIL_load_image(_path, &m_width, &m_height, 0, SOIL_LOAD_RGBA);

  if (image != nullptr) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    // TODO This is not correct this way. We can change m_loaded to true, before setting m_id to id.
    // If m_id is accessed during this time, the returned m_id will be 0 (or the last value), not the new loaded id.
    bool expected = false;
    if (m_loaded.compare_exchange_strong(expected, true)) {
      m_id = id;
      return true;
    } else {
      return false;
    }
  } else {
    // TODO Rework this!
    char message[600] = "SOIL FILE LOADING ERROR\n\0";
    strcat_s(message, _path);
    assert(false && message);
    return false;
  }
}
}
}
}
