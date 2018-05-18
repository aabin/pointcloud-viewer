#ifndef RENDERSYSTEM_GL450_DEBUG_DEBUGMESH_H
#define RENDERSYSTEM_GL450_DEBUG_DEBUGMESH_H

#include <renderer/gl450/declarations.hpp>

#include <glhelper/buffer.hpp>
#include <glhelper/vertexarrayobject.hpp>

#include <QStack>

namespace renderer {
namespace gl450 {


class DebugMesh final
{
public:
  struct vertex_t;
  class Painter;

  DebugMesh(const vertex_t* vertices, int num_vertices);
  ~DebugMesh();
  DebugMesh(DebugMesh&&debugMesh);


  DebugMesh& operator=(DebugMesh&&) = delete;
  DebugMesh(const DebugMesh&) = delete;
  DebugMesh& operator=(const DebugMesh&) = delete;

  static gl::VertexArrayObject generateVertexArrayObject();

  void bind(const gl::VertexArrayObject& vertexArrayObject);
  void draw();

private:
  gl::Buffer vertex_buffer;
  int num_vertices;
};


struct DebugMesh::vertex_t final
{
  glm::vec3 position;
  float parameter1;
  glm::vec3 color;
  float parameter2;
};


class DebugMesh::Painter final
{
public:
  enum strip_t
  {
    CLOSE,
    OPEN,
  };

  struct current_attribute_t
  {
    glm::vec3 color = glm::vec3(1, 0.5, 0);
    float parameter1 = 0.f;
    float parameter2 = 0.f;
  };

  Painter();

  current_attribute_t next_attribute;

  QVector<vertex_t> vertices;

  void begin_strip(strip_t close);
  void end_strip();

  void add_vertex(const glm::vec3& position);
  void add_vertex(const glm::vec2& position, float z=0);
  void add_vertex(float x, float y, float z=0);

  void add_circle(float radius, int nPoints);
  void add_sphere(float radius, int nPoints);
  void add_cylinder(float radius, float length, int nPoints);
  void add_rect(const glm::vec2& min, const glm::vec2& max);
  void add_cube(const glm::vec3& min, const glm::vec3& max);
  void add_arrow(float length, float tipLength);

  void push_matrix(const glm::vec3& position, bool multiply = true);
  void push_matrix(const glm::vec3& position, const glm::vec3& normal, bool multiply = true);
  void push_matrix(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& firstPointDirection, bool multiply = true);
  void push_matrix(const glm::mat4& matrix=glm::mat4(1), bool multiply = true);
  void pop_matrix();

  DebugMesh to_mesh() const;

private:
  QStack<glm::mat4> transformations;
  int strip_index = -1;
  int first_strip_vertex;
};


} // namespace gl450
} // namespace renderer

#endif // RENDERSYSTEM_GL450_DEBUG_DEBUGMESH_H

