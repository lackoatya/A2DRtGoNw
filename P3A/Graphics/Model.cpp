#include "P3A\Graphics\Model.h"
#include "P3A\Graphics\GraphicsContext.h"

void P3A::Graphics::Model::Render(void)
{
	Render_Element(mesh->elements[0], location);
}

void P3A::Graphics::Model::Render_Element(Engine::Graphics::Mesh::Element * _element, Vector2 const& _location)
{
	context.DrawBox(appearance->element_textures[_element->index], _location, interpolation_current->rotations[_element->index]);

	for (uint32 current = 0; current < _element->joints_count; ++current)
	{
		Vector2 center = _element->joints[current]->owner_location - _element->joints[current]->target_location;
		center.Rotate_Degree(interpolation_current->rotations[_element->index]);
		center += _location;
		Render_Element(mesh->elements[_element->joints[current]->target_index], center);
	}
}


/*void P3A::Graphics::Model::Render(GraphicsContext & _context)
+ {
	+Render_Element(_context, main_element, location, 0.f);
	+}
+
+void P3A::Graphics::Model::Render_Element(GraphicsContext & _context, Engine::Graphics::Element_Base * _element, Vector2 const& _location, real32 const& _rotation)
+ {
	+_context.DrawBox(_element->texture, _location, _rotation + _element->rotation);
	+
		+for (Engine::Graphics::Element_Base::Joint_Base * _joint : _element->joints)
		+ {
		+Vector2 ki_rot = _joint->owner_location;
		+ki_rot.Rotate_Degree(_rotation);
		+Vector2 be_rot = _joint->target_location;
		+be_rot.Rotate_Degree(_rotation);
		+
			+Vector2 center = _location + ki_rot - be_rot;
		+Render_Element(_context, _joint->target, center, _rotation + _element->rotation);
		+}
	+}*/