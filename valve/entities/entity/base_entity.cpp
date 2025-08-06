#include "base_entity.h"

#include "valve/entity_list.h"
#include "client_renderable.h"
#include "valve/bone.h"
#include "valve/global_vars_base.h"

#include "valve/cusercmd.h"

base_entity_t* base_entity_t::get_base_entity(int index) {
  auto client_entity = client::g_interfaces.entity_list->get_client_entity(index);
  return (client_entity ? client_entity->get_base_entity() : nullptr);
}

void base_entity_t::set_prediction_random_seed(usercmd_t* cmd) {
  static auto func = (__int64(__fastcall*)(
      usercmd_t*))client::g_addresses.client.functions.set_prediction_random_seed;

  func(cmd);
}

bool base_entity_t::is_alive() {
  return utils::get_virtual_function<bool(__fastcall*)(void*)>(this, 131)(this);
}

bool base_entity_t::is_player() {
  return utils::get_virtual_function<bool(__fastcall*)(void*)>(this, 132)(this);
}

bool base_entity_t::setup_bones(matrix_3x4_t* bone_to_world_out, int max_bones, int bone_mask,
                                float current_time) {
  return get_client_renderable()->setup_bones(bone_to_world_out, max_bones, bone_mask,
                                              current_time);
}

base_entity_t* base_entity_t::get_observer_target() {
  return utils::get_virtual_function<base_entity_t*(__fastcall*)(void*)>(this, 243)(this);
}

vector3_t base_entity_t::get_hitbox_pos(int id) {
  matrix_3x4_t hitboxes[128];
  if (setup_bones(hitboxes, 128, BONE_USED_BY_HITBOX,
                  client::g_interfaces.global_vars->cur_time))
    return vector3_t(hitboxes[id][0][3], hitboxes[id][1][3], hitboxes[id][2][3]);
  else
    return vector3_t{};
}

int base_entity_t::get_observer_mode() {
  return utils::get_virtual_function<int(__fastcall*)(void*)>(this, 242)(this);
}

vector3_t base_entity_t::get_eye_position() {
  vector3_t position;
  utils::get_virtual_function<void(__fastcall*)(void*, vector3_t*)>(this, 142)(this, &position);
  return position;
}
