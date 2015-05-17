#include "Engine/Graphics/Gl/Texture.h"


#include "SOIL/SOIL.h"

namespace Engine {
namespace Graphics {
namespace GL {
Texture::Texture(const GLchar * _path) {
  glGenTextures(1, &m_id);
  glBindTexture(GL_TEXTURE_2D, m_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char * image = SOIL_load_image(_path, &m_width, &m_height, 0, SOIL_LOAD_RGBA);
  if (image == nullptr) {
    // TODO Rework this!
    char message[600] = "SOIL FILE LOADING ERROR\n\0";
    strcat_s(message, _path);
    assert(false && message);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);

  glBindTexture(GL_TEXTURE_2D, 0);
}
}
}
}
