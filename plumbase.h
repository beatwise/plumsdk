
//          Copyright Alessandro De Santis 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#pragma once

#include <stdint.h>
#include <stdlib.h>


#define PLUM_IOBJECT_RC_IMPL(rc, type)\
	int rc = 1;\
	void reference() {++rc;}\
	void release() {if (--rc == 0) delete static_cast<type *>(this);}


#define IFID_PLUM_OBJECT 		"plum.object"
#define IFID_PLUM_STRING 		"plum.string"
#define IFID_PLUM_BLOB	 		"plum.blob"
#define IFID_PLUM_WINDOW		"plum.window"
#define IFID_PLUM_HOSTWINDOW 	"plum.hostwindow"

#define	plum_key_none 			0
#define	plum_key_enter			1
#define	plum_key_home			2
#define	plum_key_end			3
#define	plum_key_backspace		4
#define	plum_key_delete			5
#define	plum_key_left			6
#define	plum_key_right			7
#define	plum_key_up				8
#define	plum_key_down			9
#define	plum_key_tab			10

#define	plum_mod_shift			1
#define	plum_mod_control		2
#define	plum_mod_alt			4

#define	plum_button_none		0
#define	plum_button_left		1
#define	plum_button_middle		2
#define	plum_button_right		4

struct plum_size
{
	int width, height;
};



namespace plum {

class iobject
{
public:
	virtual void reference() = 0;
	virtual void release() = 0;
	virtual void *as(const char *ifid) = 0;
};

class istring : public iobject
{
public:
	virtual const char *text() = 0;	
};

class iblob : public iobject
{
public:
	virtual uint32_t size() = 0;	
	virtual uint8_t *data() = 0;	
};

class ihostwindow : public iobject
{
public:
	virtual plum_size get_size() = 0;
	virtual void on_plugin_preferred_size(plum_size) = 0;
	virtual void on_plugin_repaint() = 0;


	virtual void get_clipboard_text() = 0;
	virtual void set_clipboard_text(istring *) = 0;

	virtual void add_timer(void *id, int msperiod) = 0;
	virtual void remove_timer(void *id) = 0;
};

class iwindow : public iobject
{
public:

	virtual void close() = 0;

	virtual plum_size get_preferred_size() = 0;
	virtual void render(uint8_t *pixel_argb32) = 0;

	virtual void on_size(plum_size) = 0;

	virtual void on_mouse_in() = 0;
	virtual void on_mouse_out() = 0;

	virtual void on_mouse_move(float x, float y) = 0;
	virtual void on_mouse_down(float x, float y, uint32_t btn) = 0;
	virtual void on_mouse_up(float x, float y, uint32_t btn) = 0;

	virtual void on_utf8_char(const char *, uint32_t mod) = 0;
	virtual void on_key_down(uint32_t code, uint32_t mod) = 0;
	virtual void on_key_up(uint32_t code, uint32_t mod) = 0;

	virtual void on_paste_text(istring* str) = 0;
	virtual void on_timer(void *id) = 0;

};

} // namespace plum
