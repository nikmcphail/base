#pragma once

class vector3_t;
class qangle_t;

class debug_overlay_t {
public:
  virtual void add_entity_text_overlay(int ent_index, int line_offset, float duration, int r,
                                       int g, int b, int a, const char* format, ...) = 0;
  virtual void add_box_overlay(const vector3_t& origin, const vector3_t& mins,
                               const vector3_t& max, qangle_t const& orientation, int r, int g,
                               int b, int a, float duration)                         = 0;
  virtual void add_triangle_overlay(const vector3_t& p1, const vector3_t& p2,
                                    const vector3_t& p3, int r, int g, int b, int a,
                                    bool no_depth_test, float duration)              = 0;
  virtual void add_line_overlay(const vector3_t& origin, const vector3_t& dest, int r, int g,
                                int b, bool no_depth_test, float duration)           = 0;
  virtual void add_text_overlay(const vector3_t& origin, float duration, const char* format,
                                ...)                                                 = 0;
  virtual void add_text_overlay(const vector3_t& origin, int line_offset, float duration,
                                const char* format, ...)                             = 0;
  virtual void add_screen_text_overlay(float fl_x_pos, float fl_y_pos, float fl_duration, int r,
                                       int g, int b, int a, const char* text)        = 0;
  virtual void add_swept_box_overlay(const vector3_t& start, const vector3_t& end,
                                     const vector3_t& mins, const vector3_t& max,
                                     const qangle_t& angles, int r, int g, int b, int a,
                                     float fl_duration)                              = 0;
  virtual void add_grid_overlay(const vector3_t& origin)                             = 0;
  virtual int  screen_position(const vector3_t& point, vector3_t& screen)            = 0;
  virtual int  screen_position(float fl_x_pos, float fl_y_pos, vector3_t& screen)    = 0;

  virtual void* get_first(void)           = 0;
  virtual void* get_next(void* current)   = 0;
  virtual void  clear_dead_overlays(void) = 0;
  virtual void  clear_all_overlays()      = 0;

  virtual void add_text_overlay_rgb(const vector3_t& origin, int line_offset, float duration,
                                    float r, float g, float b, float alpha, const char* format,
                                    ...)                                                 = 0;
  virtual void add_text_overlay_rgb(const vector3_t& origin, int line_offset, float duration,
                                    int r, int g, int b, int a, const char* format, ...) = 0;

  virtual void add_line_overlay_alpha(const vector3_t& origin, const vector3_t& dest, int r,
                                      int g, int b, int a, bool no_depth_test,
                                      float duration) = 0;
  virtual void add_box_overlay2(const vector3_t& origin, const vector3_t& mins,
                                const vector3_t& max, qangle_t const& orientation,
                                const void*& face_color, const void*& edge_color,
                                float duration)       = 0;

  virtual void add_screen_text_overlay2(float fl_x_pos, float fl_y_pos, int i_line,
                                        float fl_duration, int r, int g, int b, int a,
                                        const char* text) = 0;

  // misyl: compat.
  // must be a 2 otherwise msvc will dump overloads in the middle of the vtable
  inline void add_screen_text_overlay(float fl_x_pos, float fl_y_pos, int i_line,
                                      float fl_duration, int r, int g, int b, int a,
                                      const char* text) {
    this->add_screen_text_overlay2(fl_x_pos, fl_y_pos, i_line, fl_duration, r, g, b, a, text);
  }

private:
  inline void add_text_overlay(const vector3_t& origin, int line_offset, float duration, int r,
                               int g, int b, int a, const char* format, ...) {
  } /* catch improper use of bad interface. Needed because '0' duration can be resolved by
       compiler to NULL format string (i.e., compiles but calls wrong function) */
};