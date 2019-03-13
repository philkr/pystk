#pragma once

#include <memory>
#include <vector>

struct PySTKConfig {
	enum RaceMode {
		NORMAL_RACE,
		TIME_TRIAL,
		FOLLOW_LEADER,
		THREE_STRIKES,
		FREE_FOR_ALL,
		CAPTURE_THE_FLAG,
		SOCCER,
	};
	
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
	
	int difficulty = 2;
	RaceMode mode = NORMAL_RACE;
	std::string kart;
	std::string track;
	int laps = 3;
	int seed = 0;
	
	static const PySTKConfig & hd();
	static const PySTKConfig & sd();
	static const PySTKConfig & ld();
};

class PySTKRenderTarget;

struct PySTKRenderData {
	int width, height;
	std::vector<uint8_t> color_buf_;
	std::vector<float> depth_buf_;
	std::vector<int32_t> instance_buf_;
};

struct PySTKAction {
	float steering_angle = 0;
	float acceleration = 0;
	bool nitro = false;
	bool drift = false;
	bool rescue = false;
	bool fire = false;
};

class PySuperTuxKart {
protected: // Static methods
	static int n_running;
	static void initRest();
	static void initUserConfig();
	static void cleanSuperTuxKart();
	static void cleanUserConfig();

public: // Static methods
	static void init();
	static void clean();
	static int nRunning();

protected:
	void setupConfig(const PySTKConfig & config);
	void load();
	void setupRaceStart();
	void render(float dt);
	std::vector<std::unique_ptr<PySTKRenderTarget> > render_targets_;
	std::vector<std::shared_ptr<PySTKRenderData> > render_data_;

public:
	PySuperTuxKart(const PySTKConfig & config);
	~PySuperTuxKart();
	void start();
	bool step(float dt);
	void stop();
	const std::vector<std::shared_ptr<PySTKRenderData> > & render_data() const { return render_data_; }
};
