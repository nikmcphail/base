#include "atlas.h"

#include "valve/key_values.h"
#include "valve/material_system.h"
#include "client/client.h"

material_t* create_material(const std::string& name, const std::string& shader,
                            std::string body = "") {
  key_values_t* kv     = new key_values_t(name.c_str());
  std::string   buffer = "\"" + shader + "\"\n{\n" + body + "\n}";
  kv->load_from_buffer(name.c_str(), buffer.c_str());

  material_t* mat = client::g_interfaces.material_system->create_material(name.c_str(), kv);
  if (!mat) {
    std::string err = "\t" + name + " failed to create";
    client::g_console.print(err.c_str(), console_color_red);
    return nullptr;
  }

  std::string msg = "\t" + name + " created";
  client::g_console.print(msg.c_str(), console_color_light_aqua);

  return mat;
}

bool atlas_t::initialize() {
  test_material =
      create_material("test_material", "VertexLitGeneric", "\t\"$basetexture\" \"vgui/white\"");
  if (!test_material)
    return false;

  client::g_console.print("\tatlas initialized", console_color_gray);
  return true;
}