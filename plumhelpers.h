
//          Copyright Alessandro De Santis 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#pragma once

#include "plumbase.h"

#include <string.h>
#include <vector>
#include <string>
#include <algorithm>

namespace plum {

// --------------------------------------------------------
// PLUM::STRING
// --------------------------------------------------------

class string : public istring
{
	char *m_text;

public:
	PLUM_IOBJECT_RC_IMPL(m_rc, string)

	void *as(const char *ifid)
	{
		if (std::string(ifid) == IFID_PLUM_OBJECT)
		{
			reference(); return static_cast<istring *>(this);
		}
		else if (std::string(ifid) == IFID_PLUM_STRING)
		{
			reference(); return static_cast<string *>(this);;
		}

		return nullptr;
	}

	string(const char *s)
	{
		m_text = strdup(s);
	}
	virtual ~string()
	{
		free(m_text);
	}

	const char *text() 
	{
		return m_text;
	}
};


// --------------------------------------------------------
// PLUM::BLOB
// --------------------------------------------------------

class blob : public iblob
{
	uint32_t m_size;
	uint8_t *m_data;

public:
	PLUM_IOBJECT_RC_IMPL(m_rc, blob)

	void *as(const char *ifid)
	{
		if (std::string(ifid) == IFID_PLUM_OBJECT)
		{
			reference(); return static_cast<iblob *>(this);;
		}
		else if (std::string(ifid) == IFID_PLUM_BLOB)
		{
			reference(); return static_cast<iblob *>(this);;
		}

		return nullptr;
	}

	blob(uint8_t *data, uint32_t size)
	{
		m_size = size;
		m_data = (uint8_t *)malloc(size);
		memcpy(m_data, data, m_size);
	}

	blob(uint32_t size)
	{
		m_size = size;
		m_data = (uint8_t *)malloc(size);
	}

	virtual ~blob()
	{
		free(m_data);
	}

	uint32_t size() 
	{
		return m_size;
	}

	uint8_t *data() 
	{
		return m_data;
	}
};



} // namespace plum
