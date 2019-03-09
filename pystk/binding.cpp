#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <memory>
#include <vector>
#include "pystk.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace pybind11 {
class ro_view : public py::object {
public:
	template<typename T>
    explicit ro_view(const T * v, const std::vector<Py_ssize_t> & shape) {
		// Compute the stride
		static std::vector<Py_ssize_t> stride;
		stride.resize( shape.size() );
		Py_ssize_t itemsize = sizeof(T), s = 1;
		for(int i=stride.size()-1; i>=0; i--) {
			stride[i] = s * itemsize;
			s *= shape[i];
		}
		static std::string fmt;
		fmt = py::format_descriptor<T>::format();
		
		static Py_buffer buf { };
		buf.buf = const_cast<T *>(v);
		buf.itemsize = itemsize;
		buf.format = const_cast<char *>(fmt.c_str());
		buf.ndim = (int) shape.size();
		buf.len = s;
		buf.strides = stride.data();
		buf.shape = const_cast<Py_ssize_t *>(shape.data());
		buf.suboffsets = nullptr;
		buf.readonly = true;
		buf.internal = nullptr;

		m_ptr = PyMemoryView_FromBuffer(&buf);
		if (!m_ptr)
			py::pybind11_fail("Unable to create memoryview from buffer descriptor");
    }

    PYBIND11_OBJECT_CVT(ro_view, object, PyMemoryView_Check, PyMemoryView_FromObject)
};
}

template<typename T>
py::memoryview view(const T * v, const std::vector<ssize_t> & shape) {
	std::vector<ssize_t> stride = shape;
	ssize_t s = sizeof(T);
	for(int i=stride.size()-1; i>=0; i--) {
		stride[i] = s;
		s *= shape[i];
	}
	py::buffer_info bi(const_cast<T * >(v), shape, stride);
	return py::memoryview(bi);
}

PYBIND11_MODULE(pystk, m) {
	m.doc() = "Python SuperTuxKart interface";
	
	// Make offscreen rendering default
	setenv("IRR_DEVICE_TYPE", "offscreen", 0);
		
	
	{
		py::class_<PySTKConfig, std::shared_ptr<PySTKConfig>> cls(m, "Config", "SuperTuxKart configuration.");
	
		py::enum_<PySTKConfig::RaceMode>(cls, "RaceMode")
			.value("NORMAL_RACE", PySTKConfig::RaceMode::NORMAL_RACE)
			.value("TIME_TRIAL", PySTKConfig::RaceMode::TIME_TRIAL)
			.value("FOLLOW_LEADER", PySTKConfig::RaceMode::FOLLOW_LEADER)
			.value("THREE_STRIKES", PySTKConfig::RaceMode::THREE_STRIKES)
			.value("FREE_FOR_ALL", PySTKConfig::RaceMode::FREE_FOR_ALL)
			.value("CAPTURE_THE_FLAG", PySTKConfig::RaceMode::CAPTURE_THE_FLAG)
			.value("SOCCER", PySTKConfig::RaceMode::SOCCER);
	
		cls.def_readwrite("screen_width", &PySTKConfig::screen_width);
		cls.def_readwrite("screen_height", &PySTKConfig::screen_height);
		cls.def_readwrite("glow ", &PySTKConfig::glow );
		cls.def_readwrite("dof ", &PySTKConfig::dof );
		cls.def_readwrite("particles_effects ", &PySTKConfig::particles_effects );
		cls.def_readwrite("animated_characters ", &PySTKConfig::animated_characters );
		cls.def_readwrite("motionblur ", &PySTKConfig::motionblur );
		cls.def_readwrite("mlaa ", &PySTKConfig::mlaa );
		cls.def_readwrite("texture_compression ", &PySTKConfig::texture_compression );
		cls.def_readwrite("ssao ", &PySTKConfig::ssao );
		cls.def_readwrite("degraded_IBL ", &PySTKConfig::degraded_IBL );
		cls.def_readwrite("high_definition_textures ", &PySTKConfig::high_definition_textures );
		
		cls.def_readwrite("difficulty ", &PySTKConfig::difficulty );
		cls.def_readwrite("mode ", &PySTKConfig::mode );
		cls.def_readwrite("kart", &PySTKConfig::kart);
		cls.def_readwrite("track", &PySTKConfig::track);
		cls.def_readwrite("laps ", &PySTKConfig::laps );
		cls.def_readwrite("seed ", &PySTKConfig::seed );
		
		cls.def_static("hd", &PySTKConfig::hd,"High-definitaiton graphics settings");
		cls.def_static("sd", &PySTKConfig::sd,"Standard-definition graphics settings");
		cls.def_static("ld", &PySTKConfig::ld,"Low-definition graphics settings");
	}

	{
		py::class_<PySTKRenderData, std::shared_ptr<PySTKRenderData> > cls(m, "RenderData", "SuperTuxKart rendering output");
		
		cls.def_property_readonly("image", [](const PySTKRenderData & rd) { return py::ro_view(rd.color_buf_.data(), {rd.height, rd.width, 3}); }, "Color image of the kart");
		cls.def_property_readonly("depth", [](const PySTKRenderData & rd) { return py::ro_view(rd.depth_buf_.data(), {rd.height, rd.width}); }, "Depth image of the kart");
		
	}
	
	m.def("nRunning", &PySuperTuxKart::nRunning,"Number of SuperTuxKarts running (0 or 1)");
	{
		py::class_<PySuperTuxKart, std::shared_ptr<PySuperTuxKart> > cls(m, "SuperTuxKart", "SuperTuxKart instance");
		cls.def(py::init<const PySTKConfig &>(),py::arg("config"));
		cls.def("start", &PySuperTuxKart::start,"");
		cls.def("step", (bool (PySuperTuxKart::*)(float)) &PySuperTuxKart::step,"step with arguments float",py::arg("dt"));
		cls.def("stop", &PySuperTuxKart::stop,"");
		cls.def_property_readonly("render_data", &PySuperTuxKart::render_data, "rendering data from the last step");
	}
	
	// Initialize SuperTuxKart
	PySuperTuxKart::init();
	
	// This segfaults, no cleanup
// 	auto atexit = py::module::import("atexit");
// 		atexit.attr("register")(py::cpp_function([]() {
// 			PySuperTuxKart::clean();
// 	}));
}

