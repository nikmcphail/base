#pragma once

#include "library/utils.h"

#include "valve/player_info.h"
#include "valve/vector3.h"
#include "valve/input_system.h"

class net_channel_info_t;
class key_values_t;
class model_t;

struct client_textmessage_t {
  int         effect;
  byte        r1, g1, b1, a1; // 2 colors for effects
  byte        r2, g2, b2, a2;
  float       x;
  float       y;
  float       fadein;
  float       fadeout;
  float       holdtime;
  float       fxtime;
  const char* pVGuiSchemeFontName; // If null, use default font for messages
  const char* pName;
  const char* pMessage;
  bool        bRoundedRectBackdropBox;
  float       flBoxSize; // as a function of font height
  byte        boxcolor[4];
  char const* pClearMessage; // message to clear
};

class engine_client_013_t {
public:
  virtual int get_intersecting_surfaces(const model_t* model, const vector3_t& v_center,
                                        const float radius, const bool b_only_visible_surfaces,
                                        void* p_infos, const int n_max_infos) = 0;

  virtual vector3_t get_light_for_point(const vector3_t& pos, bool b_clamp) = 0;

  virtual material_t* trace_line_material_and_lighting(const vector3_t& start,
                                                       const vector3_t& end,
                                                       vector3_t&       diffuse_light_color,
                                                       vector3_t&       base_color) = 0;

  virtual const char* parse_file(const char* data, char* token, int maxlen)        = 0;
  virtual bool        copy_local_file(const char* source, const char* destination) = 0;

  virtual void get_screen_size(int& width, int& height) = 0;

  virtual void server_cmd(const char* sz_cmd_string, bool b_reliable = true) = 0;
  virtual void client_cmd(const char* sz_cmd_string)                         = 0;

  virtual bool get_player_info(int ent_num, player_info_t* pinfo) = 0;

  virtual int get_player_for_user_id(int user_id) = 0;

  virtual client_textmessage_t* text_message_get(const char* p_name) = 0;

  virtual bool con_is_visible(void) = 0;

  virtual int get_local_player_index(void) = 0;

  virtual const model_t* load_model(const char* p_name, bool b_prop = false) = 0;

  virtual float time(void) = 0;

  virtual float get_last_time_stamp(void) = 0;

  virtual void* get_sentence(void* p_audio_source)        = 0;
  virtual float get_sentence_length(void* p_audio_source) = 0;
  virtual bool  is_streaming(void* p_audio_source) const  = 0;

  virtual void get_view_angles(qangle_t& va) = 0;
  virtual void set_view_angles(qangle_t& va) = 0;

  virtual int get_max_clients(void) = 0;

  virtual const char* key_lookup_binding(const char* p_binding) = 0;

  virtual const char* key_binding_for_key(button_code_e code) = 0;

  virtual void start_key_trap_mode(void)                    = 0;
  virtual bool check_done_key_trapping(button_code_e& code) = 0;

  virtual bool is_in_game(void)               = 0;
  virtual bool is_connected(void)             = 0;
  virtual bool is_drawing_loading_image(void) = 0;

  virtual void con_nprintf(int pos, const char* fmt, ...)                          = 0;
  virtual void con_nxprintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;

  virtual int is_box_visible(const vector3_t& mins, const vector3_t& maxs) = 0;

  virtual int is_box_in_view_cluster(const vector3_t& mins, const vector3_t& maxs) = 0;

  virtual bool cull_box(const vector3_t& mins, const vector3_t& maxs) = 0;

  virtual void sound_extra_update(void) = 0;

  virtual const char* get_game_directory(void) = 0;

  virtual const view_matrix_t& world_to_screen_matrix() = 0;

  virtual const view_matrix_t& world_to_view_matrix() = 0;

  virtual int  game_lump_version(int lump_id) const                  = 0;
  virtual int  game_lump_size(int lump_id) const                     = 0;
  virtual bool load_game_lump(int lump_id, void* p_buffer, int size) = 0;

  virtual int level_leaf_count() const = 0;

  virtual void* get_bsp_tree_query() = 0;

  virtual void linear_to_gamma(float* linear, float* gamma) = 0;

  virtual float light_style_value(int style) = 0;

  virtual void compute_dynamic_lighting(const vector3_t& pt, const vector3_t* p_normal,
                                        vector3_t& color) = 0;

  virtual void get_ambient_light_color(vector3_t& color) = 0;

  virtual int get_dx_support_level() = 0;

  virtual bool supports_hdr() = 0;

  virtual void mat_stub(material_system_t* p_mat_sys) = 0;

  virtual void        get_chapter_name(char* pch_buff, int i_max_length) = 0;
  virtual char const* get_level_name(void)                               = 0;
  virtual int         get_level_version(void)                            = 0;

#if !defined(NO_VOICE)
  virtual struct IVoiceTweak_s* get_voice_tweak_api(void) = 0;
#endif

  virtual void engine_stats_begin_frame(void) = 0;
  virtual void engine_stats_end_frame(void)   = 0;

  virtual void fire_events() = 0;

  virtual int get_leaves_area(int* p_leaves, int n_leaves) = 0;

  virtual bool does_box_touch_area_frustum(const vector3_t& mins, const vector3_t& maxs,
                                           int i_area) = 0;

  virtual void set_audio_state(const void* state) = 0;

  virtual int sentence_group_pick(int group_index, char* name, int name_buf_len) = 0;
  virtual int sentence_group_pick_sequential(int group_index, char* name, int name_buf_len,
                                             int sentence_index, int reset)      = 0;
  virtual int sentence_index_from_name(const char* p_sentence_name)              = 0;
  virtual const char* sentence_name_from_index(int sentence_index)               = 0;
  virtual int         sentence_group_index_from_name(const char* p_group_name)   = 0;
  virtual const char* sentence_group_name_from_index(int group_index)            = 0;
  virtual float       sentence_length(int sentence_index)                        = 0;

  virtual void compute_lighting(const vector3_t& pt, const vector3_t* p_normal, bool b_clamp,
                                vector3_t& color, vector3_t* p_box_colors = NULL) = 0;

  virtual void activate_occluder(int n_occluder_index, bool b_active)                    = 0;
  virtual bool is_occluded(const vector3_t& vec_abs_mins, const vector3_t& vec_abs_maxs) = 0;

  virtual void* save_alloc_memory(size_t num, size_t size) = 0;
  virtual void  save_free_memory(void* p_save_mem)         = 0;

  virtual net_channel_info_t* get_net_channel_info(void) = 0;

  virtual void  debug_draw_phys_collide(const void* p_collide, material_t* p_material,
                                        matrix_3x4_t& transform, const void* color) = 0;
  virtual void  checkpoint(const char* p_name)                                      = 0;
  virtual void  draw_portals()                                                      = 0;
  virtual bool  is_playing_demo(void)                                               = 0;
  virtual bool  is_recording_demo(void)                                             = 0;
  virtual bool  is_playing_time_demo(void)                                          = 0;
  virtual int   get_demo_recording_tick(void)                                       = 0;
  virtual int   get_demo_playback_tick(void)                                        = 0;
  virtual int   get_demo_playback_start_tick(void)                                  = 0;
  virtual float get_demo_playback_time_scale(void)                                  = 0;
  virtual int   get_demo_playback_total_ticks(void)                                 = 0;
  virtual bool  is_paused(void)                                                     = 0;
  virtual bool  is_taking_screenshot(void)                                          = 0;
  virtual bool  is_hltv(void)                                                       = 0;
  virtual bool  is_level_main_menu_background(void)                                 = 0;
  virtual void  get_main_menu_background_name(char* dest, int destlen)              = 0;

  virtual void get_video_modes(int& n_count, void*& p_modes) = 0;

  virtual void set_occlusion_parameters(const void*& params) = 0;

  virtual void get_ui_language(char* dest, int destlen) = 0;

  virtual void is_skybox_visible_from_point(const vector3_t& vec_point) = 0;

  virtual const char* get_map_entities_string() = 0;

  virtual bool is_in_edit_mode(void) = 0;

  virtual float get_screen_aspect_ratio() = 0;

  virtual bool removed_steam_refresh_login(const char* password, bool is_secure) = 0;
  virtual bool removed_steam_process_call(bool& finished)                        = 0;

  virtual unsigned int get_engine_build_number()    = 0;
  virtual const char*  get_product_version_string() = 0;

  virtual void grab_pre_color_corrected_frame(int x, int y, int width, int height) = 0;

  virtual bool is_hammer_running() const = 0;

  virtual void execute_client_cmd(const char* sz_cmd_string) = 0;

  virtual bool map_has_hdr_lighting(void) = 0;

  virtual int get_app_id() = 0;

  virtual vector3_t get_light_for_point_fast(const vector3_t& pos, bool b_clamp) = 0;

  virtual void client_cmd_unrestricted(const char* sz_cmd_string) = 0;

  virtual void set_restrict_server_commands(bool b_restrict) = 0;

  virtual void set_restrict_client_commands(bool b_restrict) = 0;

  virtual void set_overlay_bind_proxy(int i_overlay_id, void* p_bind_proxy) = 0;

  virtual bool copy_frame_buffer_to_material(const char* p_material_name) = 0;

  virtual void change_team(const char* p_team_name) = 0;

  virtual void read_configuration(const bool read_default = false) = 0;

  virtual void  set_achievement_mgr(void* p_achievement_mgr) = 0;
  virtual void* get_achievement_mgr()                        = 0;

  virtual bool map_load_failed(void)             = 0;
  virtual void set_map_load_failed(bool b_state) = 0;

  virtual bool        is_low_violence()                                    = 0;
  virtual const char* get_most_recent_save_game(void)                      = 0;
  virtual void        set_most_recent_save_game(const char* lpsz_filename) = 0;

  virtual void start_xbox_exiting_process()     = 0;
  virtual bool is_save_in_progress()            = 0;
  virtual int  on_storage_device_attached(void) = 0;
  virtual void on_storage_device_detached(void) = 0;

  virtual void reset_demo_interpolation(void) = 0;

  virtual void  set_gamestats_data(void* p_gamestats_data) = 0;
  virtual void* get_gamestats_data()                       = 0;

#if defined(USE_SDL)
  virtual void get_mouse_delta(int& x, int& y, bool b_ignore_next_mouse_delta = false) = 0;
#endif

  virtual void server_cmd_key_values(key_values_t* p_key_values) = 0;

  virtual bool is_skipping_playback(void) = 0;
  virtual bool is_loading_demo(void)      = 0;

  virtual bool is_playing_demo_a_locally_recorded_demo() = 0;

  virtual const char* key_lookup_binding_exact(const char* p_binding) = 0;

  virtual void  add_phoneme_file(const char* psz_phoneme_file) = 0;
  virtual float get_paused_expire_time(void)                   = 0;

  virtual bool start_demo_recording(const char* psz_filename,
                                    const char* psz_folder = NULL)                      = 0;
  virtual void stop_demo_recording(void)                                                = 0;
  virtual void take_screenshot(const char* psz_filename, const char* psz_folder = NULL) = 0;
};

class engine_client_t : public engine_client_013_t {
public:
  virtual int  get_protocol_version()                              = 0;
  virtual bool is_windowed_mode()                                  = 0;
  virtual void flash_window()                                      = 0;
  virtual int  get_client_version() const                          = 0;
  virtual bool is_active_app()                                     = 0;
  virtual void disconnect_internal()                               = 0;
  virtual int  get_instances_running_count()                       = 0;
  virtual void set_rich_presence_connect(const char* psz_override) = 0;
};
