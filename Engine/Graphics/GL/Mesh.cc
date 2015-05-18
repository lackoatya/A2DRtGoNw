#include "Engine/Graphics/GL/Mesh.h"

#include <string>
#include <fstream>

#include "GLM/glm.hpp"

namespace Engine {
namespace Graphics {
namespace GL {
bool Mesh::Load(const char * _path) {
  std::ifstream file(_path);

  if (!file.fail()) {
    // Vertices
    uint32 vertex_count = 0;
    file >> vertex_count;

    // TODO pragma pack?
    struct Vertex final {
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 texture_position;

      void set(std::ifstream & _stream) {
        _stream >> position.x >> position.y >> position.z;
        _stream >> normal.x >> normal.y >> normal.z;
        _stream >> texture_position.x >> texture_position.y;
      }
    } * vertices = new Vertex[vertex_count];

    for (uint32 current = 0; current < vertex_count; ++current) {
      vertices[current].set(file);
    }

    // Triangles
    file >> m_triangles_count;

    // TODO pragma pack?
    struct Triangle final {
      GLuint indicies[3];

      void set(std::ifstream & _stream) {
        _stream >> indicies[0] >> indicies[1] >> indicies[2];
      }
    } *triangles = new Triangle[m_triangles_count];

    for (uint32 current = 0; current < m_triangles_count; ++current) {
      triangles[current].set(file);
    }

    file.close();

    // Create buffers/arrays
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_triangles_count * 3 * sizeof(GLuint), triangles, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture_position));

    glBindVertexArray(0);

    delete vertices;
    delete triangles;

    return true;
  } else {
    return false;
  }
}

bool Mesh::Release(void) {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
  glDeleteBuffers(1, &m_IBO);

  return true;
}

void Mesh::Render(void) {
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, m_triangles_count * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
}
}
}