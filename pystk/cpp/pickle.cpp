#include "pickle.hpp"
#include "pystk.hpp"

void pickle(std::ostream & s, const std::string & o) {
    uint32_t n = o.size();
    s.write((const char*)&n, sizeof(n));
    s.write(o.data(), n);
}
void unpickle(std::istream & s, std::string * o) {
    uint32_t n;
    s.read((char*)&n, sizeof(n));
    o->resize(n);
    s.read(&(*o)[0], n);
}

void pickle(std::ostream & s, const PySTKGraphicsConfig & o) {
    pickle(s, o.screen_width);
    pickle(s, o.screen_height);
    pickle(s, o.glow);
    pickle(s, o.bloom);
    pickle(s, o.light_shaft);
    pickle(s, o.dynamic_lights);
    pickle(s, o.dof);
    pickle(s, o.particles_effects);
    pickle(s, o.animated_characters);
    pickle(s, o.motionblur);
    pickle(s, o.mlaa);
    pickle(s, o.texture_compression);
    pickle(s, o.ssao);
    pickle(s, o.degraded_IBL);
    pickle(s, o.high_definition_textures);
    pickle(s, o.render_window);
}
void unpickle(std::istream & s, PySTKGraphicsConfig * o) {
    unpickle(s, &o->screen_width);
    unpickle(s, &o->screen_height);
    unpickle(s, &o->glow);
    unpickle(s, &o->bloom);
    unpickle(s, &o->light_shaft);
    unpickle(s, &o->dynamic_lights);
    unpickle(s, &o->dof);
    unpickle(s, &o->particles_effects);
    unpickle(s, &o->animated_characters);
    unpickle(s, &o->motionblur);
    unpickle(s, &o->mlaa);
    unpickle(s, &o->texture_compression);
    unpickle(s, &o->ssao);
    unpickle(s, &o->degraded_IBL);
    unpickle(s, &o->high_definition_textures);
    unpickle(s, &o->render_window);
}
void pickle(std::ostream & s, const PySTKPlayerConfig & o) {
    pickle(s, o.kart);
    pickle(s, o.controller);
}
void unpickle(std::istream & s, PySTKPlayerConfig * o) {
    unpickle(s, &o->kart);
    unpickle(s, &o->controller);
}
void pickle(std::ostream & s, const PySTKRaceConfig & o) {
    pickle(s, o.difficulty);
    pickle(s, o.mode);
    pickle(s, o.players);
    pickle(s, o.track);
    pickle(s, o.laps);
    pickle(s, o.seed);
    pickle(s, o.num_kart);
    pickle(s, o.step_size);
}
void unpickle(std::istream & s, PySTKRaceConfig * o) {
    unpickle(s, &o->difficulty);
    unpickle(s, &o->mode);
    unpickle(s, &o->players);
    unpickle(s, &o->track);
    unpickle(s, &o->laps);
    unpickle(s, &o->seed);
    unpickle(s, &o->num_kart);
    unpickle(s, &o->step_size);
}
void pickle(std::ostream & s, const PySTKRenderData & o) {
    pickle(s, o.width);
    pickle(s, o.height);
    pickle(s, o.color_buf_);
    pickle(s, o.depth_buf_);
    pickle(s, o.instance_buf_);
}
void unpickle(std::istream & s, PySTKRenderData * o) {
    unpickle(s, &o->width);
    unpickle(s, &o->height);
    unpickle(s, &o->color_buf_);
    unpickle(s, &o->depth_buf_);
    unpickle(s, &o->instance_buf_);
}
void pickle(std::ostream & s, const PySTKAction & o) {
    pickle(s, o.steering_angle);
    pickle(s, o.acceleration);
    pickle(s, o.brake);
    pickle(s, o.nitro);
    pickle(s, o.drift);
    pickle(s, o.rescue);
    pickle(s, o.fire);
}
void unpickle(std::istream & s, PySTKAction * o) {
    unpickle(s, &o->steering_angle);
    unpickle(s, &o->acceleration);
    unpickle(s, &o->brake);
    unpickle(s, &o->nitro);
    unpickle(s, &o->drift);
    unpickle(s, &o->rescue);
    unpickle(s, &o->fire);
}
