
//          Copyright Alessandro De Santis 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#pragma once

#include "plumbase.h"

// INTERFACE IDs
#define IFID_PLUM_HOST 				"plum.host"
#define IFID_PLUM_PLUGIN 			"plum.plugin"
#define IFID_PLUM_STORAGE 			"plum.storage"

// PLUGIN CATEGORIES
#define PLUM_SYNTH 					0
#define PLUM_EFFECT					1

struct plum_version
{
	uint32_t major, minor;
};

// PARAMETER TYPES
#define PLUM_FLOAT					0
#define PLUM_INTEGER				1

struct plum_param_def
{
	int type;
	float min;
	float max;
	const char *name;
	void (*format)(plum_param_def *, char *str, uint32_t size, float value);
};

namespace plum {


class iplugin : public iobject
{
public:
	virtual const char *get_name() = 0;

	virtual iwindow *open_ui(ihostwindow *) = 0;

	virtual uint32_t count_inputs() = 0;
	virtual istring *get_input_name(uint32_t index) = 0;
	virtual uint32_t count_outputs() = 0;
	virtual istring *get_output_name(uint32_t index) = 0;


	virtual void configure(uint32_t samplerate, uint32_t buffersize) = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void midi_event(uint8_t *data) = 0;
	virtual void process(uint32_t nframes, float **ins, float **outs) = 0;
	

	virtual uint32_t count_presets() = 0;
	virtual uint32_t get_selected_preset() = 0;
	virtual void set_selected_preset(uint32_t index) = 0;

	virtual istring *get_preset_name(uint32_t index) = 0;
	virtual void set_preset_name(uint32_t index, istring *) = 0;

	virtual uint32_t count_parameters() = 0;
	virtual float get_parameter(uint32_t index) = 0;
	virtual void set_parameter(uint32_t index, float value) = 0;
	virtual void get_parameter_def(uint32_t index, plum_param_def *def) = 0;
};


class istorage : public iobject
{
public:
	virtual uint32_t set_preset_data(iblob *) = 0;
	virtual iblob *get_preset_data() = 0;
	virtual uint32_t set_bank_data(iblob *) = 0;
	virtual iblob *get_bank_data() = 0;
};

class ihost : public iobject
{
public:
	virtual void plugin_preset_selected(iplugin *) = 0;
	virtual void plugin_bank_changed(iplugin *) = 0;
	virtual void plugin_preset_changed(iplugin *, uint32_t index) = 0;

	virtual void plugin_load_preset(iplugin *) = 0;
	virtual void plugin_save_preset(iplugin *) = 0;
	virtual void plugin_load_bank(iplugin *) = 0;
	virtual void plugin_save_bank(iplugin *) = 0;

	//TODO: time info
};

} // namespace plum


extern "C"
{
	typedef void (*plum_begin_fn)();
	typedef void (*plum_end_fn)();
	typedef plum_version (*plum_get_version_fn)();
	typedef const char* (*plum_catalog_fn)(int category, uint32_t index);
	typedef const char* (*plum_plugin_info_fn)(const char *name);
	typedef plum::iplugin* (*plum_create_plugin_fn)(const char *name, plum::ihost *);

	void plum_begin();
	void plum_end();
	plum_version plum_get_version();
	const char* plum_catalog(int category, uint32_t index);
	const char* plum_plugin_info(const char *name);
	plum::iplugin* plum_create_plugin(const char *name, plum::ihost *);
}

