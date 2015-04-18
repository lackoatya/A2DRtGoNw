#include "P3A/Graphics/Model.h"

#include "P3A/Graphics/GraphicsContext.h"

namespace P3A{
namespace Graphics{
  void Model::Render(GraphicsContext * _context, Vector2 const& _location) {
  for (uint32 current = 0; current < mesh_->elements_count; ++current)
    _context->DrawBox(appearance_->element_textures()[mesh_->depth_indexes[current]],
                     _location + element_centers_[mesh_->depth_indexes[current]],
                     interpolation_->bases_[mesh_->depth_indexes[current]]->current.rotation);
}
}
}