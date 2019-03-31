#pragma once

#include <memory>
#include <vector>

struct PySTKGraphicsConfig {
	int screen_width=600, screen_height=400;
	bool glow = false, bloom = true, light_shaft = true, dynamic_lights = true, dof = true;
	int particles_effects = 2;
	bool animated_characters = true;
	bool motionblur = true;
	bool mlaa = true;
	bool texture_compression = true;
	bool ssao = true;
	bool degraded_IBL = true;
	int high_definition_textures = 2 | 1;
	bool render_window = false; // Render the main game window
	
	static const PySTKGraphicsConfig & hd();
	static const PySTKGraphicsConfig & sd();
	static const PySTKGraphicsConfig & ld();
};
struct PySTKRaceConfig {
	enum RaceMode {
		NORMAL_RACE,
		TIME_TRIAL,
		FOLLOW_LEADER,
		THREE_STRIKES,
		FREE_FOR_ALL,
		CAPTURE_THE_FLAG,
		SOCCER,
	};
	
	int difficulty = 2;
	RaceMode mode = NORMAL_RACE;
	std::string kart;
	std::string track;
	int laps = 3;
	int seed = 0;
	float step_size = 0.1;
	bool player_ai = true;
};

class PySTKRenderTarget;

struct PySTKRenderData {
	int width, height;
	std::vector<uint8_t> color_buf_;
	std::vector<float> depth_buf_;
	std::vector<uint32_t> instance_buf_;
};

class KartControl;
class Controller;
struct PySTKAction {
	float steering_angle = 0;
	float acceleration = 0;
	bool brake = false;
	bool nitro = false;
	bool drift = false;
	bool rescue = false;
	bool fire = false;
	void set(KartControl * control) const;
	void get(const KartControl * control);
};

class PySuperTuxKart {
protected: // Static methods
	static int n_running;
	static bool render_window;
	static void initRest();
	static void initUserConfig();
	static void initGraphicsConfig(const PySTKGraphicsConfig & config);
	static void cleanSuperTuxKart();
	static void cleanUserConfig();

public: // Static methods
	static void init(const PySTKGraphicsConfig & config);
	static void load();
	static void clean();
	static int nRunning();
	static std::vector<std::string> listTracks();
	static std::vector<std::string> listKarts();

protected:
	void setupConfig(const PySTKRaceConfig & config);
	void setupRaceStart();
	void render(float dt);
	std::vector<std::unique_ptr<PySTKRenderTarget> > render_targets_;
	std::vector<std::shared_ptr<PySTKRenderData> > render_data_;
	PySTKRaceConfig config_;
	float time_leftover_ = 0;
	Controller * ai_controller_ = nullptr;
	PySTKAction ai_action_;

public:
	PySuperTuxKart(const PySuperTuxKart &) = delete;
	PySuperTuxKart& operator=(const PySuperTuxKart &) = delete;
	PySuperTuxKart(const PySTKRaceConfig & config);
	~PySuperTuxKart();
	void start();
	bool step(const PySTKAction &);
	bool step();
	void stop();
	const PySTKAction & ai_action() const { return ai_action_; }
	const std::vector<std::shared_ptr<PySTKRenderData> > & render_data() const { return render_data_; }
};
